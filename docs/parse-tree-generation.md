<link rel="stylesheet" href="markdown.css">

[⇦ Previous page](grammar-processing.md) &nbsp;&nbsp;│&nbsp;&nbsp; [⇧ Back to index](../README.md#-rex-parser-generator) &nbsp;&nbsp;│&nbsp;&nbsp; [Next page ⇨ ](disambiguation-techniques.md)

&nbsp;
# Parse Tree Generation

A REx-generated parser emits parse tree generation events when the `-tree` command line option is used during parser generation. This is a concrete parse tree, that reflects every derivation or reduction that was done in the parsing process. No mechanisms are in place to condense it into an abstract parse tree, but this can be done by the application based on the concrete parse tree.

The parse tree is emitted as a sequence of events. These can be processed either directly by the application, or a standard tree builder can be used for materializing the tree.

The actual interface depends on the parsing algorithm. Due to the top-down nature of LL parsing, and the bottom-up nature of LR parsing, there are different events and interfaces for them.

The following is explained in this document:

 - [Top-Down Parsing: `EventHandler` Interface](#top-down-parsing-eventhandler-interface)
   - [`reset(input)`](#resetinput)
   - [`startNonterminal(name, begin)`](#startnonterminalname-begin)
   - [`endNonterminal(name, end)`](#endnonterminalname-end)
   - [`terminal(name, begin, end)`](#terminalname-begin-end)
   - [`whitespace(begin, end)`](#whitespacebegin-end)
 - [Bottom-Up Parsing: `BottomUpEventHandler` Interface](#bottom-up-parsing-bottomupeventhandler-interface)
   - [`reset(input)`](#resetinput-1)
   - [`terminal(name, begin, end)`](#terminalname-begin-end-1)
   - [`nonterminal(input)`](#nonterminalinput)
 - [Top-Down Parsing: `TopDownTreeBuilder` Class](#top-down-parsing-topdowntreebuilder-class)
 - [Bottom-Up Parsing: `ParseTreeBuilder` Class](#bottom-up-parsing-parsetreebuilder-class)
 - [Parse Tree Representation](#parse-tree-representation)
   - [`Symbol` class](#symbol-class)
   - [`Terminal` class](#terminal-class)
   - [`Nonterminal` class](#nonterminal-class)

Note: the information about parsing event interfaces does not apply to parsers genereated in XQuery or XSLT. Those will always materialize the parse tree, when enabled via `-tree`, and return it as the result of the parsing function for the start symbol.

## Top-Down Parsing: `EventHandler` Interface

The `EventHandler` interface defines the communication between an LL parser and an application. The parser emits events during the parsing process to the methods of this interface. Applications implementing this interface can process these events to construct parse trees, analyze parsed content, or perform other parsing-related tasks.

### Methods

---

### `reset(input)`
**Description:** Prepares the handler to process a new input.  
- **Parameter:**  
  `input` - The content to be parsed.  

---

### `startNonterminal(name, begin)`
**Description:** Signals the start of a non-terminal symbol in the input at a given position.  
- **Parameters:**  
  `name` - The name of the non-terminal symbol.  
  `begin` - The starting position of the non-terminal in the input.  

---

### `endNonterminal(name, end)`
**Description:** Signals the end of a non-terminal symbol in the input at a given position.  
- **Parameters:**  
  `name` - The name of the non-terminal symbol.  
  `end` - The ending position of the non-terminal in the input.  

---

### `terminal(name, begin, end)`
**Description:** Reports the recognition of a terminal symbol in the input at the given position range.  
- **Parameters:**  
  `name` - The name of the terminal symbol.  
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

### `terminal(name, begin, end)`
**Description:** Reports the recognition of a terminal symbol in the grammar.  
- **Parameters:**  
  - `name` - The name of the terminal symbol.  
  - `begin` - The starting position of the terminal in the input.  
  - `end` - The ending position of the terminal in the input.  

--- 

### `nonterminal(input)`
**Description:** Reports the recognition of a nonterminal symbol in the input. 
- **Parameters:**  
  - `name` - The name of the nonterminal symbol.  
  - `begin` - The starting position of the non-terminal in the input.  
  - `end` - The ending position of the non-terminal in the input.  
  - `count` - The number of child symbols (terminals or nonterminals) that make up this nonterminal.  

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
  - `name`: The name of the symbol (e.g., a grammar rule or token name).
  - `begin`: The starting position of the symbol in the input.
  - `end`: The ending position of the symbol in the input.

- **Abstract Method:**
  - `send(EventHandler e)`  
    Sends the symbol to an `EventHandler`, enabling traversal or processing of the parse tree.

---

### `Terminal` Class
Represents a terminal node in the parse tree, corresponding to recognized tokens.

- **Overrides `send`:**
  - Invokes `EventHandler.terminal(name, begin, end)` to communicate the terminal to the handler.

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