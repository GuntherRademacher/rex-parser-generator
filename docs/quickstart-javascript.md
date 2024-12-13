<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](quickstart-java.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-python.md)

&nbsp;
# Quick Start Guide for Generating and Running a Parser in JavaScript with REx

This tutorial will guide you through creating and running a parser in JavaScript for a simple arithmetic expression grammar using REx. It will also demonstrate how to visualize parse trees, trace parser operations, and highlight some key properties of the generated code. Finally, it will show you how to annotate the grammar with target language code to process the parser's input at runtime.

## Prerequisites

In this tutorial, we will use the Node.js runtime environment for executing JavaScript from a command line. Make sure that you have Node.js installed.

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
rex -javascript -main -tree Arithmetic.ebnf
```

This command line asks REx for

  - a parser and lexer in JavaScript (`-javascript`),
  - a simple main program for it (`-main`),
  - code generation for parse tree production (`-tree`),
  - using the grammar in file `Arithmetic.ebnf`.

The result will be a JavaScript file named `Arithmetic.js` in the current directory, containing the generated code.

The command line is used to specify the generator's options. With the above command, we have chosen the default LL parsing algorithm, which would have been specified as `-ll 3` explicitly (the grammar being LL(1), though). In case an LR parser is preferred, `-lalr 1` could have been used as an alternative here.

## Step 3: Run the Generated Code

You are now in a position to run the generated code. At this point it can be used to dump the parse tree in XML while parsing any input - this is the functionality of the main program that was generated in response to REx option `-main`.

The generated file is self-contained, i.e. it has in it everything that is needed and does not need anything to be added. So just run it with this command:

```sh
node Arithmetic
```

Without any command line arguments, it shows the usage text:

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

In the generated JavaScript code, the parser is implemented by function `Arithmetic`:

```javascript
function Arithmetic(string, parsingEventHandler)
{
   ...
```

It takes a string containing the input, and an `EventHandler`, that is used by parsing methods to communicate their operation. This is the interface:

```javascript
/**
 * @interface EventHandler
 * @description Interface for handling parsing events.
 *
 * @property {function(string): void} reset
 *   @param (string) input
 *
 * @property {function(string, number): void} startNonterminal
 *   @param {string} name - The name of the nonterminal.
 *   @param {number} begin - The start offset of the nonterminal.
 *
 * @property {function(string, number): void} endNonterminal
 *   @param {string} name - The name of the nonterminal.
 *   @param {number} end - The end offset of the nonterminal.
 *
 * @property {function(string, number, number): void} terminal
 *   @param {string} name - The name of the terminal.
 *   @param {number} begin - The start offset of the terminal.
 *   @param {number} end - The end offset of the terminal.
 *
 * @property {function(number, number): void} whitespace
 *   @param {number} begin - The start offset of the whitespace.
 *   @param {number} end - The end offset of the whitespace.
 */
```

All of the number arguments are offsets into the input string, which point to the begin, or behind the end of a nonterminal, terminal, or whitespace.

Applications could implement and use an `EventHandler` for any processing of parsing events, e.g. building their own full or condensed parse trees. The generated code also contains a sample `EventHandler` implementation doing just that:

```javascript
Arithmetic.TopDownTreeBuilder = function()
{
  ...
```

When command line options `-tree` and `-main` are used together, REx also generates

```javascript
Arithmetic.XmlSerializer = function(log, indent)
{
  ...
```

This is what was used to produce the XML representation of the parse tree, that was shown before.

## Step 4: Trace Lexer and Parser Execution

For debugging grammars, it is often useful to see the actions that the lexer and parser are performing during execution. When using the `-trace` command line option, REx will generate additional code that writes a log of actions, in XML, to `process.stderr`:

```sh
rex -javascript -main -trace Arithmetic.ebnf
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

## Step 5: Annotate the Grammar with JavaScript code

Usually you do not want to just see the parse tree, but rather compile and execute the language that is being parsed. In case of the grammar for arithmetic expressions, this could be evaluating the expressions to their result.

While it is possible to do this evaluation based on a parse tree, it can also be done by omitting parse tree generation, and instead annotating the grammar with actions in JavaScript code, that will be triggered during parser execution. This is what we will be doing in this step.

We use a stack for keeping track of operators and values while the parser works through the input:

```javascript
  this.stack = [];
```

We will add that below on top level of the generated function. The code that we will add later will be placed in nested functions. We will then refer to the stack as `thisParser.stack`.

For achieving evaluation, we will augment the grammar with the following actions, whose implementation details will be shown later:

- `number()`: calculate numeric value of most recently consumed token,
- `thisParser.stack.push(number)`: push a number onto the stack,
- `thisParser.stack.push(operator)`: push an operator onto the stack,
- `thisParser.stack.pop()`: pop an item off of the stack,
- `evaluate()`: pop an operand and an operator off the stack and evaluate it with possibly one more operand popped off the stack, pushing the result onto the stack.

For inserting an action in JavaScript into the EBNF grammar, it must be wrapped in a **processing instruction**, which

- begins with `<?` and a name,
- continues with some whitespace, and the actual JavaScript code,
- terminates with `?>`.

The JavaScript code of course must not contain the character sequence `?>`.

A grammar may contain multiple action sets using different names, and an action is only included into the generated code, if its name is selected using the `-a` command line option to specify the name. We will use `aee` as the name of our set of actions, as an acronym for *A*rithmetic *E*xpression *E*valuator. Thus command line option `-a aee` must be used, and actions inserted into the grammar will look like this: `<?aee thisParser.stack.push(number());?>`.

The actions are positioned in the grammar as follows:

```
Expression ::= Term (('+'                   <?aee thisParser.stack.push('+');?>
                          | '-'             <?aee thisParser.stack.push('-');?>
                               ) Term       <?aee evaluate();?>
                                      )*
Term       ::= Factor (('*'                 <?aee thisParser.stack.push('*');?>
                            | '/'           <?aee thisParser.stack.push('/');?>
                                 ) Factor   <?aee evaluate();?>
                                         )*
Factor     ::=                              <?aee thisParser.stack.push(' ');?>
               ('+' | '-'                   <?aee
                                              thisParser.stack.pop();
                                              thisParser.stack.push('_');
                                            ?>
                          )? Primary        <?aee evaluate();?>
Primary    ::= Number                       <?aee thisParser.stack.push(number());?>
             | '(' Expression ')'
```

Actions may be placed anywhere on the right hand side of the syntax rules, and they will be executed when the parser's control flow passes by the respective position. Note that actions can only be placed in the syntax definition, but not in the lexical definition.

You are free in formatting the grammar as you like, but in the example above, actions have been aligned on the right hand side, in order to visually separate them from the pure grammar rules on the left hand side.

Now for actually declaring the data structures and implementing the methods used in our actions, we need to add some more JavaScript code:

```javascript
  this.stack = [];

  function number() {
    return parseInt(input.substring(b0, e0));
  }

  function evaluate() {
    var stack = thisParser.stack;
    var rhs = stack.pop();
    switch (stack.pop()) {
      case "+": stack.push(stack.pop() + rhs); break;
      case "-": stack.push(stack.pop() - rhs); break;
      case "*": stack.push(stack.pop() * rhs); break;
      case "/": stack.push(Math.floor(stack.pop() / rhs)); break;
      case "_": stack.push(- rhs); break;
      default: stack.push(rhs);
    }
  }
```

Also we will supply our own main program, that takes a command line argument, passes it to the parser, and prints the result:

```javascript
var arguments = process.argv.slice(2);
var input = String(arguments[0]);
var parser = new Arithmetic(input);
try {
  parser.parse_Expression();
  console.log(parser.stack.pop());
}
catch (pe) {
  if (! (pe instanceof parser.ParseException)) {
    throw pe;
  }
  else {
    throw parser.getErrorMessage(pe);
  }
}
```

Both of this, the code implementing the actions and the main program can be added to the grammar file, for having REx include it into the generated code. Such extra code can be added

- at the very beginning of the grammar. In this case it must also contain the function declaration and a call to  `init(string)`.
- at the end of the grammar, following an `<?ENCORE?>` indicator. Code placed here is just appended to the output file, following the declaration of the parser function.

We will add our utility code at the beginning, and the main program at the end, such that the complete file `Arithmetic.ebnf` now looks as follows:

```
<?aee
function Arithmetic(string)
{
  init(string);

  this.stack = [];

  function number() {
    return parseInt(input.substring(b0, e0));
  }

  function evaluate() {
    var stack = thisParser.stack;
    var rhs = stack.pop();
    switch (stack.pop()) {
      case "+": stack.push(stack.pop() + rhs); break;
      case "-": stack.push(stack.pop() - rhs); break;
      case "*": stack.push(stack.pop() * rhs); break;
      case "/": stack.push(Math.floor(stack.pop() / rhs)); break;
      case "_": stack.push(- rhs); break;
      default: stack.push(rhs);
    }
  }
?>

Expression ::= Term (('+'                   <?aee thisParser.stack.push('+');?>
                          | '-'             <?aee thisParser.stack.push('-');?>
                               ) Term       <?aee evaluate();?>
                                      )*
Term       ::= Factor (('*'                 <?aee thisParser.stack.push('*');?>
                            | '/'           <?aee thisParser.stack.push('/');?>
                                 ) Factor   <?aee evaluate();?>
                                         )*
Factor     ::=                              <?aee thisParser.stack.push(' ');?>
               ('+' | '-'                   <?aee
                                              thisParser.stack.pop();
                                              thisParser.stack.push('_');
                                            ?>
                          )? Primary        <?aee evaluate();?>
Primary    ::= Number                       <?aee thisParser.stack.push(number());?>
             | '(' Expression ')'

<?TOKENS?>

Number     ::= [0-9]+
Whitespace ::= [ #x9#xA]+
               /*ws: definition*/

<?ENCORE?>

<?aee
var arguments = process.argv.slice(2);
var input = String(arguments[0]);
var parser = new Arithmetic(input);
try {
  parser.parse_Expression();
  console.log(parser.stack.pop());
}
catch (pe) {
  if (! (pe instanceof parser.ParseException)) {
    throw pe;
  }
  else {
    throw parser.getErrorMessage(pe);
  }
}
?>
```

REx will insert our newly added actions into the generated code, when option `-a aee` is added to the REx command line. Without that, there would be no difference in behavior, compared to the plain grammar that was used before.

Generate a parser including the actions, and compile it, using this command:

```sh
rex -javascript -a aee Arithmetic.ebnf
```

Now it can be run to actually evaluate arithmetic expressions specified in the first command line argument, e.g.

```sh
node Arithmetic "( 42 * 17 + 6 ) / 8 - -9"
```

&nbsp;
---
[⇦ Previous page](quickstart-java.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-python.md)