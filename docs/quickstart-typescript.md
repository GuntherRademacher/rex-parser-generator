<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](quickstart-scala.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-xquery.md)

&nbsp;
# Quick Start Guide for Generating and Running a Parser in TypeScript with REx

This tutorial will guide you through creating and running a parser in TypeScript for a simple arithmetic expression grammar using REx. It will also demonstrate how to visualize parse trees, trace parser operations, and highlight some key properties of the generated code. Finally, it will show you how to annotate the grammar with target language code to process the parser's input at runtime.

## Prerequisites

In this tutorial, we will use the Node.js runtime environment for executing TypeScript from a command line. Make sure that you have Node.js installed.

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
rex -typescript -main -tree Arithmetic.ebnf
```

This command line asks REx for

  - a parser and lexer in TypeScript (`-typescript`),
  - a simple main program for it (`-main`),
  - code generation for parse tree production (`-tree`),
  - using the grammar in file `Arithmetic.ebnf`.

The result will be a TypeScript file named `Arithmetic.ts` in the current directory, containing the generated code.

The command line is used to specify the generator's options. With the above command, we have chosen the default LL parsing algorithm, which would have been specified as `-ll 3` explicitly (the grammar being LL(1), though). In case an LR parser is preferred, `-lalr 1` could have been used as an alternative here.

## Step 3: Compile the Generated Code

The generated file is self-contained, i.e. it has in it everything that is needed and does not need anything to be added. So just compile it with the TypeScript compiler:

```sh
tsc Arithmetic
```

## Step 4: Run the Generated Code

You are now in a position to run the generated code. At this point it can be used to dump the parse tree in XML while parsing any input - this is the functionality of the main program that was generated in response to REx option `-main`.

Running it without any command line arguments,

```sh
node Arithmetic
```

shows the usage text:

```
Usage: node Arithmetic.js [-i] INPUT...

  parse INPUT, which is either a filename or literal text enclosed in curly braces

  Option:
    -i     indented parse tree
```

Now run it, passing command line arguments like this:

```sh
node Arithmetic "{1 + 2 * 3}"
```

The actual input that is parsed in this case is `1 + 2 * 3`, the curly braces are there just to indicate that the input is a literal rather than a file, and the double quotes serve for making it a single command line argument.

This results in the output of a lossless representation of the concrete parse tree, for the given input, in XML, to `process.stdout`.

```xml
<?xml version="1.0" encoding="UTF-8"?><Expression><Term><Factor><Primary><Number>1</Number></Primary></Factor></Term> <TOKEN>+</TOKEN> <Term><Factor><Primary><Number>2</Number></Primary></Factor> <TOKEN>*</TOKEN> <Factor><Primary><Number>3</Number></Primary></Factor></Term></Expression>
```

It is lossless in the sense that it contains every single character of the input as content, where the parse tree structure has been inserted as markup. When using XML tooling, taking the string value of the XML document would regain the original input.

For making it more readable, use the `-i` option to add extra whitespace and indentation:

```sh
node Arithmetic -i "{1 + 2 * 3}"
```

results in

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Expression>
  <Term>
    <Factor>
      <Primary>
        <Number>1</Number>
      </Primary>
    </Factor>
  </Term>
  <TOKEN>+</TOKEN>
  <Term>
    <Factor>
      <Primary>
        <Number>2</Number>
      </Primary>
    </Factor>
    <TOKEN>*</TOKEN>
    <Factor>
      <Primary>
        <Number>3</Number>
      </Primary>
    </Factor>
  </Term>
</Expression>
```

Note that this is the concrete parse tree, containing nodes for each and every derivation step that was taken during parsing. Usually many of those are not needed for further processing, so it often makes sense to condense the parse tree before applying any further transformations to it. In the actual case, a tree like the following could be sufficient:

```xml
<?xml version="1.0" encoding="UTF-8"?>
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

When looking at the generated TypeScript code, you will find this interface, that is used by parsing methods to communicate their operation:

```typescript
  export interface ParsingEventHandler
  {
    reset(source: string): void;
    startNonterminal(name: string, begin: number): void;
    endNonterminal(name: string, end: number): void;
    terminal(name: string, begin: number, end: number): void;
    whitespace(begin: number, end: number): void;
  }
```

Applications could implement and use a `ParsingEventHandler` for any processing of parsing events, e.g. building their own full or condensed parse trees. The generated code also contains a sample `ParsingEventHandler` implementation doing just that:

```typescript
  export class TopDownTreeBuilder implements ParsingEventHandler
  {
    ...
```

When command line options `-tree` and `-main` are used together, REx also generates

```typescript
class XmlSerializer implements Arithmetic.ParsingEventHandler
{
  ...
```

This is what was used to produce the XML representation of the parse tree, that was shown before.

## Step 5: Trace Lexer and Parser Execution

For debugging grammars, it is often useful to see the actions that the lexer and parser are performing during execution. When using the `-trace` command line option, REx will generate additional code that writes a log of actions, in XML, to `process.stderr`:

```sh
rex -typescript -main -trace Arithmetic.ebnf
tsc Arithmetic
node Arithmetic "{1 + 2 * 3}"
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<trace>
  <parse startnonterminal="Expression"/>
  <tokenize tokenset="1">
    <next state="2" offset="0" char="1" codepoint="49" class="7" result="Number"/>
    <next state="4" offset="1" char=" " codepoint="32" class="8"/>
    <done result="Number" begin="0" end="1"/>
  </tokenize>
  <parse startnonterminal="Term" input="Number"/>
  <parse startnonterminal="Factor" input="Number"/>
  <parse startnonterminal="Primary" input="Number"/>
  <parse terminal="Number"/>
  <parse endnonterminal="Primary"/>
  <parse endnonterminal="Factor"/>
  <tokenize tokenset="2">
    <next state="3" offset="1" char=" " codepoint="32" class="8" result="Whitespace"/>
    <next state="5" offset="2" char="+" codepoint="43" class="4"/>
    <done result="Whitespace" begin="1" end="2"/>
  </tokenize>
  <tokenize tokenset="2">
    <next state="3" offset="2" char="+" codepoint="43" class="4" result="'+'"/>
    <done result="'+'" begin="2" end="3"/>
  </tokenize>
  <parse endnonterminal="Term" input="'+'"/>
  <parse terminal="'+'"/>
  ...
```

The `parse` actions show how the parser makes its way through the grammar rules by entering and leaving the code that corresponds to the grammar nonterminals, or consuming terminals.

The `tokenize` actions show how the lexer assembles tokens from input characters.

Some details in this trace may be understandable only by looking at some internals of the parser, but the trace can by useful anyway because it documents the course of action. As trace output may become huge, it is a good idea to isolate a problem to as small as possible a reproduction, before using a trace to analyze it.

## Step 6: Annotate the Grammar with TypeScript code

Usually you do not want to just see the parse tree, but rather compile and execute the language that is being parsed. In case of the grammar for arithmetic expressions, this could be evaluating the expressions to their result.

While it is possible to do this evaluation based on a parse tree, it can also be done by omitting parse tree generation, and instead annotating the grammar with actions in TypeScript code, that will be triggered during parser execution. This is what we will be doing in this step.

We use two arrays as stacks for keeping track of operators and values while the parser works through the input:

```typescript
  let op: string[] = [];
  let val: number[] = [];
```

For achieving evaluation, we will augment the grammar with the following actions, whose implementation details will be shown later:

- `token = this.input.substring(this.b0, this.e0)`: get most recently consumed token
- `val.push(parseInt(token))`: push numeric value token onto the value stack,
- `op.push(operator)`: push an operator onto the operator stack,
- `op.pop()`: pop an operator off of the operator stack,
- `evaluate()`: pop an operator off the operator stack and evaluate it with one or more operands popped off the value stack, pushing the result onto the value stack.

For inserting an action in TypeScript into the EBNF grammar, it must be wrapped in a **processing instruction**, which

- begins with `<?` and a name,
- continues with some whitespace, and the actual TypeScript code,
- terminates with `?>`.

The TypeScript code of course must not contain the character sequence `?>`.

A grammar may contain multiple action sets using different names, and an action is only included into the generated code, if its name is selected using the `-a` command line option to specify the name. We will use `aee` as the name of our set of actions, as an acronym for *A*rithmetic *E*xpression *E*valuator. Thus command line option `-a aee` must be used, and actions inserted into the grammar will look like this: `<?aee evaluate();?>`.

The actions are positioned in the grammar as follows:

```
Expression ::= Term (('+'                   <?aee op.push('+');?>
                          | '-'             <?aee op.push('-');?>
                               ) Term       <?aee evaluate();?>
                                      )*
Term       ::= Factor (('*'                 <?aee op.push('*');?>
                            | '/'           <?aee op.push('/');?>
                                 ) Factor   <?aee evaluate();?>
                                         )*
Factor     ::=                              <?aee op.push(' ');?>
               ('+' | '-'                   <?aee
                                              op.pop();
                                              op.push('_');
                                            ?>
                          )? Primary        <?aee evaluate();?>
Primary    ::= Number                       <?aee
                                              var token = this.input.substring(this.b0, this.e0);
                                              val.push(parseInt(token));
                                            ?>
             | '(' Expression ')'
```

Actions may be placed anywhere on the right hand side of the syntax rules, and they will be executed when the parser's control flow passes by the respective position. Note that actions can only be placed in the syntax definition, but not in the lexical definition.

You are free in formatting the grammar as you like, but in the example above, actions have been aligned on the right hand side, in order to visually separate them from the pure grammar rules on the left hand side.

Now for actually declaring the data structures and implementing the methods used in our actions, we need to add some more TypeScript code:

```typescript
  let val: number[] = [];
  let op: string[] = [];

  function evaluate() {
    var rhs = val.pop();
    switch (op.pop()) {
      case "+": val.push(val.pop() + rhs); break;
      case "-": val.push(val.pop() - rhs); break;
      case "*": val.push(val.pop() * rhs); break;
      case "/": val.push(Math.floor(val.pop() / rhs)); break;
      case "_": val.push(- rhs); break;
      default: val.push(rhs);
    }
  }
```

Also we will supply our own main program, that takes a command line argument, passes it to the parser, and prints the result:

```typescript
  export function main() {
    var input: string = process.argv[2];
    var parser = new Arithmetic.Parser(input);
    try
    {
      parser.parse_Expression();
      console.log(val.pop());
    }
    catch (pe) {
      if (! (pe instanceof Arithmetic.ParseException)) {
        throw pe;
      }
      else {
        throw parser.getErrorMessage(pe);
      }
    }
  }
```

Both of this, the code implementing the actions and the main program can be added to the grammar file, for having REx include it into the generated code. Such extra code can be added

- at the very beginning of the grammar. In this case it must also contain the module declaration.
- at the end of the grammar, following an `<?ENCORE?>` indicator. Code placed here is placed by the end of the output file, at the end of the module declaration. In this case it must also contain the closing curly brace of the module declaration.

We will add our code at the end, such that the complete file `Arithmetic.ebnf` now looks as follows:

```
Expression ::= Term (('+'                   <?aee op.push('+');?>
                          | '-'             <?aee op.push('-');?>
                               ) Term       <?aee evaluate();?>
                                      )*
Term       ::= Factor (('*'                 <?aee op.push('*');?>
                            | '/'           <?aee op.push('/');?>
                                 ) Factor   <?aee evaluate();?>
                                         )*
Factor     ::=                              <?aee op.push(' ');?>
               ('+' | '-'                   <?aee
                                              op.pop();
                                              op.push('_');
                                            ?>
                          )? Primary        <?aee evaluate();?>
Primary    ::= Number                       <?aee
                                              var token = this.input.substring(this.b0, this.e0);
                                              val.push(parseInt(token));
                                            ?>
             | '(' Expression ')'

<?TOKENS?>

Number     ::= [0-9]+
Whitespace ::= [ #x9#xA]+
               /*ws: definition*/

<?ENCORE?>

<?aee
  let val: number[] = [];
  let op: string[] = [];

  function evaluate() {
    var rhs = val.pop();
    switch (op.pop()) {
      case "+": val.push(val.pop() + rhs); break;
      case "-": val.push(val.pop() - rhs); break;
      case "*": val.push(val.pop() * rhs); break;
      case "/": val.push(Math.floor(val.pop() / rhs)); break;
      case "_": val.push(- rhs); break;
      default: val.push(rhs);
    }
  }

  export function main() {
    var input: string = process.argv[2];
    var parser = new Arithmetic.Parser(input);
    try
    {
      parser.parse_Expression();
      console.log(val.pop());
    }
    catch (pe) {
      if (! (pe instanceof Arithmetic.ParseException)) {
        throw pe;
      }
      else {
        throw parser.getErrorMessage(pe);
      }
    }
  }
}

Arithmetic.main();
?>
```

REx will only insert our newly added actions into the generated code, when option `-a aee` is added to the REx command line. Without that, there would be no difference in behavior, compared to the plain grammar that was used before.

Generate a parser including the actions, and compile it, using these commands:

```sh
rex -typescript -a aee Arithmetic.ebnf
tsc Arithmetic
```

Now it can be run to actually evaluate arithmetic expressions specified in the first command line argument, e.g.

```sh
node Arithmetic "( 42 * 17 + 6 ) / 8 - -9"
```

&nbsp;
---
[⇦ Previous page](quickstart-scala.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-xquery.md)