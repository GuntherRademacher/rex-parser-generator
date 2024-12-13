<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](quickstart-javascript.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-scala.md)

&nbsp;
# Quick Start Guide for Generating and Running a Parser in Python with REx

This tutorial will guide you through creating and running a parser in Python for a simple arithmetic expression grammar using REx. It will also show how to visualize parse trees, trace parser operation, and spotlight some properties of the generated code. Finally it will show how to annotate the grammar with target language code in order to process the parser's input at runtime.

## Prerequisites

A Python 3 interpreter will be used, so a Python 3 installation is needed. Ensure that it is available on your machine, and if not installed, download and install it.

The examples in this tutotial were tested with Python 3.12.7.

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
rex -python -main -tree Arithmetic.ebnf
```

This command line asks REx for

  - a parser and lexer in Python (`-python`),
  - a simple main program for it (`-main`),
  - code generation for parse tree production (`-tree`),
  - using the grammar in file `Arithmetic.ebnf`.

The result will be a Python file named `Arithmetic.py` in the current directory, containing the generated code.

The command line is used to specify the generator's options. With the above command, we have chosen the default LL parsing algorithm, which would have been specified as `-ll 3` explicitly (the grammar being LL(1), though). In case an LR parser is preferred, `-lalr 1` could have been used as an alternative here.

## Step 3: Compile the Generated Code

The generated file is self-contained, i.e. it has in it everything that is needed and does not have any additional classpath requirement, besides the standard Python runtime libraries, of course.

So you are now in a position to run the generated code. At this point it can be used to dump the parse tree in XML while parsing any input - this is the functionality of the main program that was generated in response to REx option `-main`.

Running it without any command line arguments,

```sh
python3 Arithmetic.py
```

shows the usage text:

```
Usage: python Arithmetic.py [-i] INPUT...

  parse INPUT, which is either a filename or literal text enclosed in curly braces

  Option:
    -i     indented parse tree
```

Now run the generated class, passing command line arguments like this:

```sh
python3 Arithmetic.py "{1 + 2 * 3}"
```

The actual input that is parsed in this case is `1 + 2 * 3`, the curly braces are there just to indicate that the input is a literal rather than a file, and the double quotes serve for making it a single command line argument.

This results in the output of a lossless representation of the concrete parse tree, for the given input, in XML, to `System.out`.

```xml
<?xml version="1.0" encoding="UTF-8"?><Expression><Term><Factor><Primary><Number>1</Number></Primary></Factor></Term> <TOKEN>+</TOKEN> <Term><Factor><Primary><Number>2</Number></Primary></Factor> <TOKEN>*</TOKEN> <Factor><Primary><Number>3</Number></Primary></Factor></Term></Expression>
```

It is lossless in the sense that it contains every single character of the input as content, where the parse tree structure has been inserted as markup. When using XML tooling, taking the string value of the XML document would regain the original input.

For making it more readable, use the `-i` option to add extra whitespace and indentation:

```sh
python3 Arithmetic.py -i "{1 + 2 * 3}"
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

When looking at the generated Python code, you will find that parsing methods communicate their operation over an "Event Handler" interface. There is no abstract base class for it, so it is not obvious in the code, but it consists of these methods:

 - `reset(self, string: str)`
 - `start_nonterminal(self, name: str, begin: int)`
 - `end_nonterminal(self, name: str, end: int)`
 - `terminal(self, name: str, begin: int, end: int)`
 - `whitespace(self, begin: int, end: int)`

Applications could implement and use an "Event Handler" for any processing of parsing events, e.g. building their own full or condensed parse trees. The generated code also contains a sample "Event Handler" implementation doing just that:

```python
  class TopDownTreeBuilder:

    def reset(self, inputString):
    ...
```

When command line options `-tree` and `-main` are used together, REx also generates this "Event Handler":

```python
  class XmlSerializer:

    def reset(self, inputString):
    ...
```

This is what was used to produce the XML representation of the parse tree, that was shown before.

## Step 4: Trace Lexer and Parser Execution

For debugging grammars, it is often useful to see the actions that the lexer and parser are performing during execution. When using the `-trace` command line option, REx will generate additional code that writes a log of actions, in XML, to `sys.stderr`:

```sh
rex -python -main -trace Arithmetic.ebnf
python Arithmetic.py "{1 + 2 * 3}"
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

## Step 5: Annotate the Grammar with Python code

Usually you do not want to just see the parse tree, but rather compile and execute the language that is being parsed. In case of the grammar for arithmetic expressions, this could be evaluating the expressions to their result.

While it is possible to do this evaluation based on a parse tree, it can also be done by omitting parse tree generation, and instead annotating the grammar with actions in Python code, that will be triggered during parser execution. This is what we will be doing in this step.

We use two stacks for keeping track of operators and values while the parser works through the input:

```python
op = []   # operator stack
val = []  # value stack
```

For achieving evaluation, we will augment the grammar with the following actions, whose implementation details will be shown later:

- `number()`: calculate numeric value of most recently consumed token,
- `val.append(number)`: push a number onto the value stack,
- `op.append(operator)`: push an operator onto the operator stack,
- `evaluate()`: pop an operator off the operator stack and evaluate it with one or more operands popped off the value stack, pushing the result onto the value stack.

For inserting an action in Python into the EBNF grammar, it must be wrapped in a **processing instruction**, which

- begins with `<?` and a name,
- continues with some whitespace, and the actual Python code,
- terminates with `?>`.

The Python code of course must not contain the character sequence `?>`.

A grammar may contain multiple action sets using different names, and an action is only included into the generated code, if its name is selected using the `-a` command line option to specify the name. We will use `aee` as the name of our set of actions, as an acronym for *A*rithmetic *E*xpression *E*valuator. Thus command line option `-a aee` must be used, and actions inserted into the grammar will look like this: `<?aee self.val.append(self.number())?>`.

The actions are positioned in the grammar as follows:

```
Expression ::= Term (('+'                   <?aee self.op.append('+')?>
                          | '-'             <?aee self.op.append('-')?>
                               ) Term       <?aee self.evaluate()?>
                                      )*
Term       ::= Factor (('*'                 <?aee self.op.append('*')?>
                            | '/'           <?aee self.op.append('/')?>
                                 ) Factor   <?aee self.evaluate()?>
                                         )*
Factor     ::=                              <?aee self.op.append(' ')?>
               ('+' | '-'                   <?aee
                                              self.op.pop()
                                              self.op.append('_')
                                            ?>
                          )? Primary        <?aee self.evaluate()?>
Primary    ::= Number                       <?aee self.val.append(self.number())?>
             | '(' Expression ')'
```

Actions may be placed anywhere on the right hand side of the syntax rules, and they will be executed when the parser's control flow passes by the respective position. Note that actions can only be placed in the syntax definition, but not in the lexical definition.

You are free in formatting the grammar as you like, but in the example above, actions have been aligned on the right hand side, in order to visually separate them from the pure grammar rules on the left hand side.

Now for actually declaring the data structures and implementing the methods used in our actions, we need to add some more Python code:

```python
op = []   # operator stack
val = []  # value stack

def number(self):
  token = self.input[self.b0:self.e0]
  return int(token)

def evaluate(self):
  rhs = self.val.pop()
  operator = self.op.pop()
  if operator == '+':
    self.val.append(self.val.pop() + rhs)
  elif operator == '-':
    self.val.append(self.val.pop() - rhs)
  elif operator == '*':
    self.val.append(self.val.pop() * rhs)
  elif operator == '/':
    self.val.append(self.val.pop() // rhs)
  elif operator == '_':
    self.val.append(- rhs)
  else:
    self.val.append(rhs)
```

Also we will supply our own main program, that takes a command line argument, passes it to the parser, and prints the result:

```python
def main(args):
  parser = Arithmetic(args[1])
  try:
    parser.parse_Expression()
    print(parser.val.pop())
  except Arithmetic.ParseException as pe:
    raise Exception (parser.getErrorMessage(pe)) from pe

if __name__ == '__main__':
  sys.exit(main(sys.argv))
```

Both of this, the code implementing the actions and the main program can be added to the grammar file, for having REx include it into the generated code. Such extra code can be added

- at the very beginning of the grammar. In this case it must also contain any necessary `import` statements, the `class` declaration, and the constructor, which usually must call `initialize(inputString)`.
- at the end of the grammar, following an `<?ENCORE?>` indicator.

We will add our utility code at the beginning, and the main program at the end, such that the complete file `Arithmetic.ebnf` now looks as follows:

```
                                            <?aee
                                              import sys

                                              class Arithmetic:

                                                def __init__(self, inputString):
                                                  self.initialize(inputString)

                                                op = []   # operator stack
                                                val = []  # value stack

                                                def number(self):
                                                  token = self.input[self.b0:self.e0]
                                                  return int(token)

                                                def evaluate(self):
                                                  rhs = self.val.pop()
                                                  operator = self.op.pop()
                                                  if operator == '+':
                                                    self.val.append(self.val.pop() + rhs)
                                                  elif operator == '-':
                                                    self.val.append(self.val.pop() - rhs)
                                                  elif operator == '*':
                                                    self.val.append(self.val.pop() * rhs)
                                                  elif operator == '/':
                                                    self.val.append(self.val.pop() // rhs)
                                                  elif operator == '_':
                                                    self.val.append(- rhs)
                                                  else:
                                                    self.val.append(rhs)
                                            ?>

Expression ::= Term (('+'                   <?aee self.op.append('+')?>
                          | '-'             <?aee self.op.append('-')?>
                               ) Term       <?aee self.evaluate()?>
                                      )*
Term       ::= Factor (('*'                 <?aee self.op.append('*')?>
                            | '/'           <?aee self.op.append('/')?>
                                 ) Factor   <?aee self.evaluate()?>
                                         )*
Factor     ::=                              <?aee self.op.append(' ')?>
               ('+' | '-'                   <?aee
                                              self.op.pop()
                                              self.op.append('_')
                                            ?>
                          )? Primary        <?aee self.evaluate()?>
Primary    ::= Number                       <?aee self.val.append(self.number())?>
             | '(' Expression ')'

<?TOKENS?>

Number     ::= [0-9]+
Whitespace ::= [ #x9#xA]+
               /*ws: definition*/

<?ENCORE?>

                                            <?aee
                                              def main(args):
                                                parser = Arithmetic(args[1])
                                                try:
                                                  parser.parse_Expression()
                                                  print(parser.val.pop())
                                                except Arithmetic.ParseException as pe:
                                                  raise Exception (parser.getErrorMessage(pe)) from pe

                                              if __name__ == '__main__':
                                                sys.exit(main(sys.argv))
                                            ?>
```

When inserted at the beginning, custom code also must include any `import` statements required by the generated code. For knowing them, we could have generated once without adding our custom code,

```sh
rex -python Arithmetic.ebnf
```

The `import` statement can then be grabbed from `Arithmetic.py` and augmented with those required by our custom code. In the actual case, the plain code generated for parsing has no specific `import` requirements, but that depends on details affected by the actual command line options that are used.

For having REx insert our newly added actions into the generated code, option `-a aee` must be added to the REx command line. Without that, there would be no difference in behavior, compared to the plain grammar that was used before.

Generate a parser including the actions, and compile it, using these commands:

```sh
rex -python -a aee Arithmetic.ebnf
```

Now it can be run to actually evaluate arithmetic expressions specified in the first command line argument, e.g.

```sh
python3 Arithmetic.py "( 42 * 17 + 6 ) / 8 - -9"
```

&nbsp;
---
[⇦ Previous page](quickstart-javascript.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](quickstart-scala.md)