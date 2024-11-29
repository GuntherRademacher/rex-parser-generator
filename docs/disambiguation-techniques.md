<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](parse-tree-generation.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](parser-debugging.md)

&nbsp;
# Disambiguation Techniques

This section discusses techniques for addressing parser and lexer construction challenges.

On the lexical level, multiple token definitions may overlap, meaning that a sequence of input characters could match more than one token. This ambiguity needs to be resolved in the grammar specification, as the lexer must return a unique result. REx's strategy of generating specific lexers for each parser state helps reduce lexical ambiguities, but any remaining ambiguities still need to be addressed.

In deterministic parsing, conflicts can arise when the current lookahead sequence matches multiple alternatives for a given grammar rule.

One way to handle such conflicts is through non-deterministic parsing techniques, such as backtracking with LL parsing or GLR parsing. However, these approaches can introduce runtime issues. With backtracking, some input might not be parsed as intended because one alternative may succeed while another, more appropriate alternative, would have yielded the correct result. With GLR parsing, ambiguities may only be detected at runtime.

On the other hand, deterministic parsing methods like LL or LR construction have the advantage of proving that a grammar is unambiguous. While non-deterministic methods are convenient, avoiding them when possible offers the benefit of reducing uncertainty in the parsing process.

In addition to supporting lookaheads longer than a single token, REx provides mechanisms for resolving lexical ambiguities and parsing conflicts. These mechanisms include:

 - [Token preference rules](#token-preference-rules)
 - [Lexical lookahead]()
 - [Ordered alternation](#using-ordered-alternation) 

## Token Preference Rules

The lexer prioritizes the longest matching token. If two or more tokens of the same length match, an error is raised during generation.

For example, a grammar might allow `Integer` and `Decimal` literals in the same context, and also allow `Decimal` literals in some context without a decimal point:

```
...
<?TOKENS?>

Digits  ::= [0-9]+
Integer ::= [-+]? Digits
Decimal ::= [-+]? Digits ('.' Digits?)?
          | [-+]? '.' Digits
...
```

At lexer generation time, the lexer would reject the grammar:

```
--Error-- Lexical ambiguities for Integer(2): Decimal
```

In this case, a [token preference](ebnf-notation.md#token-preference) rule can be used to resolve this issue:

```
Decimal >> Integer
```

With this rule in place, the lexer will prefer `Decimal` over `Integer` when either is expected. The rule could also have been

```
Integer << Decimal
```

with the same meaning. The preference operators `>>` `<<` allow a single token on the left hand side and a list of tokens on the right hand side.

Token preferences are particularly useful when [implementing non-reserved keywords](grammar-processing.md#implementing-non-reserved-keywords).


## Lexical Lookahead

The lexer definition allows the specifcation of a lookahead character sequence. This is achieved by using the lexical lookahead operator `&`, followed by an expression describing the lookahead. It can be done for each top-level alternative of a lexical rule. At runtime, the lookahead sequence is expected to follow the token that it is specified for, but it is not consumed as content of the token. Rather it is left in the input character stream for being processed with the next tokenization step.

While this kind of lookahead affects lexer operation, it can also be used for resolving conflicts on syntax level. In order to do this, define an empty token that only asks for some lookahead, and refer to it in a syntax rule. For example, this grammar cannot be handled by an LL parser, because there is no way to distinguish between the alternatives before processing them to up their end:

```
S ::= 'a'* 'b'
    | 'a'* 'c'
```

But it can be handled when introducing a lookahead-only token. In this case the lexer scans upcoming input, without consuming it, and delivers the `lookahead_for_b` token, allowing the parser a decision for the first alternative:

```
S ::= lookahead_for_b 'a'* 'b'
    |                 'a'* 'c'

<?TOKENS?>

lookahead_for_b ::= & ('a'* 'b')
```

Due to it being handled by the lexer, the lookahead can only be regular.

## Using Ordered Alternation

Sometimes during parser construction the distinction of alternatives cannot be done with reasonable lookahead. REx offers ordered alternation to help in cases where it possible to statically prefer particular alternatives over others.

An example where this comes to help can be found in the specification of [XQuery](https://www.w3.org/TR/xquery-31/). It has [this rule](https://www.w3.org/TR/xquery-31/#id-path-expressions):

```
PathExpr	   ::= ("/" RelativePathExpr?)         /* xgc: leading-lone-slash */
                 | ("//" RelativePathExpr)
                 | RelativePathExpr
```

When using the plain grammar with REx and `-ll 3`, there are lots of sLL(3) conflicts for the "optional" operator `?` in the first alternative, because a lookahead of 3 tokens in insufficient for distinguishing the followers of `PathExpr` from the token sequences that a `RelativePathExpr` can begin with. REx will respond like this:

```
strong-LL(3) conflict #1 in optional operator of production PathExpr:
  conflicting lookahead token sequences:
    'and' '(' IntegerLiteral
    'case' '(' IntegerLiteral
    'div' '(' IntegerLiteral
    'else' '(' IntegerLiteral
    'eq' '(' IntegerLiteral
    'except' '(' IntegerLiteral
    'ge' '(' IntegerLiteral
    'gt' '(' IntegerLiteral
    'idiv' '(' IntegerLiteral
    'intersect' '(' IntegerLiteral
    'is' '(' IntegerLiteral
    'le' '(' IntegerLiteral
    'lt' '(' IntegerLiteral
    'mod' '(' IntegerLiteral
    'ne' '(' IntegerLiteral
    'or' '(' IntegerLiteral
    ... 31146 more
grammar fails to be strong-LL(3)
```

Fortunately the specification additionally has this ["extra-grammatical constraint: leading-lone-slash"](https://www.w3.org/TR/xquery-31/#parse-note-leading-lone-slash):

> If the token immediately following a slash can form the start of a RelativePathExpr, then the slash must be the beginning of a PathExpr, not the entirety of it.

Though this cannot be fed to REx as is, we can slightly change the grammar to resolve the conflicts. We will rewrite the "optional" operator `?` to a choice between `RelativePathExpr` and the empty alternative, and use an ordered alternation `/` for it:

```
PathExpr	   ::= ("/" ( RelativePathExpr
                        / 
                        )
                 | ("//" RelativePathExpr)
                 | RelativePathExpr
```

The effect will be that during parser construction, the first alternative, `RelativePathExpr`, is preferred over the second, which is still used in cases where the lookahead is not suitable for the first one.

&nbsp;
---
[⇦ Previous page](parse-tree-generation.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](parser-debugging.md)