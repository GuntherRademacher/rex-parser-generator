<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](quickstart-cpp.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-go.md)

&nbsp;
# Quick Start Guide for Generating and Running a Parser in C# with REx

This tutorial will guide you through creating and running a parser in C# for a simple arithmetic expression grammar using REx. It will also show how to visualize parse trees, trace parser operation, and spotlight some properties of the generated code. Finally it will show how to annotate the grammar with target language code in order to process the parser's input at runtime.

## Prerequisites

A C# compiler will be need, e.g. Microsoft Visual C#, or Mono C#. Ensure you have one installed on your machine, and if not installed, download and install it.

In the examples below, we will use the `csc` command to invoke the Microsoft Visual C# compiler.

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
rex -csharp -main -tree Arithmetic.ebnf
```

This command line asks REx for

  - a parser and lexer in C# (`-csharp`),
  - a simple main program for it (`-main`),
  - code generation for parse tree production (`-tree`),
  - using the grammar in file `Arithmetic.ebnf`.

The result will be a C# file named `Arithmetic.cs` in the current directory, containing the generated code.

The command line is used to specify the generator's options. With the above command, we have chosen the default LL parsing algorithm, which would have been specified as `-ll 3` explicitly (the grammar being LL(1), though). In case an LR parser is preferred, `-lalr 1` could have been used as an alternative here.

## Step 3: Compile the Generated Code

The generated file is self-contained, i.e. it has in it everything that is needed and does not have any additional  requirement, besides the standard C# runtime libraries, of course. So just compile it with the C# compiler:

```sh
csc Arithmetic.cs
```

## Step 4: Run the Generated Code

You are now in a position to run the generated code. At this point it can be used to dump the parse tree in XML while parsing any input - this is the functionality of the main program that was generated in response to REx option `-main`.

Running it without any command line arguments,

```sh
Arithmetic
```
(on Linux or macOS, prepending `./` to the command)

shows the usage text:

```
Usage: Arithmetic [-i] INPUT...

  parse INPUT, which is either a filename or literal text enclosed in curly braces

  Option:
    -i     indented parse tree
```

Now run the generated class, passing command line arguments like this:

```sh
Arithmetic "{1 + 2 * 3}"
```
(on Linux or macOS, prepend `./` to the command).

The actual input that is parsed in this case is `1 + 2 * 3`, the curly braces are there just to indicate that the input is a literal rather than a file, and the double quotes serve for making it a single command line argument.

This results in the output of a lossless representation of the concrete parse tree, for the given input, in XML, to `System.out`.

```xml
<?xml version="1.0" encoding="UTF-8"?><Expression><Term><Factor><Primary><Number>1</Number></Primary></Factor></Term> <TOKEN>+</TOKEN> <Term><Factor><Primary><Number>2</Number></Primary></Factor> <TOKEN>*</TOKEN> <Factor><Primary><Number>3</Number></Primary></Factor></Term></Expression>
```

It is lossless in the sense that it contains every single character of the input as content, where the parse tree structure has been inserted as markup. When using XML tooling, taking the string value of the XML document would regain the original input.

For making it more readable, use the `-i` option to add extra whitespace and indentation:

```sh
Arithmetic -i "{1 + 2 * 3}"
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

When looking at the generated C# code, you will find this interface, that is used by parsing methods to communicate their operation:

```c#
  public interface EventHandler
  {
    void reset(String s);
    void startNonterminal(String name, int begin);
    void endNonterminal(String name, int end);
    void terminal(String name, int begin, int end);
    void whitespace(int begin, int end);
  }
```

Applications could implement and use an `EventHandler` for any processing of parsing events, e.g. building their own full or condensed parse trees. The generated code also contains a sample `EventHandler` implementation doing just that:

```c#
  public class TopDownTreeBuilder : EventHandler
  {
    ...
```

When command line options `-tree` and `-main` are used together, REx also generates

```c#
  public class XmlSerializer : EventHandler
  {
    ...
```

This is what was used to produce the XML representation of the parse tree, that was shown before.

## Step 5: Trace Lexer and Parser Execution

For debugging grammars, it is often useful to see the actions that the lexer and parser are performing during execution. When using the `-trace` command line option, REx will generate additional code that writes a log of actions, in XML, to `System.err`:

```sh
rex -csharp -main -trace Arithmetic.ebnf
csc Arithmetic.cs
Arithmetic "{1 + 2 * 3}"
```
(on Linux or macOS, prepend `./` to the command).

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

## Step 6: Annotate the Grammar with C# code

Usually you do not want to just see the parse tree, but rather compile and execute the language that is being parsed. In case of the grammar for arithmetic expressions, this could be evaluating the expressions to their result.

While it is possible to do this evaluation based on a parse tree, it can also be done by omitting parse tree generation, and instead annotating the grammar with actions in C# code, that will be triggered during parser execution. This is what we will be doing in this step.

We use two stacks for keeping track of operators and values while the parser works through the input:

```c#
  private Stack<char> op = new Stack<char>(); // operator stack
  private Stack<int> val = new Stack<int>();  // value stack
```

For achieving evaluation, we will augment the grammar with the following actions, whose implementation details will be shown later:

- `number()`: calculate numeric value of most recently consumed token,
- `val.Push(number)`: push a number onto the value stack,
- `op.Push(operator)`: push an operator onto the operator stack,
- `evaluate()`: pop an operator off the operator stack and evaluate it with one or more operands popped off the value stack, pushing the result onto the value stack.

For inserting an action in C# into the EBNF grammar, it must be wrapped in a **processing instruction**, which

- begins with `<?` and a name,
- continues with some whitespace, and the actual C# code,
- terminates with `?>`.

The C# code of course must not contain the character sequence `?>`.

A grammar may contain multiple action sets using different names, and an action is only included into the generated code, if its name is selected using the `-a` command line option to specify the name. We will use `aee` as the name of our set of actions, as an acronym for *A*rithmetic *E*xpression *E*valuator. Thus command line option `-a aee` must be used, and actions inserted into the grammar will look like this: `<?aee val.push(number());?>`.

The actions are positioned in the grammar as follows:

```
Expression ::= Term (('+'                   <?aee op.Push('+');?>
                          | '-'             <?aee op.Push('-');?>
                               ) Term       <?aee evaluate();?>
                                      )*
Term       ::= Factor (('*'                 <?aee op.Push('*');?>
                            | '/'           <?aee op.Push('/');?>
                                 ) Factor   <?aee evaluate();?>
                                         )*
Factor     ::=                              <?aee op.Push(' ');?>
               ('+' | '-'                   <?aee
                                              op.Pop();
                                              op.Push('_');
                                            ?>
                          )? Primary        <?aee evaluate();?>
Primary    ::= Number                       <?aee val.Push(number());?>
             | '(' Expression ')'
```

Actions may be placed anywhere on the right hand side of the syntax rules, and they will be executed when the parser's control flow passes by the respective position. Note that actions can only be placed in the syntax definition, but not in the lexical definition.

You are free in formatting the grammar as you like, but in the example above, actions have been aligned on the right hand side, in order to visually separate them from the pure grammar rules on the left hand side.

Now for actually declaring the data structures and implementing the methods used in our actions, we need to add some more C# code:

```c#
  private Stack<char> op = new Stack<char>(); // operator stack
  private Stack<int> val = new Stack<int>();  // value stack

  private int number() {
    String token = input.Substring(b0, e0 - b0);
    return int.Parse(token);
  }

  private void evaluate() {
    int rhs = val.Pop();
    switch (op.Pop()) {
    case '+': val.Push(val.Pop() + rhs); break;
    case '-': val.Push(val.Pop() - rhs); break;
    case '*': val.Push(val.Pop() * rhs); break;
    case '/': val.Push(val.Pop() / rhs); break;
    case '_': val.Push(- rhs); break;
    default: val.Push(rhs); break;
    }
  }
```

Also we will supply our own main program, that takes a command line argument, passes it to the parser, and prints the result:

```c#
  public static int Main(string[] args) {
    String input = args[0];
    Arithmetic parser = new Arithmetic(input);
    try {
      parser.parse_Expression();
      Console.WriteLine(parser.val.Pop());
    }
    catch (ParseException pe) {
      Console.Error.WriteLine("ParseException while processing "
          + input + ":\n" + parser.getErrorMessage(pe));
      return 1;
    }
    return 0;
  }
```

Both of this, the code implementing the actions and the main program can be added to the grammar file, for having REx include it into the generated code. Such extra code can be added

- at the very beginning of the grammar. In this case it must also contain any necessary `using` directives, the `class` declaration, and any constructors, which usually must call `initialize(String input)`.
- at the end of the grammar, following an `<?ENCORE?>` indicator. When added at the end, it must also contain the curly brace `}` that closes the C# class.

We will add our code at the beginning, such that the complete file `Arithmetic.ebnf` now looks as follows:

```
<?aee
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

public class Arithmetic {

  public Arithmetic(String s) {
    initialize(s);
  }

  private Stack<char> op = new Stack<char>(); // operator stack
  private Stack<int> val = new Stack<int>();  // value stack

  private int number() {
    String token = input.Substring(b0, e0 - b0);
    return int.Parse(token);
  }

  private void evaluate() {
    int rhs = val.Pop();
    switch (op.Pop()) {
    case '+': val.Push(val.Pop() + rhs); break;
    case '-': val.Push(val.Pop() - rhs); break;
    case '*': val.Push(val.Pop() * rhs); break;
    case '/': val.Push(val.Pop() / rhs); break;
    case '_': val.Push(- rhs); break;
    default: val.Push(rhs); break;
    }
  }

  public static int Main(string[] args) {
    String input = args[0];
    Arithmetic parser = new Arithmetic(input);
    try {
      parser.parse_Expression();
      Console.WriteLine(parser.val.Pop());
    }
    catch (ParseException pe) {
      Console.Error.WriteLine("ParseException while processing "
          + input + ":\n" + parser.getErrorMessage(pe));
      return 1;
    }
    return 0;
  }
?>

Expression ::= Term (('+'                   <?aee op.Push('+');?>
                          | '-'             <?aee op.Push('-');?>
                               ) Term       <?aee evaluate();?>
                                      )*
Term       ::= Factor (('*'                 <?aee op.Push('*');?>
                            | '/'           <?aee op.Push('/');?>
                                 ) Factor   <?aee evaluate();?>
                                         )*
Factor     ::=                              <?aee op.Push(' ');?>
               ('+' | '-'                   <?aee
                                              op.Pop();
                                              op.Push('_');
                                            ?>
                          )? Primary        <?aee evaluate();?>
Primary    ::= Number                       <?aee val.Push(number());?>
             | '(' Expression ')'

<?TOKENS?>

Number     ::= [0-9]+
Whitespace ::= [ #x9#xA]+
               /*ws: definition*/
```

For knowing the `using` directives, required by the generated code, that had to be inserted above, we could have generated it once without adding our code,

```sh
rex -csharp Arithmetic.ebnf
```

The `using` directives can then be grabbed from `Arithmetic.cs` and augmented with those required by our custom code.

For having REx insert our newly added actions into the generated code, option `-a aee` must be added to the REx command line. Without that, there would be no difference in behavior, compared to the plain grammar that was used before.

Generate a parser including the actions, and compile it, using these commands:

```sh
rex -csharp -a aee Arithmetic.ebnf
csc Arithmetic.cs
```

Now it can be run to actually evaluate arithmetic expressions specified in the first command line argument, e.g.

```sh
Arithmetic "( 42 * 17 + 6 ) / 8 - -9"
```
(on Linux or macOS, prepend `./` to the command).

&nbsp;
---
[⇦ Previous page](quickstart-cpp.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-go.md)