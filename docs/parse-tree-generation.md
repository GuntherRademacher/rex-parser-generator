<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](grammar-processing.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](disambiguation-techniques.md)

&nbsp;
# Parse Tree Generation

A REx-generated parser emits parse tree generation events when the `-tree` command line option is used during parser generation. This is a concrete parse tree, that reflects every derivation or reduction that was done in the parsing process. No mechanisms are in place to condense it into an abstract parse tree, but this can be done by the application based on the concrete parse tree.

The parse tree is emitted as a sequence of events. These can be processed either directly by the application, or a standard tree builder can be used for materializing the tree.

The actual interface depends on the parsing algorithm. Due to the top-down nature of LL parsing, and the bottom-up nature of LR parsing, there are different events and interfaces for them.

The following is explained in this document:

 - [Identifying Nonterminals and Terminals](#identifying-nonterminals-and-terminals)
 - [Migrating from Names to Codes](#migrating-from-names-to-codes)
 - [Top-Down Parsing: `EventHandler` Interface](#top-down-parsing-eventhandler-interface)
   - [`reset(input)`](#resetinput)
   - [`startNonterminal(id, begin)`](#startnonterminalid-begin)
   - [`endNonterminal(id, end)`](#endnonterminalid-end)
   - [`terminal(id, begin, end)`](#terminalid-begin-end)
   - [`whitespace(begin, end)`](#whitespacebegin-end)
 - [Bottom-Up Parsing: `BottomUpEventHandler` Interface](#bottom-up-parsing-bottomupeventhandler-interface)
   - [`reset(input)`](#resetinput-1)
   - [`terminal(id, begin, end)`](#terminalid-begin-end-1)
   - [`nonterminal(id, begin, end, count)`](#nonterminalid-begin-end-count)
   - [`ambiguity(begin, end)`](#ambiguitybegin-end)
 - [Top-Down Parsing: `TopDownTreeBuilder` Class](#top-down-parsing-topdowntreebuilder-class)
 - [Bottom-Up Parsing: `ParseTreeBuilder` Class](#bottom-up-parsing-parsetreebuilder-class)
 - [Parse Tree Representation](#parse-tree-representation)
   - [`Symbol` class](#symbol-class)
   - [`Terminal` class](#terminal-class)
   - [`Nonterminal` class](#nonterminal-class)

Note: the information about parsing event interfaces does not apply to parsers genereated in XQuery or XSLT. Those will always materialize the parse tree, when enabled via `-tree`, and return it as the result of the parsing function for the start symbol.

## Identifying Nonterminals and Terminals

Parsing events identify nonterminals and terminals by their integer codes, not by their names. 
The names are available in two arrays of the generated parser, which are public when `-tree` 
is specified:

 - `NONTERMINAL` maps the code of a nonterminal to its name.
 - `TOKEN` maps the code of a terminal to its name. It is also public with `-nolexer`, where 
   an external lexer needs to deliver the codes of the terminals.

Without these options, the arrays are not part of the public interface of the generated parser. 
JavaScript and Python have no access control for them, so they are accessible anyway.

For convenience, the generated parser also provides the accessor methods `getNonterminalName(id)` 
and `getTerminalName(id)` (spelled `GetNonterminalName` and `GetTerminalName` in Go), that 
return the entries of these arrays. Applications that only need the names for presentation 
purposes can thus look them up on demand, while applications that dispatch on the kind of 
symbol can compare the integer codes without any string handling.

Nonterminal codes are assigned in the same way for all parsing algorithms.

**Special case: `-glr` or `-glalr` with `-ambiguity reject`.** When the parse tree of an 
ambiguous input is reported, as described in [Disambiguation Techniques](disambiguation-techniques.md), 
event handlers will see three additional nonterminals: `ALTERNATIVE` (code -2), `AMBIGUOUS` 
(code -3), and `UNAMBIGUOUS` (code -4). Their codes are negative and the same for all grammars. 
They are not entries of the `NONTERMINAL` array, and indexing it with them would fail. 
Applications that use this combination of options should therefore resolve nonterminal names 
with `getNonterminalName(id)`. In all other cases, it is safe to access the `NONTERMINAL` array 
directly.

The codes are specific to the grammar they were generated for: the same code denotes different 
symbols in parsers generated from different grammars, and codes may change when the grammar is 
modified. Applications should therefore not store codes persistently, and should not compare 
them across parsers.

**Exception: Java parsers generated with `-interface NAME`.** Such parsers share the event 
handler interfaces with other parsers, so there is no single grammar the codes can be resolved 
against:

 - The names are obtained from a parser instance, so `getNonterminalName(id)` and 
   `getTerminalName(id)` are instance methods, not static ones.
 - `Symbol.getName()` takes the parser as an argument: `getName(parser)`.
 - The standard serializers need the parser as an additional constructor argument, e.g. 
   `new XmlSerializer(writer, indent, parser)`.

## Migrating from Names to Codes

Earlier releases passed names to the event handler methods. When updating an application:

 - Change the parameter lists of `startNonterminal`, `endNonterminal`, `terminal`, and 
   `nonterminal` implementations: the `String name` (or the language's equivalent) is replaced 
   by `int id`, at the same position.
 - Obtain names from `NONTERMINAL[id]` and `TOKEN[id]`, or through `getNonterminalName(id)` 
   and `getTerminalName(id)`.
 - Replace the `name` field of `Symbol` by `id`, and use `getName()` where the name is needed.
 - Do not carry codes over from one parser to another, they are grammar specific.

## Top-Down Parsing: `EventHandler` Interface

The `EventHandler` interface defines the communication between an LL parser and an application. The parser emits events during the parsing process to the methods of this interface. Applications implementing this interface can process these events to construct parse trees, analyze parsed content, or perform other parsing-related tasks.

### Methods

---

### `reset(input)`
**Description:** Prepares the handler to process a new input.
- **Parameter:**
  `input` - The content to be parsed.

---

### `startNonterminal(id, begin)`
**Description:** Signals the start of a non-terminal symbol in the input at a given position.
- **Parameters:**
  `id` - The code of the non-terminal symbol, an index into the `NONTERMINAL` array (but see the [special case](#identifying-nonterminals-and-terminals) for ambiguity reporting).
  `begin` - The starting position of the non-terminal in the input.

---

### `endNonterminal(id, end)`
**Description:** Signals the end of a non-terminal symbol in the input at a given position.
- **Parameters:**
  `id` - The code of the non-terminal symbol, an index into the `NONTERMINAL` array (but see the [special case](#identifying-nonterminals-and-terminals) for ambiguity reporting).
  `end` - The ending position of the non-terminal in the input.

---

### `terminal(id, begin, end)`
**Description:** Reports the recognition of a terminal symbol in the input at the given position range.
- **Parameters:**
  `id` - The code of the terminal symbol, an index into the `TOKEN` array.
  `begin` - The starting position of the terminal in the input.
  `end` - The ending position of the terminal in the input.

---

### `whitespace(begin, end)`
**Description:** Identifies a sequence of whitespace characters in the input.
- **Parameters:**
  `begin` - The starting position of the whitespace sequence in the input.
  `end` - The ending position of the whitespace sequence in the input.

---

## Top-Down Parsing: `TopDownTreeBuilder` Class

`TopDownTreeBuilder` is a standard implementation of the `EventHandler` interface that constructs a materialized parse tree during the parsing process.

- **Fields:**
  - `stack`: The stack holding the symbols being processed. After parsing completes successfully, the single remaining node in the stack is the `Nonterminal` representing the start symbol.

## Bottom-Up Parsing: `BottomUpEventHandler` Interface

The `BottomUpEventHandler` interface defines the communication between an LALR, LR, or GLR parser and an application. The parser emits events during the parsing process to the methods of this interface. Applications implementing this interface can process these events to construct parse trees, analyze parsed content, or perform other parsing-related tasks.

### Methods

---

### `reset(input)`
**Description:** Prepares the handler to process a new input.
- **Parameter:**
  `input` - The content to be parsed.

---

### `terminal(id, begin, end)`
**Description:** Reports the recognition of a terminal symbol in the grammar.
- **Parameters:**
  - `id` - The code of the terminal symbol, an index into the `TOKEN` array.
  - `begin` - The starting position of the terminal in the input.
  - `end` - The ending position of the terminal in the input.

---

### `nonterminal(id, begin, end, count)`
**Description:** Reports the recognition of a nonterminal symbol in the input.
- **Parameters:**
  - `id` - The code of the nonterminal symbol, an index into the `NONTERMINAL` array (but see the [special case](#identifying-nonterminals-and-terminals) for ambiguity reporting).
  - `begin` - The starting position of the non-terminal in the input.
  - `end` - The ending position of the non-terminal in the input.
  - `count` - The number of child symbols (terminals or nonterminals) that make up this nonterminal.

---

### `ambiguity(begin, end)`
**Description:** Only present for parsers generated with `-tree` and `-ambiguity minimal` or `-ambiguity shift` (see [Disambiguation Techniques](disambiguation-techniques.md#resolving-ambiguity-in-glr-parsers)). Reports that an ambiguity has been resolved by selecting one of the alternatives. The range from `begin` to `end` is an over-approximation of the ambiguous input: it contains the ambiguous part, but may start earlier, and it includes the lookahead token that had been read when the alternatives were merged.
- The notification is delivered after the events of the selected alternative, and possibly after further events: the lookahead terminal, or, if the ambiguity is only detected at the end of the input, the enclosing nonterminals.
- The events of the discarded alternatives are never delivered.
- For more than two alternatives, more than one notification may be delivered.
- `ParseTreeBuilder` ignores it.
- **Parameters:**
  - `begin` - The starting position of the range.
  - `end` - The ending position of the range.

## Bottom-Up Parsing: `ParseTreeBuilder` Class

`ParseTreeBuilder` is a standard implementation of the `BottomUpEventHandler` interface that constructs a materialized parse tree during the parsing process.

- **Fields:**
  - `stack`: The stack holding the symbols being processed. After parsing completes successfully, the single remaining node in the stack is the `Nonterminal` representing the start symbol.

## Parse Tree Representation

A materialized parse tree, as created by `TopDownTreeBuilder`  or `BottomUpTreeBuilder`, consists of two main types of nodes: `Terminal` and `Nonterminal`, both derived from the abstract `Symbol` class.

---

### `Symbol` Class

The base class for all nodes in the parse tree. It defines common properties and methods for tree nodes.

- **Fields:**
  - `id`: The code of the symbol: an index into the `NONTERMINAL` array for a `Nonterminal`, or into the `TOKEN` array for a `Terminal`. The exception are the special nonterminals used for reporting ambiguity (see [Identifying Nonterminals and Terminals](#identifying-nonterminals-and-terminals)), which have negative codes.
  - `begin`: The starting position of the symbol in the input.
  - `end`: The ending position of the symbol in the input.

- **Methods:**
  - `getName()`
    Returns the name of the symbol (e.g., a grammar rule or token name), by looking up `id` in the `NONTERMINAL` or `TOKEN` array.
  - `send(EventHandler e)` (abstract)
    Sends the symbol to an `EventHandler`, enabling traversal or processing of the parse tree.

---

### `Terminal` Class
Represents a terminal node in the parse tree, corresponding to recognized tokens.

- **Overrides `send`:**
  - Invokes `EventHandler.terminal(id, begin, end)` to communicate the terminal to the handler.

---

### `Nonterminal` Class

Represents a nonterminal node in the parse tree, corresponding to grammar rules. A nonterminal node can have child nodes, which may be other nonterminals or terminals.

- **Fields:**
  - `children`: An array of child `Symbol` nodes representing the subtree of this nonterminal.

- **Overrides `send`:**
  - Recursively invokes `send` on all child nodes, starting with `startNonterminal`, followed by processing children, and ending with `endNonterminal`.


&nbsp;
---
[⇦ Previous page](grammar-processing.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](disambiguation-techniques.md)