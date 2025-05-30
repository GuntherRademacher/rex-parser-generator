<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](quickstart-haxe.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-javascript.md)

&nbsp;
# Quick Start Guide for Generating and Running a Parser in Java with REx

This tutorial will guide you through creating and running a parser in Java for a simple arithmetic expression grammar using REx. It will also show how to visualize parse trees, trace parser operation, and spotlight some properties of the generated code. Finally it will show how to annotate the grammar with target language code in order to process the parser's input at runtime.

## Prerequisites

A Java compiler will be used, so a **Java Development Kit (JDK)** is needed. Ensure you have a JDK installed on your machine, and if not installed, download a JDK and install it.

These days REx generated parsers are tested with Java 17 and higher. They should work with newer versions, and they may or may not work with older versions. In any case it may be worth a try, if necessary.

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
rex -java -main -tree Arithmetic.ebnf
```

This command line asks REx for

  - a parser and lexer in Java (`-java`),
  - a simple main program for it (`-main`),
  - code generation for parse tree production (`-tree`),
  - using the grammar in file `Arithmetic.ebnf`.

The result will be a Java file named `Arithmetic.java` in the current directory, containing the generated code.

The command line is used to specify the generator's options. With the above command, we have chosen the default LL parsing algorithm, which would have been specified as `-ll 3` explicitly (the grammar being LL(1), though). In case an LR parser is preferred, `-lalr 1` could have been used as an alternative here.

## Step 3: Compile the Generated Code

The generated file is self-contained, i.e. it has in it everything that is needed and does not have any additional classpath requirement, besides the standard Java runtime libraries, of course. So just compile it with the Java compiler:

```sh
javac Arithmetic.java
```

## Step 4: Run the Generated Code

You are now in a position to run the generated code. At this point it can be used to dump the parse tree in XML while parsing any input - this is the functionality of the main program that was generated in response to REx option `-main`.

Running it without any command line arguments,

```sh
java Arithmetic
```

shows the usage text:

```
Usage: java Arithmetic [-i] INPUT...

  parse INPUT, which is either a filename or literal text enclosed in curly braces

  Option:
    -i     indented parse tree
```

Now run the generated class, passing command line arguments like this:

```sh
java Arithmetic "{1 + 2 * 3}"
```

The actual input that is parsed in this case is `1 + 2 * 3`, the curly braces are there just to indicate that the input is a literal rather than a file, and the double quotes serve for making it a single command line argument.

This results in the output of a lossless representation of the concrete parse tree, for the given input, in XML, to `System.out`.

```xml
<?xml version="1.0" encoding="UTF-8"?><Expression><Term><Factor><Primary><Number>1</Number></Primary></Factor></Term> <TOKEN>+</TOKEN> <Term><Factor><Primary><Number>2</Number></Primary></Factor> <TOKEN>*</TOKEN> <Factor><Primary><Number>3</Number></Primary></Factor></Term></Expression>
```

It is lossless in the sense that it contains every single character of the input as content, where the parse tree structure has been inserted as markup. When using XML tooling, taking the string value of the XML document would regain the original input.

For making it more readable, use the `-i` option to add extra whitespace and indentation:

```sh
java Arithmetic -i "{1 + 2 * 3}"
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

When looking at the generated Java code, you will find this interface, that is used by parsing methods to communicate their operation:

```java
  public interface EventHandler
  {
    public void reset(CharSequence string);
    public void startNonterminal(String name, int begin);
    public void endNonterminal(String name, int end);
    public void terminal(String name, int begin, int end);
    public void whitespace(int begin, int end);
  }
```

Applications could implement and use an `EventHandler` for any processing of parsing events, e.g. building their own full or condensed parse trees. The generated code also contains a sample `EventHandler` implementation doing just that:

```java
  public static class TopDownTreeBuilder implements EventHandler
  {
    ...
```

When command line options `-tree` and `-main` are used together, REx also generates

```java
  public static class XmlSerializer implements EventHandler
  {
    ...
```

This is what was used to produce the XML representation of the parse tree, that was shown before.

## Step 5: Trace Lexer and Parser Execution

For debugging grammars, it is often useful to see the actions that the lexer and parser are performing during execution. When using the `-trace` command line option, REx will generate additional code that writes a log of actions, in XML, to `System.err`:

```sh
rex -java -main -trace Arithmetic.ebnf
javac Arithmetic.java
java Arithmetic "{1 + 2 * 3}"
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

## Step 6: Annotate the Grammar with Java code

Usually you do not want to just see the parse tree, but rather compile and execute the language that is being parsed. In case of the grammar for arithmetic expressions, this could be evaluating the expressions to their result.

While it is possible to do this evaluation based on a parse tree, it can also be done by omitting parse tree generation, and instead annotating the grammar with actions in Java code, that will be triggered during parser execution. This is what we will be doing in this step.

We use two stacks for keeping track of operators and values while the parser works through the input:

```java
    private Stack<Character> op = new Stack<>(); // operator stack
    private Stack<Integer> val = new Stack<>();  // value stack
```

For achieving evaluation, we will augment the grammar with the following actions, whose implementation details will be shown later:

- `number()`: calculate numeric value of most recently consumed token,
- `val.push(number)`: push a number onto the value stack,
- `op.push(operator)`: push an operator onto the operator stack,
- `evaluate()`: pop an operator off the operator stack and evaluate it with one or more operands popped off the value stack, pushing the result onto the value stack.

For inserting an action in Java into the EBNF grammar, it must be wrapped in a **processing instruction**, which

- begins with `<?` and a name,
- continues with some whitespace, and the actual Java code,
- terminates with `?>`.

The Java code of course must not contain the character sequence `?>`.

A grammar may contain multiple action sets using different names, and an action is only included into the generated code, if its name is selected using the `-a` command line option to specify the name. We will use `aee` as the name of our set of actions, as an acronym for *A*rithmetic *E*xpression *E*valuator. Thus command line option `-a aee` must be used, and actions inserted into the grammar will look like this: `<?aee val.push(number());?>`.

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
Primary    ::= Number                       <?aee val.push(number());?>
             | '(' Expression ')'
```

Actions may be placed anywhere on the right hand side of the syntax rules, and they will be executed when the parser's control flow passes by the respective position. Note that actions can only be placed in the syntax definition, but not in the lexical definition.

You are free in formatting the grammar as you like, but in the example above, actions have been aligned on the right hand side, in order to visually separate them from the pure grammar rules on the left hand side.

Now for actually declaring the data structures and implementing the methods used in our actions, we need to add some more Java code:

```java
    private Stack<Character> op = new Stack<>(); // operator stack
    private Stack<Integer> val = new Stack<>();  // value stack

    private void evaluate() {
      int rhs = val.pop();
      switch (op.pop()) {
      case '+': val.push(val.pop() + rhs); break;
      case '-': val.push(val.pop() - rhs); break;
      case '*': val.push(val.pop() * rhs); break;
      case '/': val.push(val.pop() / rhs); break;
      case '_': val.push(- rhs); break;
      default: val.push(rhs);
      }
    }

    private int number() {
      String tokenValue = input.subSequence(b0, e0).toString();
      return Integer.valueOf(tokenValue);
    }
```

Also we will supply our own main program, that takes a command line argument, passes it to the parser, and prints the result:

```java
  public static void main(String[] args) {
    Arithmetic parser = new Arithmetic();
    parser.initialize(args[0]);
    try {
      parser.parse_Expression();
      System.out.println(parser.val.pop());
    }
    catch (ParseException e) {
      throw new RuntimeException(parser.getErrorMessage(e), e);
    }
  }
```

Both of this, the code implementing the actions and the main program can be added to the grammar file, for having REx include it into the generated code. Such extra code can be added

- at the very beginning of the grammar. In this case it must also contain any necessary `import` directives, the `class` declaration, and any constructors, which usually must call `initialize(Charsequence input)`.
- at the end of the grammar, following an `<?ENCORE?>` indicator. When added at the end, it must also contain the curly brace `}` that closes the Java class.

We will add our code at the beginning, such that the complete file `Arithmetic.ebnf` now looks as follows:

```
<?aee
  import java.util.Arrays;
  import java.util.Stack;

  public class Arithmetic {
    private Stack<Character> op = new Stack<>(); // operator stack
    private Stack<Integer> val = new Stack<>();  // value stack

    public static void main(String[] args) {
      Arithmetic parser = new Arithmetic();
      parser.initialize(args[0]);
      try {
        parser.parse_Expression();
        System.out.println(parser.val.pop());
      }
      catch (ParseException e) {
        throw new RuntimeException(parser.getErrorMessage(e), e);
      }
    }

    private void evaluate() {
      int rhs = val.pop();
      switch (op.pop()) {
      case '+': val.push(val.pop() + rhs); break;
      case '-': val.push(val.pop() - rhs); break;
      case '*': val.push(val.pop() * rhs); break;
      case '/': val.push(val.pop() / rhs); break;
      case '_': val.push(- rhs); break;
      default: val.push(rhs);
      }
    }

    private int number() {
      String tokenValue = input.subSequence(b0, e0).toString();
      return Integer.valueOf(tokenValue);
    }
?>

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
Primary    ::= Number                       <?aee val.push(number());?>
             | '(' Expression ')'

<?TOKENS?>

Number     ::= [0-9]+
Whitespace ::= [ #x9#xA]+
               /*ws: definition*/
```

For knowing the `import` directives, required by the generated code, that had to be inserted above, we could have generated it once without adding our code,

```sh
rex -java Arithmetic.ebnf
```

The `import` directives can then be grabbed from `Arithmetic.java` and augmented with those required by our custom code.

For having REx insert our newly added actions into the generated code, option `-a aee` must be added to the REx command line. Without that, there would be no difference in behavior, compared to the plain grammar that was used before.

Generate a parser including the actions, and compile it, using these commands:

```sh
rex -java -a aee Arithmetic.ebnf
javac Arithmetic.java
```

Now it can be run to actually evaluate arithmetic expressions specified in the first command line argument, e.g.

```sh
java Arithmetic "( 42 * 17 + 6 ) / 8 - -9"
```

&nbsp;
---
[⇦ Previous page](quickstart-haxe.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-javascript.md)