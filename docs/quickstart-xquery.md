<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](quickstart-typescript.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-xslt.md)

&nbsp;
# Quick Start Guide for Generating and Running a Parser in XQuery with REx

This tutorial will guide you through creating and running a parser in XQuery for a simple arithmetic expression grammar using REx. It will also show how to visualize parse trees, trace parser operation, and spotlight some properties of the generated code. Finally it will show how to annotate the grammar with target language code in order to process the parser's input at runtime.

## Prerequisites

The XQuery code generated by REx conforms to XSLT 1.0 when generating an LL or LR parser, and to XQuery 3.1 for a GLR one. REx-generated code has been tested with BaseX and Saxon, in the examples below, we will use BaseX 11.1. Make sure you have BaseX available as a prerequisite. Earlier or later versions might do as well, it is certainly worth trying.

## Step 1: Define the Grammar

Create a text file named `Arithmetic.ebnf` and define the grammar for simple arithmetic expressions as follows:

```
Expression ::= Term (('+' | '-') Term)*
Term       ::= Factor (('*' | '/') Factor)*
Factor     ::= ('+' | '-')? Primary
Primary    ::= Number
             | '(' Expression ')'

<?TOKENS?>

Number     ::= [0-9]+
Whitespace ::= [ #x9#xA]+
               /*ws: definition*/
```

This grammar defines:

  - basic arithmetic operations (`+`, `-`, `*`, `/`)
  - integer numbers
  - ignored whitespace

We will use it to produce parse trees, trace parser and lexer execution, and evaluate actual arithmetic expressions to get their result.

Two remarks on the grammar:

 - Note that `<?TOKENS?>` separates syntax rules from lexical rules. While syntax rules describe the structure of the language, lexical rules define individual tokens. These sections have different constraints: syntax rules allow recursive patterns, whereas lexical rules are restricted to regular expressions.
 - This grammar does not enforce end-of-input processing. As a result, a parser generated from it may accept input as valid once it reaches a stopping point, even if additional characters remain. This behavior could lead to subtle bugs, especially when input is expected to match the grammar entirely. To ensure complete processing, additional checks or rules should be added to handle end-of-input explicitly.

## Step 2: Generate the Parser and Lexer

Open a command prompt or terminal and navigate to the directory containing `Arithmetic.ebnf`. Run the following command to generate the parser and lexer code:

```sh
rex -xquery -main -tree Arithmetic.ebnf
```

This command line asks REx for

  - a parser and lexer in XQuery (`-xquery`),
  - a simple main program for it (`-main`),
  - code generation for parse tree production (`-tree`),
  - using the grammar in file `Arithmetic.ebnf`.

The result will be an XQuery file named `Arithmetic.xquery` in the current directory, containing the generated code.

The command line is used to specify the generator's options. With the above command, we have chosen the default LL parsing algorithm, which would have been specified as `-ll 3` explicitly (the grammar being LL(1), though). In case an LR parser is preferred, `-lalr 1` could have been used as an alternative here.

## Step 3: Run the Generated Code

The generated code is self-contained, i.e. it has in it everything that is needed and does not need anything to be added. So you are now in a position to run it. At this point it can be used to dump the parse tree in XML while parsing any input - this is the functionality of the main program that was generated in response to REx option `-main`.

The main program requires the setting of external variable `input`. This can be a filename, but when enclosed in curly braces, it is taken as literal text.

So it can be run, passing command line arguments like this:

```sh
basex "-binput={1 + 2 * 3}" Arithmetic.xquery
```

The actual input that is parsed in this case is `1 + 2 * 3`, the curly braces are stripped as the literal indicator, the double quotes serve for making it a single command line argument, and `-binput=` binds the string following it to variable `$input`.

This results in the output of a lossless representation of the concrete parse tree, for the given input, in XML:

```xml
<Expression><Term><Factor><Primary><Number>1</Number></Primary></Factor></Term> <TOKEN>+</TOKEN> <Term><Factor><Primary><Number>2</Number></Primary></Factor> <TOKEN>*</TOKEN> <Factor><Primary><Number>3</Number></Primary></Factor></Term></Expression>
```

It is lossless in the sense that it contains every single character of the input as content, where the parse tree structure has been inserted as markup. Taking the string value of the XML document would regain the original input.

For making it more readable, serialization option `indent` could be used to add extra whitespace and indentation:

```sh
basex -sindent=yes "-binput={1 + 2 * 3}" Arithmetic.xquery
```

results in

```xml
<Expression>
  <Term>
    <Factor>
      <Primary>
        <Number>1</Number>
      </Primary>
    </Factor>
  </Term> <TOKEN>+</TOKEN> <Term>
    <Factor>
      <Primary>
        <Number>2</Number>
      </Primary>
    </Factor> <TOKEN>*</TOKEN> <Factor>
      <Primary>
        <Number>3</Number>
      </Primary>
    </Factor>
  </Term>
</Expression>
```

Note that this is the concrete parse tree, containing nodes for each and every derivation step that was taken during parsing. Usually many of those are not needed for further processing, so it often makes sense to condense the parse tree before applying any further transformations to it. In the actual case, a tree like the following could be sufficient:

```xml
<Expression>
  <Number>1</Number>
  <TOKEN>+</TOKEN>
  <Term>
    <Number>2</Number>
    <TOKEN>*</TOKEN>
    <Number>3</Number>
  </Term>
</Expression>
```

However condensing the tree must be performed on behalf of the application, REx does not provide means to support it.

When looking at the generated XQuery code, you will find the main program as an example of how to invoke the generated parser:

```xquery
(:~
 : The input filename, or string, if surrounded by curly braces.
 :)
declare variable $input as xs:string external;

let $result :=
  if (matches($input, "^\{.*\}$")) then
    p:parse-Expression(substring($input, 2, string-length($input) - 2))
  else
    p:parse-Expression(unparsed-text($input, "utf-8"))
return
  if (empty($result/self::ERROR)) then
    $result
  else
    error(xs:QName("p:parse-Expression"), concat("&#10;    ", replace($result, "&#10;", "&#10;    ")))
```

For the start symbol of the grammar, `Expression`, REx has generated function `parse-Expression`, which when called with an input string, returns an `Expression` element node that represents the parse tree, or an `ERROR` element in case of parsing errors.

## Step 4: Trace Lexer and Parser Execution

For debugging grammars, it is often useful to see the actions that the lexer and parser are performing during execution. When using the `-trace` command line option, REx will generate additional code that writes a log of actions, in XML.

```sh
rex -xquery -main -trace Arithmetic.ebnf
basex "-binput={1 + 2 * 3}" Arithmetic.xquery
```

The trace is written using XQuery function `fn:trace`. It is written in XML, but `fn:trace` output typically contains some extra annotations, e.g. BaseX quotes the content, with its internal qutoes escaped. This is may vary when using another XQuery processor. The word `trace`, that is prepended to each line is the label that is passed to `fn:trace`.

```xml
trace"<trace>"
trace"  <parse startnonterminal=""Expression""/>"
trace"  <tokenize tokenset=""1"">"
trace"    <next state=""2"" offset=""1"" char=""1"" codepoint=""49"" class=""7"" result=""Number""/>"
trace"    <next state=""4"" offset=""2"" char="" "" codepoint=""32"" class=""8""/>"
trace"    <done result=""Number"" begin=""1"" end=""2""/>"
trace"  </tokenize>"
trace"  <parse startnonterminal=""Term"" input=""Number""/>"
trace"  <parse startnonterminal=""Factor"" input=""Number""/>"
trace"  <parse startnonterminal=""Primary"" input=""Number""/>"
trace"  <parse terminal=""Number""/>"
trace"  <parse endnonterminal=""Primary""/>"
trace"  <parse endnonterminal=""Factor""/>"
trace"  <tokenize tokenset=""2"">"
trace"    <next state=""3"" offset=""2"" char="" "" codepoint=""32"" class=""8"" result=""Whitespace""/>"
trace"    <next state=""5"" offset=""3"" char=""+"" codepoint=""43"" class=""4""/>"
trace"    <done result=""Whitespace"" begin=""2"" end=""3""/>"
trace"  </tokenize>"
trace"  <tokenize tokenset=""2"">"
trace"    <next state=""3"" offset=""3"" char=""+"" codepoint=""43"" class=""4"" result=""'+'""/>"
trace"    <done result=""'+'"" begin=""3"" end=""4""/>"
trace"  </tokenize>"
trace"  <parse endnonterminal=""Term"" input=""'+'""/>"
trace"  <parse terminal=""'+'""/>"
...
```

The `parse` actions show how the parser makes its way through the grammar rules by entering and leaving the code that corresponds to the grammar nonterminals, or consuming terminals.

The `tokenize` actions show how the lexer assembles tokens from input characters.

Some details in this trace may be understandable only by looking at some internals of the parser, but the trace can by useful anyway because it documents the course of action. As trace output may become huge, it is a good idea to isolate a problem to as small as possible a reproduction, before using a trace to analyze it.

## Step 5: Annotate the Grammar with XQuery code

Usually you do not want to just see the parse tree, but rather compile and execute the language that is being parsed. In case of the grammar for arithmetic expressions, this could be evaluating the expressions to their result.

While it is possible to do this evaluation based on a parse tree, it can also be done by omitting parse tree generation, and instead annotating the grammar with actions in XQuery code, that will be triggered during parser execution. This is what we will be doing in this step.

The parser maintains its state in a variable called `$state`, which is a sequence of items. There is a constant, declared as a variable named `$p:result`, that holds the index of the first item in the `$state` sequence that is not used for internal purposes by the parser. Initially, the sequence ends exactly before this index, allowing us to maintain our own state in the subsequent elements.

In our example we will use the end of `$state` as a stack, appending our items, and removing them from the end when evaluating them.

For achieving evaluation, we will augment the grammar with the following actions, whose implementation details will be shown later:

- `local:number($state)`: push numeric value of most recently consumed token onto the stack,
- `local:push($state, $item)`: push an item onto the stack,
- `local:pop($state)`: pop the top item off of the stack
- `local:evaluate($state)`: pop an operand, and operator, and maybe a second operand off of the stack and evaluate the operator on the operands, then pushing the result back onto the stack.

Each of these actions will return an updated state, to be stored in variable `$state`.

For inserting an action in XQuery into the EBNF grammar, it must be wrapped in a **processing instruction**, which

- begins with `<?` and a name,
- continues with some whitespace, and the actual XQuery code,
- terminates with `?>`.

The inserted XQuery code of course must not contain the character sequence `?>`.

A grammar may contain multiple action sets using different names, and an action is only included into the generated code, if its name is selected using the `-a` command line option to specify the name. We will use `aee` as the name of our set of actions, as an acronym for *A*rithmetic *E*xpression *E*valuator. Thus command line option `-a aee` must be used, and actions inserted into the grammar will look like this: `<?aee let $state := local:number($state)?>`.

The actions are positioned in the grammar as follows:

```
Expression ::= Term (('+'                   <?aee let $state := local:push($state, '+')?>
                          | '-'             <?aee let $state := local:push($state, '-')?>
                               ) Term       <?aee let $state := local:evaluate($state)?>
                                      )*
Term       ::= Factor (('*'                 <?aee let $state := local:push($state, '*')?>
                            | '/'           <?aee let $state := local:push($state, '/')?>
                                 ) Factor   <?aee let $state := local:evaluate($state)?>
                                         )*
Factor     ::=                              <?aee let $state := local:push($state, ' ')?>
               ('+' | '-'                   <?aee
                                              let $state := local:pop($state)
                                              let $state := local:push($state, '_')
                                            ?>
                          )? Primary        <?aee let $state := local:evaluate($state)?>
Primary    ::= Number                       <?aee let $state := local:number($state)?>
             | '(' Expression ')'
```

Actions may be placed anywhere on the right hand side of the syntax rules, and they will be executed when the parser's control flow passes by the respective position. Note that actions can only be placed in the syntax definition, but not in the lexical definition.

You are free in formatting the grammar as you like, but in the example above, actions have been aligned on the right hand side, in order to visually separate them from the pure grammar rules on the left hand side.

Now for actually implementing the functions used in our actions, we need to add some more XQuery code:

```xquery
  declare function local:evaluate($state) {
    let $length := count($state)
    let $rhs := $state[$length]
    let $op := $state[$length - 1]
    let $lhs := $state[$length - 2]
    let $pop := if ($op = (' ', '_')) then 2 else 3
    let $result := switch ($op)
      case '+' return $lhs + $rhs
      case '-' return $lhs - $rhs
      case '*' return $lhs * $rhs
      case '/' return $lhs idiv $rhs
      case '_' return - $rhs
      default  return $rhs
    return (subsequence($state, 1, $length - $pop), $result)
  };

  declare function local:number($state) {
    let $begin := $state[$p:b0]
    let $end := $state[$p:e0]
    let $length := $end - $begin
    let $token := substring($input, $begin, $length)
    return ($state, xs:integer($token))
  };

  declare function local:push($state, $item) {
    ($state, $item)
  };

  declare function local:pop($state) {
    subsequence($state, 1, count($state) - 1)
  };
```

Also we will no longer use the standard main program, that is generated when using the `-main` REx command line option, but supply our own main program, taking input from external variable `$input`, passing it to the parser, and returning the result:

```xquery
  declare variable $input as xs:string external;

  let $result := p:parse-Expression($input)
  return
    if ($result instance of element(ERROR)) then
      error(xs:QName("p:parse-Expression"), $result)
    else
      $result
```

Both of this, the code implementing the actions and the main program can be added to the grammar file, for having REx include it into the generated code. Such extra code can be added

- at the very beginning of the grammar. In this case it must also contain a module declaration or a namespace declaration for prefix `p`. In absence of the `-main` command line option, REx generates a module declaration. Thus if we don't want to use `-main`, but want to have a main module, we must specify a namespace declaration.
- at the end of the grammar, following an `<?ENCORE?>` indicator. In that case, the code is just appended to the end of the generated `.xquery` file.

We will add the namespace declaration at the beginning, and the rest of our code at the end, such that the complete file `Arithmetic.ebnf` now looks as follows:

```
<?aee
  declare namespace p="Arithmetic";
?>

Expression ::= Term (('+'                   <?aee let $state := local:push($state, '+')?>
                          | '-'             <?aee let $state := local:push($state, '-')?>
                               ) Term       <?aee let $state := local:evaluate($state)?>
                                      )*
Term       ::= Factor (('*'                 <?aee let $state := local:push($state, '*')?>
                            | '/'           <?aee let $state := local:push($state, '/')?>
                                 ) Factor   <?aee let $state := local:evaluate($state)?>
                                         )*
Factor     ::=                              <?aee let $state := local:push($state, ' ')?>
               ('+' | '-'                   <?aee
                                              let $state := local:pop($state)
                                              let $state := local:push($state, '_')
                                            ?>
                          )? Primary        <?aee let $state := local:evaluate($state)?>
Primary    ::= Number                       <?aee let $state := local:number($state)?>
             | '(' Expression ')'

<?TOKENS?>

Number     ::= [0-9]+
Whitespace ::= [ #x9#xA]+
               /*ws: definition*/

<?ENCORE?>

<?aee
  declare function local:evaluate($state) {
    let $length := count($state)
    let $rhs := $state[$length]
    let $op := $state[$length - 1]
    let $lhs := $state[$length - 2]
    let $pop := if ($op = (' ', '_')) then 2 else 3
    let $result := switch ($op)
      case '+' return $lhs + $rhs
      case '-' return $lhs - $rhs
      case '*' return $lhs * $rhs
      case '/' return $lhs idiv $rhs
      case '_' return - $rhs
      default  return $rhs
    return (subsequence($state, 1, $length - $pop), $result)
  };

  declare function local:number($state) {
    let $begin := $state[$p:b0]
    let $end := $state[$p:e0]
    let $length := $end - $begin
    let $token := substring($input, $begin, $length)
    return ($state, xs:integer($token))
  };

  declare function local:push($state, $item) {
    ($state, $item)
  };

  declare function local:pop($state) {
    subsequence($state, 1, count($state) - 1)
  };

  declare variable $input as xs:string external;

  let $result := p:parse-Expression($input)
  return
    if ($result instance of element(ERROR)) then
      error(xs:QName("p:parse-Expression"), $result)
    else
      $result
?>
```

For having REx insert our newly added actions into the generated code, option `-a aee` must be added to the REx command line. Without that, there would be no difference in behavior, compared to the plain grammar that was used before.

Generate a parser including the actions, using this command:

```sh
rex -xquery -a aee Arithmetic.ebnf
```

Now it can be run to actually evaluate arithmetic expressions specified in variable `$input`, e.g.

```sh
basex "-binput=( 42 * 17 + 6 ) / 8 - -9" Arithmetic.xquery
```

&nbsp;
---
[⇦ Previous page](quickstart-typescript.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-xslt.md)