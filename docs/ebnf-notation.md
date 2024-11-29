<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](supported-algorithms.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](grammar-for-parsing-ebnf.md)

&nbsp;
# EBNF Notation

Extended Backus-Naur Form (EBNF) is the formal notation used to define the grammar of programming languages, protocols, and data formats. There are several variants of EBNF out there. This section provides an explanation of the specific EBNF format used by REx parser generator. It is closely related to the format used by W3C in the XML and XQuery recommendations.

The following describes the individual elements of the grammar notation. As REx itself uses a REx-generated parser for processing the input grammr, its own grammar can be inspected for reference here: [EbnfParser.ebnf](../rex/src/parser/EbnfParser.ebnf).

## Grammar Structure

A REx grammar is divided into three sections:

```
// The syntax rules. Each REx grammar begins with the syntax rules.

<?TOKENS?>

// The lexical definition, introduced by the <?TOKENS?> token. It is optional,
// because a grammar might get along with just literal tokens in the syntax rules.

<?ENCORE?>

// Additional target language code, introduced by the <?ENCORE?> token. The target
// language code in this optional section will be placed at the bottom of the
// generated parser file, if selected by command line option -a.
```

Syntax rules define the structure of valid sentences in the language. They specify how tokens can be combined to form valid expressions, statements, or other language constructs. From these rules an LL or LR parser is generated, which processes the input token sequence.

Lexical structure defines the individual tokens used in the syntax rules. These are the basic building blocks of the language, for example keywords, identifiers, operators, and literals. The lexical rules are used to generate a set of finite automata that recognize these tokens. The lexical analyzer (lexer) processes the input to produce tokens, which are then passed on to the syntax analyzer (parser) to form a parse tree.

The notations used for syntax rules and lexical definition are very similar, however many of the constructs that are explained in more detail below are allowed only in the lexical definition. These are

 - [any character](#any-character)
 - [end-of-input](#end-of-input)
 - [character classes](#character-classes)
 - [hexadecimal escape notation](#hexadecimal-escape-notation)
 - [exclusion](#exclusion)
 - [non-greedy tokens](#non-greedy-tokens)
 - [lookahead](#lookahead)
 - [lookahead list](#lookahead-list)
 - [token precedence](#token-precedence)
 - [character equivalence](#character-equivalence)

Only allowed in syntax rules, and disallowed in lexical rules, are

 - [ordered alternation](#ordered-alternation)
 - [annotation with target language code](#annotation-with-target-language-code)

## Names

A name in the Grammar begins with a Unicode letter, and continues with zero or more Unicode letters or digits or additional name characters (see `Name` in the [Grammar for Parsing EBNF](grammar-for-parsing-ebnf.md) for details).

The names are case-sensitive. Upper and lower case characters can be used, but no particular meaning is assigned to the case of characters. The names of syntax rules are mapped to names in the generated program. For some target languages, the case might be adapted automatically. 

**Examples:**

```
Expression
Term
Factor
Number
Letter
Digit 
```

Names are used for nonterminal symbols in the syntax rules, and for tokens defined in the lexical definition.

Sometimes it is useful to use the same name for both a nonterminal and a token, or to have two tokens sharing the same definiton, but with different token identities. In these cases it is necessary to mark token references when they occur in the syntax rules, by appending a caret `^` to the name, followed by another name.

**Example:**

```
Idenfifier^Token
```

## Nonterminal Symbols

Nonterminal symbols are the names of the syntax rules. They appear on the left hand side of a syntax rule definition, and on the right hand side of syntax rules as a reference.

**Example:**

```
Expression
```

## Terminal Symbols

The terminal symbols, or tokens, of the grammar are 

 - quoted string literals occurring in the syntax rules, enclosed in single quotes or double quotes. There is no escape notation for having the quote character withing the literal, so a literal cannot contain both a single quote and a double quote.
 - names occurring in the syntax rules, but not defined there. Any names that are not defined as nonterminals within the syntax rules are considered terminal names and must be defined in the lexical definition.
 - names (or string literals) that carry a suffix introduced by a caret `^`. These are used to distinguish a terminal name from an otherwise identical nonterminal name, or a terminal from another distinct terminal sharing the same definition.

**Example:** 

```
'{' | '}' | "0" | "1" | Letter | Operator^Token
```

Literal token references can also use the trailing caret `^` notation to select a particular token identity.

**Examples:**

```
'*'^Wildcard
'*'^Occurrence
'*'^Multiplication
```

## Concatenation

Concatenation is the sequential occurrence of symbols or groups. It is the default operation and does not require an explicit operator. Symbols to be concatenated are simply written next to each other, separated by whitespace.

**Example:**

```
Integer ::= Digit Digit*
```

## Alternation

Alternation denotes a choice between multiple options. It is represented by the vertical bar `|`. 

**Example:**

```
Sign ::= '+' | '-'
```

Alternation has a lower precedence than concatenation, i.e. `A B | C` is equivalent to `( A B ) | C`.

## Ordered Alternation

Ordered alternation represents a choice between multiple options, denoted by the slash /. In this approach, alternatives are prioritized during parser construction based on their position in the grammar definition, with earlier alternatives taking precedence over later ones. Any conflicts in parser construction, such as overlaps or ambiguities between alternatives, are automatically resolved by favoring the earlier-defined alternative and disregarding the later one.

This operator is supported only in syntax rules.

For a real-world example, see [Using Ordered Alternation](disambiguation-techniques.md#using-ordered-alternation) in section on [Disambiguation Techniques](disambiguation-techniques.md).

Ordered alternation has a lower precedence than concatenation, i.e. `A B / C` is equivalent to `( A B ) / C`. It must not be intermixed with unordered alternation on the same level.

## Occurrence

An occurrence operator specifies how many times a symbol or group of symbols can repeat.

- `*` denotes zero or more occurrences.
- `+` denotes one or more occurrences.
- `?` denotes zero or one occurrence.

**Example:**

```
Digits       ::= Digit*   // Zero or more digits
Digits1      ::= Digit+   // One or more digits
OptionalSign ::= '-'?     // An optional minus sign
```

Occurrence operators have a higher precedence than concatenation, i.e. `A B?` is equivalent to `A (B?)`.

## Grouping

Grouping combines subexpessions into a group, that is treated as a single unit when applying surrounding operators, thus overriding operator precedence. Parentheses `(` `)` are used for grouping.

**Example:**

```
Number ::= ('+' | '-')? Integer
```

## Comments

Comments are used to add explanatory notes within the grammar.

- **Single-line comments** start with double slashes `//`.
- **Multi-line comments** start with `/*` and end with `*/`.

**Example:**

```
OptionalSign ::= '-'?     // This is a single line comment

/* This is a comment
   that actually spans
   multiple lines */
```

## Rules

A rule definition assigns a pattern to a nonterminal symbol. The assignment operator `::=` is used to define a rule.

**Example:**

```
Digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
```

## Annotation with Target Language Code

Annotations with actions in target language code can be included 

 - before the syntax definition. Code placed here will be go to the beginning of the generated parser file. It must also contain the initial part of the generated program up to class declarations and constructors.
 - anywhere in a syntax rule. The action will be executed whenever the parser's control flow passes by its position in the rule.
 - at the end of the grammar, in an Encore section. Code placed here will go to the end of the generated parser file. It must also include any closing braces, if applicable.

An annotation starts with `<?`, immediately followed by an a name, then whitespace, the actual code (not containing `?>`), and `?>` at the end.

Annotations need to be activated by a `-a` command line option followed by the annotation name. The grammar can contain multiple sets of annotations using different names, and by activating one using command line option `-a`, the respective actions will be enabled.

**Example:**

```
Expression ::= Term (('+' | '-') Term)*     <?java System.out.println("Parsed an expression");?>
Term       ::= Factor (('*' | '/') Factor)* <?java System.out.println("Parsed a term");?>
Factor     ::= ('+' | '-')? Primary         <?java System.out.println("Parsed a factor");?>
Primary    ::= Number                       <?java System.out.println("Parsed a number");?>
             | '(' Expression ')'           <?java System.out.println("Parsed a parenthesized expr");?>

<?TOKENS?>

Number     ::= Digit Digit*
Digit      ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
```

Note: while the actions integrate seamlessly with LL parsing, their presence in arbitrary positions may cause conflicts in LR parsing, that would not be there without the action. This is due to the fact that an LR parser does not have clarity about an already processed sequence of tokens until it can involve them in a reduction. So the natural place to attach an action in an LR parser is at the end of a top level alternative of a syntax rule, i.e. when the LR parser performs a reduction anyway.

REx supports actions in other places as well, but it will introduce extra reductions just for them. This means that a decision may be forced much earlier, and this is what may cause an LR conflict.

An LL parser does not have this problem, because it always must decide early. So the advantage, that an LR parser usually has by deciding late, is given up to some extent, when actions are placed where a reduction was not needed yet.

## Hexadecimal Escape Notation

In the lexical definition, it is possible to use an escape notation for characters. This starts with `#x`, followed by the hexadecimal digits of the Unicode code point.

**Example:**

```
CR_LF ::= #xA #xD
```

## Character Classes

In the lexical definition, character classes are used to define sets of characters. They are enclosed in square brackets `[` `]` and can contain enumerations of literal characters, hexadecimal escaped charactes, and ranges thereof, where a dash `-` between two characters stands for the inclusive range of characters from the character on the left of it to the character on the right of it. A dash `-` representing itself must be placed as the first literal character of the character class.

A character class starting with a caret `^` consists the complement of the specified characters with respect to the set of all valid characters. A caret `^` representing itself cannot be placed at the very beginning of the character class.

**Example:**

```
Digit    ::= [0-9]
Letter   ::= [a-zA-Z]
NonDigit ::= [^0-9]
```

## Any Character

In the lexical definition, a single unquoted dot `.` represents any character out of the set of all valid characters that the lexer supports.

**Example:**

```
NonLetter ::= . - Letter
```

The set of all valid characters by default consists of these Unicode characters:

```
#x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF]
```

It can however be redefined by adding a rule with the dot `.` on the left hand side.

**Example:**

```
.  ::= [#x9xA#xD#x20-#x7E]  // printable ASCII chars
```

All characters and character ranges that are used in literals, hexadecimal escaped characters, or character classes throughout the grammar are considered valid characters as well, even if they do not occur in the definition given for `.`. The set of all valid characters is also relevant for character class complements.

## End-of-Input

In the lexical definition, a dollar sign `$` represents the end of input.

**Example**:

```
EOF ::= $
```

## Exclusion

In the lexical definition, the general exclusion operator `-` is used to exclude complex expressions from each other.

**Example:**

```
Comment ::= '/*' (.* - (.* '*/' .*)) '*/'
```

In the above example, `Comment` matches anything starting with `/*` and ending with `*/`, excluding any occurrence of `*/` within the comment.

The exclusion operator must not occur in a concatenated sequence, rather there must be a single expression or group on both its left and right hand sides. All of the parentheses in the above example are thus required.

## Non-greedy Tokens

In the lexical definition, a rule that defines a token can be marked as non-greedy, by appending a question mark `?` to its name on the right hand side of the rule definition.

This overrules, for the token using this, the lexers behavior of going for the longest possible pattern matching its definition. Instead the shortest input that matches the definition will yield the token.

**Example:**

Specifying non-greedy tokens is useful for tokens containing arbitrary content that is terminated by some patterm e.g. a Java multi-line comment:

```
MultiLineComment? ::= '/*' . '*/'
```

Without using a non-greedy token, the specificaton would have been much more complicated, e.g.:

```
MultiLineComment ::= '/*' ( [^*] | '*' [^/] )* '*'+ '/'
```

## Lookahead

In the lexical definition, a top-level alternative in a rule may be followed by the `&` operator and a lookahead expression. The correspoding token will then only be recognized by the lexer, if it is followed by the given lookahead.

As a restriction imposed by the implementation, either the token definition or the lookahead definition must produce a fixed length. It is not supported to specify variable-length lookahead for a variable-length token.

**Example**:

This is an example from the [XQuery 3.1 grammar](sample-grammars/XQuery-31.ebnf). It is meant for lexing and parsing `<![CDATA[abc]]>` as a squence of three tokens `<![CDATA[`, `abc`, and `]]>`, disallowing interspersed whitespace. The advantage of this is that the content goes into a separate token, with the introducer and terminator already stripped from it.

```
CDataSection
         ::= '<![CDATA[' CDataSectionContents ']]>'
          /* ws: explicit */

<?TOKENS?>

CDataSectionContents
         ::= Char* - ( Char* ']]>' Char* ) & ']]'
```

Without using the lookahead, the content would include the two brackets near the end, because they are part of the longest sequence of characters not containing `]]>`.

## Lookahead List

In the lexical definition, a lookahead list can be used to ask for a list of tokens all to be followed by the same lookahead. 

The specification begins with the name of a lexical rule (specifiying the lookahead) on the left hand side, followed by the `\\` operator, followed by one or more token names or literals on the right hand side. The lexer will only recognize the tokens in this list, when they are immediately followed by the given lookahead.

**Example**:

In this example, a lookahead list is used to ensure that each of the listed keywords is followed by a character other than an ASCII letter, or by the end-of-input, such that adjacent keywords without intervening whitespace are not permitted. Without such provision, the lexer is allowed to tokenize two adjacent keywords, such as `beginend`, into subsequent tokens `begin` `end`, which is usually not wanted.

```
NonLetter ::= [^a-zA-Z] | $
NonLetter  \\ 'and' 'begin' 'end' 'for' 'or' 'while' 'until'
```

## Token Preference

In the lexical definition, token preferences can by specified to eliminate lexcial ambiguities between multiple tokens. A preference speficiation begins with a token name or literal, followed by a `<<` or `>>` operator, followed by a list of token names or literals. The `<<` operator specifies that the token on the left hand side has a lower precedence than the tokens on the right hand side, while the `>>` operator specifies that the token on the left hand side has a higher precedence than the tokens on the right hand side.

In a situation where the input conforms to either of two token definitions, and a precedence has been established for them, the lexer will produce the token with the higher precedence.

**Example**:

This is useful for resolving lexical ambiguities between keywords and identifiers:

```
Identifier ::= [a-zA-Z] [a-zA-Z0-9]
Identifier  << 'and' 'begin' 'end' 'for' 'or' 'while' 'until'
```

Note that a specification like this does not establish reserved keywords, at least not fully, because it only applies to parser states where either token is actually expected. An `Identifier` might still match a keyword, when it appears in a state where the keyword is unexpected. For reserving keywords, rather use an exclusion in the definition of `Identifier`.

## Character Equivalence

In the lexical definition, two characters or character ranges can be declared as equivalent by using the `==` operator. When ranges are specified, they must be of the same length.

**Example:**

```
[A-Z] == [a-z]
```

This is useful for case-insensitive languages, eliminating the need to enumerate individual characters in different cases.

## Whitespace definition

For allowing the generated parser to skip whitespace implicitly, without having to specify its occurrences throughout the grammar, a whitespace definition rule can be used. This is accomplished by appending an annotation of `/*ws: definition*/` to the end of a rule. This annotation allows the parser to ignore matching whitespace between any two symbols of each syntax rule, unless the rule itself is annotated with `/*ws: explicit*/`.

The rule annotated with `/*ws: definition*/` can be a lexical rule or a syntax rule. With a syntax rule, the whitespace definition can be recursive, which is not possible with a lexical rule. However when using a syntax rule, the tokens that whitespace may start with, must be distinct from any tokens used in non-whitespace rules. 

Disallowing whitespace with `/*ws: explicit*/` only applies to the syntax section. There is no implicit whitespace handling in the lexical section. There is thus no need to annotate lexical rules with `/*ws: explicit*/`, as it is the only available option for them.

Besides plain whitespace, the whitespace definition rule would typically also cover comments and other ignorable content, that can occur between any two tokens.

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

Rather than defining single-character whitespace, it is advisable to define consecutive whitespace as a single token. This way, the effort keeps restricted to the lexer, rather than having it pass every single whitespace character to the parser.

&nbsp;
---
[⇦ Previous page](supported-algorithms.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](grammar-for-parsing-ebnf.md)