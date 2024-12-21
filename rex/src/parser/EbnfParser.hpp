// This file was generated on Fri Dec 20, 2024 23:02 (UTC+01) by REx v6.0 which is Copyright (c) 1979-2024 by Gunther Rademacher <grd@gmx.net>
// REx command line: EbnfParser.ebnf -cpp -a rex

#ifndef EBNFPARSER_HPP
#define EBNFPARSER_HPP

#include <stdio.h>
#include <string>
#include <algorithm>
                                                            #line 3 "EbnfParser.ebnf"
                                                            #include "EbnfParserBase.hpp"
                                                            #include "../common/Strings.hpp"

                                                            // TODO: supply syntax for "disambiguating/lazy" lookahead (as opposed to mandatory lookahead)

                                                            class EbnfParser : public EbnfParserBase
                                                            {
                                                              const wchar_t *currentChar() {return input + b0;}
                                                              const int currentLength() {return e0 - b0;}

                                                            public:
                                                              virtual ~EbnfParser() {}

                                                              Grammar *parse(wchar_t *input, const wchar_t *aFileName)
                                                              {
                                                                fileName = aFileName;
                                                                initialize(input);
                                                                grammar = new Grammar();
                                                                currentNode = grammar;
                                                                parse_Grammar();
                                                                Grammar *g = grammar;
                                                                grammar = 0;
                                                                return g;
                                                              }
                                                            #line 36 "EbnfParser.hpp"
public:
  class ParseException
  {
  private:
    int begin, end, offending, expected, state;
    friend class EbnfParser;

  protected:
    ParseException(int b, int e, int s, int o, int x)
    : begin(b), end(e), offending(o), expected(x), state(s)
    {
    }

  public:
    const wchar_t *getMessage() const
    {
      return offending < 0
           ? L"lexical analysis failed"
           : L"syntax error";
    }

    int getBegin() const {return begin;}
    int getEnd() const {return end;}
    int getState() const {return state;}
    int getOffending() const {return offending;}
    int getExpected() const {return expected;}
  };

  void initialize(const wchar_t *source)
  {
    input = source;
    reset(0, 0, 0);
  }

  const wchar_t *getInput() const
  {
    return input;
  }

  int getTokenOffset() const
  {
    return b0;
  }

  int getTokenEnd() const
  {
    return e0;
  }

  void reset(int l, int b, int e)
  {
            b0 = b; e0 = b;
    l1 = l; b1 = b; e1 = e;
    l2 = 0; b2 = 0; e2 = 0;
    l3 = 0; b3 = 0; e3 = 0;
    end = e;
  }

  void reset()
  {
    reset(0, 0, 0);
  }

  static const wchar_t *getOffendingToken(ParseException e)
  {
    return e.getOffending() < 0 ? 0 : TOKEN[e.getOffending()];
  }

  static void getExpectedTokenSet(const ParseException &e, const wchar_t **set, int size)
  {
    if (e.expected < 0)
    {
      getTokenSet(- e.state, set, size);
    }
    else if (size == 1)
    {
      set[0] = 0;
    }
    else if (size > 1)
    {
      set[0] = TOKEN[e.expected];
      set[1] = 0;
    }
  }

  static std::wstring to_wstring(int i)
  {
    const wchar_t *sign = i < 0 ? L"-" : L"";
    std::wstring a;
    do
    {
      a += L'0' + abs(i % 10);
      i /= 10;
    }
    while (i != 0);
    a += sign;
    std::reverse(a.begin(), a.end());
    return a;
  }

  std::wstring getErrorMessage(const ParseException &e)
  {
    std::wstring message(e.getMessage());
    const wchar_t *found = getOffendingToken(e);
    if (found != 0)
    {
      message += L", found ";
      message += found;
    }
    const wchar_t *expected[64];
    getExpectedTokenSet(e, expected, sizeof expected / sizeof *expected);
    message += L"\nwhile expecting ";
    const wchar_t *delimiter(expected[1] ? L"[" : L"");
    for (const wchar_t **x = expected; *x; ++x)
    {
      message += delimiter;
      message += *x;
      delimiter = L", ";
    }
    message += expected[1] ? L"]\n" : L"\n";
    int size = e.getEnd() - e.getBegin();
    if (size != 0 && found == 0)
    {
      message += L"after successfully scanning ";
      message += to_wstring(size);
      message += L" characters beginning ";
    }
    int line = 1;
    int column = 1;
    for (int i = 0; i < e.getBegin(); ++i)
    {
      if (input[i] == L'\n')
      {
        ++line;
        column = 1;
      }
      else
      {
        ++column;
      }
    }
    message += L"at line ";
    message += to_wstring(line);
    message += L", column ";
    message += to_wstring(column);
    message += L":\n...";
    const wchar_t *w = input + e.getBegin();
    for (int i = 0; i < 64 && *w; ++i)
    {
      message += *w++;
    }
    message += L"...";
    return message;
  }

  void parse_Grammar()
  {
    lookahead1W(11);                // Whitespace | Name | '<?'
    parse_Prolog();
    parse_SyntaxDefinition();
    if (l1 == 29)                   // '<?TOKENS?>'
    {
      parse_LexicalDefinition();
    }
    if (l1 == 28)                   // '<?ENCORE?>'
    {
      parse_Encore();
    }
    consume(11);                    // EOF
  }

private:

  void parse_Prolog()
  {
                                                            #line 29 "EbnfParser.ebnf"
                                                            section = PROLOG;
                                                            #line 214 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(11);              // Whitespace | Name | '<?'
      if (l1 != 27)                 // '<?'
      {
        break;
      }
      parse_ProcessingInstruction();
    }
  }

  void parse_ProcessingInstruction()
  {
    consume(27);                    // '<?'
    lookahead1(0);                  // Name
    consume(2);                     // Name
                                                            #line 33 "EbnfParser.ebnf"
                                                            wchar_t *name(WStringRef(currentToken()).copy());
                                                            wchar_t *content = 0;
                                                            int line;
                                                            int column;
                                                            Strings::getLineAndColumn(input, b0, &line, &column);
                                                            #line 237 "EbnfParser.hpp"
    lookahead1(8);                  // Space | '?>'
    if (l1 == 3)                    // Space
    {
      for (;;)
      {
        consume(3);                 // Space
        lookahead1(17);             // Space | DirPIContents | '?>'
        if (l1 != 3)                // Space
        {
          break;
        }
      }
      if (l1 == 4)                  // DirPIContents
      {
        consume(4);                 // DirPIContents
                                                            #line 41 "EbnfParser.ebnf"
                                                            Strings::getLineAndColumn(input, b0, &line, &column);
                                                            wchar_t *value = currentToken().copy();
                                                            content = Format::reIndent(trim(value), 0);
                                                            free(value);
                                                            #line 258 "EbnfParser.hpp"
      }
    }
                                                            #line 48 "EbnfParser.ebnf"
                                                            if (content == 0)
                                                              content = wcsdup(L"");
                                                            currentNode->addChild(new ProcessingInstruction(name, line, fileName, content));
                                                            #line 265 "EbnfParser.hpp"
    lookahead1(2);                  // '?>'
    consume(33);                    // '?>'
  }

  void parse_SyntaxDefinition()
  {
                                                            #line 55 "EbnfParser.ebnf"
                                                            static_cast<Grammar *>(currentNode)->setProlog();
                                                            section = NONTERMINALS;
                                                            #line 275 "EbnfParser.hpp"
    for (;;)
    {
      parse_SyntaxProduction();
      if (l1 != 2)                  // Name
      {
        break;
      }
    }
                                                            #line 58 "EbnfParser.ebnf"
                                                            static_cast<Grammar *>(currentNode)->setNonTerminals();
                                                            #line 286 "EbnfParser.hpp"
  }

  void parse_SyntaxProduction()
  {
                                                            #line 59 "EbnfParser.ebnf"
                                                            GrammarSection s = section;
                                                            #line 293 "EbnfParser.hpp"
    consume(2);                     // Name
                                                            #line 60 "EbnfParser.ebnf"
                                                            WStringRef name(currentToken());
                                                            #line 297 "EbnfParser.hpp"
    lookahead1W(4);                 // Whitespace | '::='
    consume(25);                    // '::='
    lookahead1W(34);                // Whitespace | Name | StringLiteral | EOF | '(' | '/' | '/*' | '<?' |
                                    // '<?ENCORE?>' | '<?TOKENS?>' | '|'
    parse_SyntaxChoice();
                                                            #line 61 "EbnfParser.ebnf"
                                                            wrap(new Production(s, false, name.copy()));
                                                            #line 305 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(21);              // Whitespace | Name | EOF | '/*' | '<?ENCORE?>' | '<?TOKENS?>'
      if (l1 != 23)                 // '/*'
      {
        break;
      }
      parse_Option();
    }
  }

  void parse_SyntaxChoice()
  {
    parse_SyntaxSequence();
                                                            #line 63 "EbnfParser.ebnf"
                                                            Choice *choice = 0;
                                                            #line 322 "EbnfParser.hpp"
    if (l1 == 22                    // '/'
     || l1 == 41)                   // '|'
    {
      switch (l1)
      {
      case 41:                      // '|'
        {
          for (;;)
          {
            consume(41);            // '|'
                                                            #line 64 "EbnfParser.ebnf"
                                                            if (choice == 0) choice = currentNode->addChild(new Choice(currentNode->isolateLastChild()));
                                                            #line 335 "EbnfParser.hpp"
            lookahead1W(33);        // Whitespace | Name | StringLiteral | EOF | '(' | ')' | '/*' | '<?' |
                                    // '<?ENCORE?>' | '<?TOKENS?>' | '|'
            parse_SyntaxSequence();
                                                            #line 65 "EbnfParser.ebnf"
                                                            choice->addCase(currentNode->isolateLastChild());
                                                            #line 341 "EbnfParser.hpp"
            if (l1 != 41)           // '|'
            {
              break;
            }
          }
        }
        break;
      default:
        {
          for (;;)
          {
            consume(22);            // '/'
                                                            #line 67 "EbnfParser.ebnf"
                                                            if (choice == 0) choice = currentNode->addChild(new Choice(currentNode->isolateLastChild()));
                                                            #line 356 "EbnfParser.hpp"
            lookahead1W(32);        // Whitespace | Name | StringLiteral | EOF | '(' | ')' | '/' | '/*' | '<?' |
                                    // '<?ENCORE?>' | '<?TOKENS?>'
            parse_SyntaxSequence();
                                                            #line 68 "EbnfParser.ebnf"
                                                            choice->addCase(currentNode->isolateLastChild());
                                                            #line 362 "EbnfParser.hpp"
            if (l1 != 22)           // '/'
            {
              break;
            }
          }
                                                            #line 69 "EbnfParser.ebnf"
                                                            choice->setOrdered();
                                                            #line 370 "EbnfParser.hpp"
        }
        break;
      }
    }
                                                            #line 71 "EbnfParser.ebnf"
                                                            if (choice)
                                                            {
                                                              Node *simplified = currentNode->isolateLastChild()->simplified();
                                                              currentNode->addChild(simplified);
                                                              if (choice != simplified) delete choice;
                                                            }
                                                            #line 382 "EbnfParser.hpp"
  }

  void parse_SyntaxSequence()
  {
                                                            #line 78 "EbnfParser.ebnf"
                                                            descend(new Sequence());
                                                            #line 389 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(35);              // Whitespace | Name | StringLiteral | EOF | '(' | ')' | '/' | '/*' | '<?' |
                                    // '<?ENCORE?>' | '<?TOKENS?>' | '|'
      switch (l1)
      {
      case 2:                       // Name
        lookahead2W(40);            // Whitespace | Name | StringLiteral | CaretName | EOF | '(' | ')' | '*' | '+' |
                                    // '/' | '/*' | '::=' | '<?' | '<?ENCORE?>' | '<?TOKENS?>' | '?' | '|'
        break;
      default:
        lk = l1;
        break;
      }
      if (lk == 11                  // EOF
       || lk == 16                  // ')'
       || lk == 22                  // '/'
       || lk == 23                  // '/*'
       || lk == 28                  // '<?ENCORE?>'
       || lk == 29                  // '<?TOKENS?>'
       || lk == 41                  // '|'
       || lk == 1602)               // Name '::='
      {
        break;
      }
      parse_SyntaxItem();
    }
                                                            #line 79 "EbnfParser.ebnf"
                                                            ascend();
                                                            #line 419 "EbnfParser.hpp"
  }

  void parse_SyntaxItem()
  {
    parse_SyntaxPrimary();
    lookahead1W(38);                // Whitespace | Name | StringLiteral | EOF | '(' | ')' | '*' | '+' | '/' | '/*' |
                                    // '<?' | '<?ENCORE?>' | '<?TOKENS?>' | '?' | '|'
    if (l1 == 17                    // '*'
     || l1 == 19                    // '+'
     || l1 == 32)                   // '?'
    {
      switch (l1)
      {
      case 32:                      // '?'
        {
          consume(32);              // '?'
                                                            #line 81 "EbnfParser.ebnf"
                                                            wrap(new Optional());
                                                            #line 438 "EbnfParser.hpp"
        }
        break;
      case 17:                      // '*'
        {
          consume(17);              // '*'
                                                            #line 82 "EbnfParser.ebnf"
                                                            wrap(new ZeroOrMore());
                                                            #line 446 "EbnfParser.hpp"
        }
        break;
      default:
        {
          consume(19);              // '+'
                                                            #line 83 "EbnfParser.ebnf"
                                                            wrap(new OneOrMore());
                                                            #line 454 "EbnfParser.hpp"
        }
        break;
      }
    }
  }

  void parse_SyntaxPrimary()
  {
    switch (l1)
    {
    case 15:                        // '('
      consume(15);                  // '('
      lookahead1W(25);              // Whitespace | Name | StringLiteral | '(' | ')' | '/' | '<?' | '|'
      parse_SyntaxChoice();
      consume(16);                  // ')'
      break;
    case 27:                        // '<?'
      parse_ProcessingInstruction();
      break;
    default:
      parse_NameOrString();
      break;
    }
  }

  void parse_LexicalDefinition()
  {
    consume(29);                    // '<?TOKENS?>'
                                                            #line 88 "EbnfParser.ebnf"
                                                            section = TERMINALS;
                                                            #line 485 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(22);              // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' |
                                    // '<?ENCORE?>'
      if (l1 == 11                  // EOF
       || l1 == 28)                 // '<?ENCORE?>'
      {
        break;
      }
      switch (l1)
      {
      case 2:                       // Name
        lookahead2W(23);            // Whitespace | CaretName | '::=' | '<<' | '>>' | '?' | '\\'
        break;
      default:
        lk = l1;
        break;
      }
      switch (lk)
      {
      case 21:                      // '.'
      case 1602:                    // Name '::='
      case 2050:                    // Name '?'
        parse_LexicalProduction();
        break;
      case 2306:                    // Name '\\'
        parse_Delimiter();
        break;
      case 12:                      // EquivalenceLookAhead
        parse_Equivalence();
        break;
      default:
        parse_Preference();
        break;
      }
    }
                                                            #line 93 "EbnfParser.ebnf"
                                                            static_cast<Grammar *>(currentNode)->setTerminals();
                                                            #line 524 "EbnfParser.hpp"
  }

  void parse_LexicalProduction()
  {
                                                            #line 94 "EbnfParser.ebnf"
                                                            GrammarSection
                                                            s = section;
                                                            bool nonGreedy = false;
                                                            #line 533 "EbnfParser.hpp"
    switch (l1)
    {
    case 2:                         // Name
      consume(2);                   // Name
      break;
    default:
      consume(21);                  // '.'
      break;
    }
                                                            #line 100 "EbnfParser.ebnf"
                                                            WStringRef name(currentToken());
                                                            #line 545 "EbnfParser.hpp"
    lookahead1W(15);                // Whitespace | '::=' | '?'
    if (l1 == 32)                   // '?'
    {
      consume(32);                  // '?'
                                                            #line 101 "EbnfParser.ebnf"
                                                            nonGreedy = true;
                                                            #line 552 "EbnfParser.hpp"
    }
    lookahead1W(4);                 // Whitespace | '::='
    consume(25);                    // '::='
    lookahead1W(37);                // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | '.' | '/*' | '<?ENCORE?>' | '[' | '[^' | '|'
    parse_ContextChoice();
                                                            #line 103 "EbnfParser.ebnf"
                                                            wrap(new Production(s, nonGreedy, name.copy()));
                                                            #line 561 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(24);              // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '/*' |
                                    // '<?ENCORE?>'
      if (l1 != 23)                 // '/*'
      {
        break;
      }
      parse_Option();
    }
  }

  void parse_ContextChoice()
  {
    parse_ContextExpression();
                                                            #line 105 "EbnfParser.ebnf"
                                                            Choice *choice = 0;
                                                            #line 579 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(27);              // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '/*' |
                                    // '<?ENCORE?>' | '|'
      if (l1 != 41)                 // '|'
      {
        break;
      }
      consume(41);                  // '|'
                                                            #line 106 "EbnfParser.ebnf"
                                                            if (choice == 0) choice = currentNode->addChild(new Choice(currentNode->isolateLastChild()));
                                                            #line 591 "EbnfParser.hpp"
      lookahead1W(37);              // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | '.' | '/*' | '<?ENCORE?>' | '[' | '[^' | '|'
      parse_ContextExpression();
                                                            #line 107 "EbnfParser.ebnf"
                                                            choice->addCase(currentNode->isolateLastChild());
                                                            #line 597 "EbnfParser.hpp"
    }
                                                            #line 109 "EbnfParser.ebnf"
                                                            if (choice)
                                                            {
                                                              Node *simplified = currentNode->isolateLastChild()->simplified();
                                                              currentNode->addChild(simplified);
                                                              if (choice != simplified) delete choice;
                                                            }
                                                            #line 606 "EbnfParser.hpp"
  }

  void parse_LexicalChoice()
  {
    parse_LexicalSequence();
                                                            #line 116 "EbnfParser.ebnf"
                                                            Choice *choice = 0;
                                                            #line 614 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(14);              // Whitespace | ')' | '|'
      if (l1 != 41)                 // '|'
      {
        break;
      }
      consume(41);                  // '|'
                                                            #line 117 "EbnfParser.ebnf"
                                                            if (choice == 0) choice = currentNode->addChild(new Choice(currentNode->isolateLastChild()));
                                                            #line 625 "EbnfParser.hpp"
      lookahead1W(31);              // Whitespace | Name | StringLiteral | CharCode | '$' | '(' | ')' | '.' | '[' |
                                    // '[^' | '|'
      parse_LexicalSequence();
                                                            #line 118 "EbnfParser.ebnf"
                                                            choice->addCase(currentNode->isolateLastChild());
                                                            #line 631 "EbnfParser.hpp"
    }
                                                            #line 120 "EbnfParser.ebnf"
                                                            if (choice)
                                                            {
                                                              Node *simplified = currentNode->isolateLastChild()->simplified();
                                                              currentNode->addChild(simplified);
                                                              if (choice != simplified) delete choice;
                                                            }
                                                            #line 640 "EbnfParser.hpp"
  }

  void parse_ContextExpression()
  {
    parse_LexicalSequence();
    lookahead1W(30);                // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '&' | '.' |
                                    // '/*' | '<?ENCORE?>' | '|'
    if (l1 == 14)                   // '&'
    {
      consume(14);                  // '&'
      lookahead1W(26);              // Whitespace | Name | StringLiteral | CharCode | '$' | '(' | '.' | '[' | '[^'
      parse_LexicalItem();
                                                            #line 129 "EbnfParser.ebnf"
                                                            Node *rhs = currentNode->isolateLastChild();
                                                            currentNode->addChild(new Context(currentNode->isolateLastChild(), rhs));
                                                            #line 656 "EbnfParser.hpp"
    }
  }

  void parse_LexicalSequence()
  {
                                                            #line 133 "EbnfParser.ebnf"
                                                            descend(new Sequence());
                                                            #line 664 "EbnfParser.hpp"
    switch (l1)
    {
    case 2:                         // Name
      lookahead2W(51);              // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '-' | '.' | '/*' |
                                    // '::=' | '<<' | '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '\\' | '|'
      switch (lk)
      {
      case 2050:                    // Name '?'
        lookahead3W(43);            // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '-' | '.' | '/*' | '::=' | '<?ENCORE?>' | '[' | '[^' | '|'
        break;
      }
      break;
    case 5:                         // StringLiteral
      lookahead2W(49);              // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '-' | '.' | '/*' |
                                    // '<<' | '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '|'
      break;
    case 21:                        // '.'
      lookahead2W(47);              // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '*' | '+' | '-' | '.' | '/*' | '::=' | '<?ENCORE?>' | '?' |
                                    // '[' | '[^' | '|'
      switch (lk)
      {
      case 2069:                    // '.' '?'
        lookahead3W(43);            // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '-' | '.' | '/*' | '::=' | '<?ENCORE?>' | '[' | '[^' | '|'
        break;
      }
      break;
    default:
      lk = l1;
      break;
    }
    switch (lk)
    {
    case 11:                        // EOF
    case 12:                        // EquivalenceLookAhead
    case 14:                        // '&'
    case 16:                        // ')'
    case 23:                        // '/*'
    case 28:                        // '<?ENCORE?>'
    case 41:                        // '|'
    case 386:                       // Name CaretName
    case 389:                       // StringLiteral CaretName
    case 1602:                      // Name '::='
    case 1621:                      // '.' '::='
    case 1666:                      // Name '<<'
    case 1669:                      // StringLiteral '<<'
    case 1986:                      // Name '>>'
    case 1989:                      // StringLiteral '>>'
    case 2306:                      // Name '\\'
    case 104450:                    // Name '?' '::='
    case 104469:                    // '.' '?' '::='
      break;
    default:
      {
        parse_LexicalItem();
        lookahead1W(41);            // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '-' | '.' | '/*' | '<?ENCORE?>' | '[' | '[^' | '|'
        switch (l1)
        {
        case 20:                    // '-'
          {
            consume(20);            // '-'
            lookahead1W(26);        // Whitespace | Name | StringLiteral | CharCode | '$' | '(' | '.' | '[' | '[^'
            parse_LexicalItem();
                                                            #line 137 "EbnfParser.ebnf"
                                                            Node *rhs = currentNode->isolateLastChild();
                                                            Node *lhs = currentNode->isolateLastChild();
                                                            currentNode->addChild(new Exclusion(lhs, rhs));
                                                            #line 737 "EbnfParser.hpp"
          }
          break;
        default:
          for (;;)
          {
            lookahead1W(39);        // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '.' | '/*' | '<?ENCORE?>' | '[' | '[^' | '|'
            switch (l1)
            {
            case 2:                 // Name
              lookahead2W(50);      // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '.' | '/*' | '::=' |
                                    // '<<' | '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '\\' | '|'
              switch (lk)
              {
              case 2050:            // Name '?'
                lookahead3W(42);    // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '.' | '/*' | '::=' | '<?ENCORE?>' | '[' | '[^' | '|'
                break;
              }
              break;
            case 5:                 // StringLiteral
              lookahead2W(48);      // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '.' | '/*' | '<<' |
                                    // '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '|'
              break;
            case 21:                // '.'
              lookahead2W(46);      // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '*' | '+' | '.' | '/*' | '::=' | '<?ENCORE?>' | '?' | '[' |
                                    // '[^' | '|'
              switch (lk)
              {
              case 2069:            // '.' '?'
                lookahead3W(42);    // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '.' | '/*' | '::=' | '<?ENCORE?>' | '[' | '[^' | '|'
                break;
              }
              break;
            default:
              lk = l1;
              break;
            }
            if (lk == 11            // EOF
             || lk == 12            // EquivalenceLookAhead
             || lk == 14            // '&'
             || lk == 16            // ')'
             || lk == 23            // '/*'
             || lk == 28            // '<?ENCORE?>'
             || lk == 41            // '|'
             || lk == 386           // Name CaretName
             || lk == 389           // StringLiteral CaretName
             || lk == 1602          // Name '::='
             || lk == 1621          // '.' '::='
             || lk == 1666          // Name '<<'
             || lk == 1669          // StringLiteral '<<'
             || lk == 1986          // Name '>>'
             || lk == 1989          // StringLiteral '>>'
             || lk == 2306          // Name '\\'
             || lk == 104450        // Name '?' '::='
             || lk == 104469)       // '.' '?' '::='
            {
              break;
            }
            parse_LexicalItem();
          }
          break;
        }
      }
      break;
    }
                                                            #line 143 "EbnfParser.ebnf"
                                                            ascend();
                                                            #line 810 "EbnfParser.hpp"
  }

  void parse_LexicalItem()
  {
    parse_LexicalPrimary();
    lookahead1W(45);                // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '*' | '+' | '-' | '.' | '/*' | '<?ENCORE?>' | '?' | '[' |
                                    // '[^' | '|'
    if (l1 == 17                    // '*'
     || l1 == 19                    // '+'
     || l1 == 32)                   // '?'
    {
      switch (l1)
      {
      case 32:                      // '?'
        {
          consume(32);              // '?'
                                                            #line 145 "EbnfParser.ebnf"
                                                            wrap(new Optional());
                                                            #line 830 "EbnfParser.hpp"
        }
        break;
      case 17:                      // '*'
        {
          consume(17);              // '*'
                                                            #line 146 "EbnfParser.ebnf"
                                                            wrap(new ZeroOrMore());
                                                            #line 838 "EbnfParser.hpp"
        }
        break;
      default:
        {
          consume(19);              // '+'
                                                            #line 147 "EbnfParser.ebnf"
                                                            wrap(new OneOrMore());
                                                            #line 846 "EbnfParser.hpp"
        }
        break;
      }
    }
  }

  void parse_LexicalPrimary()
  {
    switch (l1)
    {
    case 2:                         // Name
    case 21:                        // '.'
      {
        switch (l1)
        {
        case 2:                     // Name
          consume(2);               // Name
          break;
        default:
          consume(21);              // '.'
          break;
        }
                                                            #line 149 "EbnfParser.ebnf"
                                                            currentNode->addChild(new Ref(currentToken().copy()));
                                                            #line 871 "EbnfParser.hpp"
      }
      break;
    case 5:                         // StringLiteral
      {
        consume(5);                 // StringLiteral
                                                            #line 150 "EbnfParser.ebnf"
                                                            currentNode->addChild(new String(currentToken().copy()));
                                                            #line 879 "EbnfParser.hpp"
      }
      break;
    case 15:                        // '('
      consume(15);                  // '('
      lookahead1W(31);              // Whitespace | Name | StringLiteral | CharCode | '$' | '(' | ')' | '.' | '[' |
                                    // '[^' | '|'
      parse_LexicalChoice();
      consume(16);                  // ')'
      break;
    case 13:                        // '$'
      {
        consume(13);                // '$'
                                                            #line 152 "EbnfParser.ebnf"
                                                            currentNode->addChild(new EndOfFile());
                                                            #line 894 "EbnfParser.hpp"
      }
      break;
    case 7:                         // CharCode
      {
        consume(7);                 // CharCode
                                                            #line 153 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharCode(charCodeValue(currentChar() + 1)));
                                                            #line 902 "EbnfParser.hpp"
      }
      break;
    default:
      parse_CharClass();
      break;
    }
  }

  void parse_NameOrString()
  {
    switch (l1)
    {
    case 2:                         // Name
      {
        consume(2);                 // Name
                                                            #line 155 "EbnfParser.ebnf"
                                                            currentNode->addChild(new Ref(currentToken().copy()));
                                                            #line 920 "EbnfParser.hpp"
        lookahead1W(44);            // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '(' | ')' | '*' | '+' | '.' | '/' | '/*' | '<<' | '<?' | '<?ENCORE?>' |
                                    // '<?TOKENS?>' | '>>' | '?' | '|'
        if (l1 == 6)                // CaretName
        {
          parse_Context();
        }
      }
      break;
    default:
      {
        consume(5);                 // StringLiteral
                                                            #line 157 "EbnfParser.ebnf"
                                                            currentNode->addChild(new String(currentToken().copy()));
                                                            #line 935 "EbnfParser.hpp"
        lookahead1W(44);            // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '(' | ')' | '*' | '+' | '.' | '/' | '/*' | '<<' | '<?' | '<?ENCORE?>' |
                                    // '<?TOKENS?>' | '>>' | '?' | '|'
        if (l1 == 6)                // CaretName
        {
          parse_Context();
        }
      }
      break;
    }
  }

  void parse_Context()
  {
    consume(6);                     // CaretName
                                                            #line 159 "EbnfParser.ebnf"
                                                            static_cast<NodeWithContext *>(currentNode->lastChild)->context = currentToken().copy(1);
                                                            #line 953 "EbnfParser.hpp"
  }

  void parse_CharClass()
  {
                                                            #line 160 "EbnfParser.ebnf"
                                                            bool complement = false;
                                                            #line 960 "EbnfParser.hpp"
    switch (l1)
    {
    case 34:                        // '['
      consume(34);                  // '['
      break;
    default:
      {
        consume(35);                // '[^'
                                                            #line 162 "EbnfParser.ebnf"
                                                            complement = true;
                                                            #line 971 "EbnfParser.hpp"
      }
      break;
    }
                                                            #line 163 "EbnfParser.ebnf"
                                                            descend(new CharClass());
                                                            #line 977 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1(19);               // CharCode | Char | CharRange | CharCodeRange
      switch (l1)
      {
      case 8:                       // Char
        {
          consume(8);               // Char
                                                            #line 164 "EbnfParser.ebnf"
                                                            currentNode->addChild(new Char(*currentChar()));
                                                            #line 988 "EbnfParser.hpp"
        }
        break;
      case 7:                       // CharCode
        {
          consume(7);               // CharCode
                                                            #line 165 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharCode(charCodeValue(currentChar() + 1)));
                                                            #line 996 "EbnfParser.hpp"
        }
        break;
      case 9:                       // CharRange
        {
          consume(9);               // CharRange
                                                            #line 166 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharRange(b0, *currentChar(), *(currentChar() + 2)));
                                                            #line 1004 "EbnfParser.hpp"
        }
        break;
      default:
        {
          consume(10);              // CharCodeRange
                                                            #line 168 "EbnfParser.ebnf"
                                                            int minValue = charCodeValue(currentChar() + 1);
                                                            currentNode->addChild(new CharCodeRange(b0, minValue, charCodeValue(wcschr(currentChar(), L'-') + 2)));
                                                            #line 1013 "EbnfParser.hpp"
        }
        break;
      }
      lookahead1(20);               // CharCode | Char | CharRange | CharCodeRange | ']'
      if (l1 == 37)                 // ']'
      {
        break;
      }
    }
                                                            #line 171 "EbnfParser.ebnf"
                                                            ascend();
                                                            #line 1025 "EbnfParser.hpp"
    consume(37);                    // ']'
                                                            #line 173 "EbnfParser.ebnf"
                                                            if (complement)
                                                            {
                                                              currentNode->addChild(new Complement(static_cast<CharClass *>(currentNode->isolateLastChild())));
                                                            }
                                                            #line 1032 "EbnfParser.hpp"
  }

  void parse_Option()
  {
    consume(23);                    // '/*'
    for (;;)
    {
      lookahead1(9);                // Space | 'ws'
      if (l1 != 3)                  // Space
      {
        break;
      }
      consume(3);                   // Space
    }
    consume(40);                    // 'ws'
    lookahead1(1);                  // ':'
    consume(24);                    // ':'
    for (;;)
    {
      lookahead1(18);               // Space | 'definition' | 'explicit'
      if (l1 != 3)                  // Space
      {
        break;
      }
      consume(3);                   // Space
    }
    switch (l1)
    {
    case 39:                        // 'explicit'
      {
        consume(39);                // 'explicit'
                                                            #line 181 "EbnfParser.ebnf"
                                                            static_cast<Production *>(currentNode->lastChild)->wsExplicit = true;
                                                            #line 1066 "EbnfParser.hpp"
      }
      break;
    default:
      {
        consume(38);                // 'definition'
                                                            #line 183 "EbnfParser.ebnf"
                                                            Production *p = static_cast<Production *>(currentNode->lastChild);
                                                            p->wsExplicit = true;
                                                            setWhitespaceDefinition(p);
                                                            #line 1076 "EbnfParser.hpp"
      }
      break;
    }
    for (;;)
    {
      lookahead1(7);                // Space | '*/'
      if (l1 != 3)                  // Space
      {
        break;
      }
      consume(3);                   // Space
    }
    consume(18);                    // '*/'
  }

  void parse_Preference()
  {
    parse_NameOrString();
                                                            #line 192 "EbnfParser.ebnf"
                                                            Preference *preference = new Preference();
                                                            #line 1097 "EbnfParser.hpp"
    lookahead1W(16);                // Whitespace | '<<' | '>>'
    switch (l1)
    {
    case 31:                        // '>>'
      {
        consume(31);                // '>>'
                                                            #line 193 "EbnfParser.ebnf"
                                                            preference->addLhs(currentNode->isolateLastChild());
                                                            #line 1106 "EbnfParser.hpp"
        for (;;)
        {
          lookahead1W(10);          // Whitespace | Name | StringLiteral
          parse_NameOrString();
                                                            #line 194 "EbnfParser.ebnf"
                                                            preference->addRhs(currentNode->isolateLastChild());
                                                            #line 1113 "EbnfParser.hpp"
          lookahead1W(22);          // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' |
                                    // '<?ENCORE?>'
          switch (l1)
          {
          case 2:                   // Name
            lookahead2W(36);        // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '.' | '::=' | '<<' | '<?ENCORE?>' | '>>' | '?' | '\\'
            switch (lk)
            {
            case 386:               // Name CaretName
              lookahead3W(28);      // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '<<' |
                                    // '<?ENCORE?>' | '>>'
              break;
            }
            break;
          case 5:                   // StringLiteral
            lookahead2W(29);        // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '.' | '<<' | '<?ENCORE?>' | '>>'
            switch (lk)
            {
            case 389:               // StringLiteral CaretName
              lookahead3W(28);      // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '<<' |
                                    // '<?ENCORE?>' | '>>'
              break;
            }
            break;
          default:
            lk = l1;
            break;
          }
          if (lk == 11              // EOF
           || lk == 12              // EquivalenceLookAhead
           || lk == 21              // '.'
           || lk == 28              // '<?ENCORE?>'
           || lk == 1602            // Name '::='
           || lk == 1666            // Name '<<'
           || lk == 1669            // StringLiteral '<<'
           || lk == 1986            // Name '>>'
           || lk == 1989            // StringLiteral '>>'
           || lk == 2050            // Name '?'
           || lk == 2306            // Name '\\'
           || lk == 106882          // Name CaretName '<<'
           || lk == 106885          // StringLiteral CaretName '<<'
           || lk == 127362          // Name CaretName '>>'
           || lk == 127365)         // StringLiteral CaretName '>>'
          {
            break;
          }
        }
      }
      break;
    default:
      {
        consume(26);                // '<<'
                                                            #line 196 "EbnfParser.ebnf"
                                                            preference->addRhs(currentNode->isolateLastChild());
                                                            #line 1170 "EbnfParser.hpp"
        for (;;)
        {
          lookahead1W(10);          // Whitespace | Name | StringLiteral
          parse_NameOrString();
                                                            #line 197 "EbnfParser.ebnf"
                                                            preference->addLhs(currentNode->isolateLastChild());
                                                            #line 1177 "EbnfParser.hpp"
          lookahead1W(22);          // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' |
                                    // '<?ENCORE?>'
          switch (l1)
          {
          case 2:                   // Name
            lookahead2W(36);        // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '.' | '::=' | '<<' | '<?ENCORE?>' | '>>' | '?' | '\\'
            switch (lk)
            {
            case 386:               // Name CaretName
              lookahead3W(28);      // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '<<' |
                                    // '<?ENCORE?>' | '>>'
              break;
            }
            break;
          case 5:                   // StringLiteral
            lookahead2W(29);        // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '.' | '<<' | '<?ENCORE?>' | '>>'
            switch (lk)
            {
            case 389:               // StringLiteral CaretName
              lookahead3W(28);      // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '<<' |
                                    // '<?ENCORE?>' | '>>'
              break;
            }
            break;
          default:
            lk = l1;
            break;
          }
          if (lk == 11              // EOF
           || lk == 12              // EquivalenceLookAhead
           || lk == 21              // '.'
           || lk == 28              // '<?ENCORE?>'
           || lk == 1602            // Name '::='
           || lk == 1666            // Name '<<'
           || lk == 1669            // StringLiteral '<<'
           || lk == 1986            // Name '>>'
           || lk == 1989            // StringLiteral '>>'
           || lk == 2050            // Name '?'
           || lk == 2306            // Name '\\'
           || lk == 106882          // Name CaretName '<<'
           || lk == 106885          // StringLiteral CaretName '<<'
           || lk == 127362          // Name CaretName '>>'
           || lk == 127365)         // StringLiteral CaretName '>>'
          {
            break;
          }
        }
      }
      break;
    }
                                                            #line 199 "EbnfParser.ebnf"
                                                            currentNode->addChild(preference);
                                                            #line 1232 "EbnfParser.hpp"
  }

  void parse_Delimiter()
  {
    consume(2);                     // Name
                                                            #line 200 "EbnfParser.ebnf"
                                                            Delimiter *delimiter = new Delimiter(new Ref(currentToken().copy()));
                                                            #line 1240 "EbnfParser.hpp"
    lookahead1W(6);                 // Whitespace | '\\'
    consume(36);                    // '\\'
    for (;;)
    {
      lookahead1W(10);              // Whitespace | Name | StringLiteral
      parse_NameOrString();
                                                            #line 201 "EbnfParser.ebnf"
                                                            delimiter->addRhs(currentNode->isolateLastChild());
                                                            #line 1249 "EbnfParser.hpp"
      lookahead1W(22);              // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' |
                                    // '<?ENCORE?>'
      switch (l1)
      {
      case 2:                       // Name
        lookahead2W(36);            // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '.' | '::=' | '<<' | '<?ENCORE?>' | '>>' | '?' | '\\'
        switch (lk)
        {
        case 386:                   // Name CaretName
          lookahead3W(28);          // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '<<' |
                                    // '<?ENCORE?>' | '>>'
          break;
        }
        break;
      case 5:                       // StringLiteral
        lookahead2W(29);            // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
                                    // '.' | '<<' | '<?ENCORE?>' | '>>'
        switch (lk)
        {
        case 389:                   // StringLiteral CaretName
          lookahead3W(28);          // Whitespace | Name | StringLiteral | EOF | EquivalenceLookAhead | '.' | '<<' |
                                    // '<?ENCORE?>' | '>>'
          break;
        }
        break;
      default:
        lk = l1;
        break;
      }
      if (lk == 11                  // EOF
       || lk == 12                  // EquivalenceLookAhead
       || lk == 21                  // '.'
       || lk == 28                  // '<?ENCORE?>'
       || lk == 1602                // Name '::='
       || lk == 1666                // Name '<<'
       || lk == 1669                // StringLiteral '<<'
       || lk == 1986                // Name '>>'
       || lk == 1989                // StringLiteral '>>'
       || lk == 2050                // Name '?'
       || lk == 2306                // Name '\\'
       || lk == 106882              // Name CaretName '<<'
       || lk == 106885              // StringLiteral CaretName '<<'
       || lk == 127362              // Name CaretName '>>'
       || lk == 127365)             // StringLiteral CaretName '>>'
      {
        break;
      }
    }
                                                            #line 202 "EbnfParser.ebnf"
                                                            currentNode->addChild(delimiter);
                                                            #line 1301 "EbnfParser.hpp"
  }

  void parse_Equivalence()
  {
    consume(12);                    // EquivalenceLookAhead
                                                            #line 203 "EbnfParser.ebnf"
                                                            Equivalence *equivalence = new Equivalence();
                                                            #line 1309 "EbnfParser.hpp"
    lookahead1W(12);                // Whitespace | StringLiteral | '['
    parse_EquivalenceCharRange();
                                                            #line 204 "EbnfParser.ebnf"
                                                            equivalence->setLhs(currentNode->isolateLastChild());
                                                            #line 1314 "EbnfParser.hpp"
    lookahead1W(5);                 // Whitespace | '=='
    consume(30);                    // '=='
    lookahead1W(12);                // Whitespace | StringLiteral | '['
    parse_EquivalenceCharRange();
                                                            #line 207 "EbnfParser.ebnf"
                                                            equivalence->setRhs(currentNode->isolateLastChild());
                                                            currentNode->addChild(equivalence);
                                                            #line 1322 "EbnfParser.hpp"
  }

  void parse_EquivalenceCharRange()
  {
    switch (l1)
    {
    case 5:                         // StringLiteral
      {
        consume(5);                 // StringLiteral
                                                            #line 211 "EbnfParser.ebnf"
                                                            currentNode->addChild(new String(currentToken().copy()));
                                                            #line 1334 "EbnfParser.hpp"
      }
      break;
    default:
      {
        consume(34);                // '['
        lookahead1(19);             // CharCode | Char | CharRange | CharCodeRange
        switch (l1)
        {
        case 8:                     // Char
          {
            consume(8);             // Char
                                                            #line 213 "EbnfParser.ebnf"
                                                            currentNode->addChild(new Char(*currentChar()));
                                                            #line 1348 "EbnfParser.hpp"
          }
          break;
        case 7:                     // CharCode
          {
            consume(7);             // CharCode
                                                            #line 214 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharCode(charCodeValue(currentChar() + 1)));
                                                            #line 1356 "EbnfParser.hpp"
          }
          break;
        case 9:                     // CharRange
          {
            consume(9);             // CharRange
                                                            #line 215 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharRange(b0, *currentChar(), *(currentChar() + 2)));
                                                            #line 1364 "EbnfParser.hpp"
          }
          break;
        default:
          {
            consume(10);            // CharCodeRange
                                                            #line 217 "EbnfParser.ebnf"
                                                            int minValue = charCodeValue(currentChar() + 1);
                                                            currentNode->addChild(new CharCodeRange(b0, minValue, charCodeValue(wcschr(currentChar(), L'-') + 2)));
                                                            #line 1373 "EbnfParser.hpp"
          }
          break;
        }
        lookahead1(3);              // ']'
        consume(37);                // ']'
      }
      break;
    }
  }

  void parse_Encore()
  {
    consume(28);                    // '<?ENCORE?>'
                                                            #line 224 "EbnfParser.ebnf"
                                                            section = EPILOG;
                                                            #line 1389 "EbnfParser.hpp"
    for (;;)
    {
      lookahead1W(13);              // Whitespace | EOF | '<?'
      if (l1 != 27)                 // '<?'
      {
        break;
      }
      parse_ProcessingInstruction();
    }
                                                            #line 225 "EbnfParser.ebnf"
                                                            static_cast<Grammar *>(currentNode)->setEpilog();
                                                            #line 1401 "EbnfParser.hpp"
  }

  void consume(int t)
  {
    if (l1 == t)
    {
      b0 = b1; e0 = e1; l1 = l2; if (l1 != 0) {
      b1 = b2; e1 = e2; l2 = l3; if (l2 != 0) {
      b2 = b3; e2 = e3; l3 = 0; }}
    }
    else
    {
      error(b1, e1, 0, l1, t);
    }
  }

  int matchW(int tokenSetId)
  {
    int code;
    for (;;)
    {
      code = match(tokenSetId);
      if (code != 1)                // Whitespace
      {
        break;
      }
    }
    return code;
  }

  void lookahead1W(int tokenSetId)
  {
    if (l1 == 0)
    {
      l1 = matchW(tokenSetId);
      b1 = begin;
      e1 = end;
    }
  }

  void lookahead2W(int tokenSetId)
  {
    if (l2 == 0)
    {
      l2 = matchW(tokenSetId);
      b2 = begin;
      e2 = end;
    }
    lk = (l2 << 6) | l1;
  }

  void lookahead3W(int tokenSetId)
  {
    if (l3 == 0)
    {
      l3 = matchW(tokenSetId);
      b3 = begin;
      e3 = end;
    }
    lk |= l3 << 12;
  }

  void lookahead1(int tokenSetId)
  {
    if (l1 == 0)
    {
      l1 = match(tokenSetId);
      b1 = begin;
      e1 = end;
    }
  }

  int error(int b, int e, int s, int l, int t)
  {
    throw ParseException(b, e, s, l, t);
  }

  int lk, b0, e0;
  int l1, b1, e1;
  int l2, b2, e2;
  int l3, b3, e3;

  const wchar_t *input;
  int begin;
  int end;

  int match(int tokenSetId)
  {
    bool nonbmp = false;
    begin = end;
    int current = end;
    int result = INITIAL[tokenSetId];
    int state = 0;

    for (int code = result & 255; code != 0; )
    {
      int charclass;
      int c0 = input[current];
      ++current;
      if (c0 < 0x80)
      {
        charclass = MAP0[c0];
      }
      else if (c0 < 0xd800)
      {
        int c1 = c0 >> 4;
        charclass = MAP1[(c0 & 15) + MAP1[(c1 & 31) + MAP1[c1 >> 5]]];
      }
      else
      {
        if (c0 < 0xdc00)
        {
          int c1 = input[current];
          if (c1 >= 0xdc00 && c1 < 0xe000)
          {
            nonbmp = true;
            ++current;
            c0 = ((c0 & 0x3ff) << 10) + (c1 & 0x3ff) + 0x10000;
          }
        }
        int lo = 0, hi = 5;
        for (int m = 3; ; m = (hi + lo) >> 1)
        {
          if (MAP2[m] > c0) hi = m - 1;
          else if (MAP2[6 + m] < c0) lo = m + 1;
          else {charclass = MAP2[12 + m]; break;}
          if (lo > hi) {charclass = 0; break;}
        }
      }

      state = code;
      int i0 = (charclass << 8) + code - 1;
      code = TRANSITION[(i0 & 7) + TRANSITION[i0 >> 3]];
      if (code > 255)
      {
        result = code;
        code &= 255;
        end = current;
      }
    }

    result >>= 8;
    if (result == 0)
    {
      end = current - 1;
      int c1 = input[end];
      if (c1 >= 0xdc00 && c1 < 0xe000) --end;
      return error(begin, end, state, -1, -1);
    }

    if ((result & 64) != 0)
    {
      end = begin;
      if (nonbmp)
      {
        for (int i = result >> 7; i > 0; --i)
        {
          int c1 = input[end++];
          if (c1 >= 0xd800 && c1 < 0xdc00) ++end;
        }
      }
      else
      {
        end += (result >> 7);
      }
    }
    else
    {
      if (nonbmp)
      {
        for (int i = result >> 7; i > 0; --i)
        {
          int c1 = input[--end];
          if (c1 >= 0xdc00 && c1 < 0xe000) --end;
        }
      }
      else
      {
        end -= result >> 7;
      }
    }

    if (input[begin] == 0) end = begin;
    return (result & 63) - 1;
  }

  static void getTokenSet(int tokenSetId, const wchar_t **set, int size)
  {
    int s = tokenSetId < 0 ? - tokenSetId : INITIAL[tokenSetId] & 255;
    for (int i = 0; i < 42; i += 32)
    {
      int j = i;
      for (unsigned int f = ec(i >> 5, s); f != 0; f >>= 1, ++j)
      {
        if ((f & 1) != 0)
        {
          if (size > 1)
          {
            set[0] = TOKEN[j];
            ++set;
            --size;
          }
        }
      }
    }
    if (size > 0)
    {
      set[0] = 0;
    }
  }

  static int ec(int t, int s)
  {
    int i0 = t * 177 + s - 1;
    return EXPECTED[(i0 & 3) + EXPECTED[i0 >> 2]];
  }

  static const int MAP0[];
  static const int MAP1[];
  static const int MAP2[];
  static const int INITIAL[];
  static const int TRANSITION[];
  static const int EXPECTED[];
  static const wchar_t *TOKEN[];
};

const int EbnfParser::MAP0[] =
{
/*   0 */ 52, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 6,
/*  36 */ 7, 4, 8, 9, 10, 11, 12, 13, 4, 14, 15, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 4, 19, 20, 21, 22, 4,
/*  65 */ 23, 23, 24, 23, 25, 23, 26, 26, 26, 26, 27, 26, 26, 28, 29, 26, 26, 30, 31, 32, 26, 26, 26, 26, 26, 26, 33,
/*  92 */ 34, 35, 36, 26, 4, 23, 23, 37, 38, 39, 40, 26, 26, 41, 26, 26, 42, 26, 43, 44, 45, 26, 26, 46, 47, 26, 26, 48,
/* 120 */ 49, 26, 26, 4, 50, 4, 4, 4
};

const int EbnfParser::MAP1[] =
{
/*   0 */ 108, 124, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 156, 181, 181, 181, 181, 181,
/*  22 */ 214, 215, 213, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214,
/*  44 */ 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214,
/*  66 */ 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214,
/*  88 */ 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 247, 261,
/* 110 */ 277, 293, 309, 325, 371, 387, 424, 424, 424, 416, 355, 347, 355, 347, 355, 355, 355, 355, 355, 355, 355, 355,
/* 132 */ 355, 355, 355, 355, 355, 355, 355, 355, 441, 441, 441, 441, 441, 441, 441, 340, 355, 355, 355, 355, 355, 355,
/* 154 */ 355, 355, 400, 424, 424, 425, 423, 424, 424, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355,
/* 176 */ 355, 355, 355, 355, 355, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424,
/* 198 */ 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 424, 354, 355, 355, 355, 355, 355, 355,
/* 220 */ 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355, 355,
/* 242 */ 355, 355, 355, 355, 424, 52, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/* 275 */ 0, 0, 3, 4, 5, 6, 7, 4, 8, 9, 10, 11, 12, 13, 4, 14, 15, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 4,
/* 305 */ 19, 20, 21, 22, 4, 23, 23, 24, 23, 25, 23, 26, 26, 26, 26, 27, 26, 26, 28, 29, 26, 26, 30, 31, 32, 26, 26, 26,
/* 333 */ 26, 26, 26, 33, 34, 35, 36, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 4, 26, 26, 26, 26, 26, 26,
/* 361 */ 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 4, 23, 23, 37, 38, 39, 40, 26, 26, 41, 26, 26, 42, 26, 43, 44, 45, 26,
/* 389 */ 26, 46, 47, 26, 26, 48, 49, 26, 26, 4, 50, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 26, 26, 4, 4, 4, 4, 4, 4, 4, 4,
/* 422 */ 4, 51, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
/* 454 */ 51, 51, 51
};

const int EbnfParser::MAP2[] =
{
/*  0 */ 57344, 63744, 64976, 65008, 65536, 983040, 63743, 64975, 65007, 65533, 983039, 1114111, 4, 26, 4, 26, 26, 4
};

const int EbnfParser::INITIAL[] =
{
/*  0 */ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
/* 30 */ 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52
};

const int EbnfParser::TRANSITION[] =
{
/*    0 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*   18 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3275, 1696, 1706, 1698,
/*   36 */ 1698, 1698, 1813, 2663, 2078, 1728, 2455, 2082, 2150, 2220, 1738, 2805, 3305, 1747, 1758, 3076, 1775, 3257,
/*   54 */ 1797, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3086, 1809, 1713, 1698, 1698, 1698, 1813, 1729,
/*   72 */ 2078, 1728, 2125, 2082, 2959, 2220, 1821, 2895, 2405, 1831, 3001, 3270, 1842, 2439, 1797, 1729, 1729, 1729,
/*   90 */ 1729, 1729, 1729, 1729, 1729, 1729, 3275, 1696, 1720, 1698, 1698, 1698, 1813, 2827, 2078, 1872, 1897, 2188,
/*  108 */ 2150, 2863, 1738, 2805, 3305, 1747, 1758, 3076, 1775, 3257, 1797, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  126 */ 1729, 1729, 1729, 1729, 2347, 1729, 1729, 1729, 1729, 1823, 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205,
/*  144 */ 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2902,
/*  162 */ 3230, 1921, 1921, 1921, 1925, 2685, 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416,
/*  180 */ 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2073, 1849, 3286, 1855,
/*  198 */ 1860, 1823, 2078, 1937, 2341, 2188, 2150, 2880, 2507, 2205, 1834, 2776, 1890, 3416, 3384, 3117, 2683, 1729,
/*  216 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2347, 3048, 1864, 3054, 3059, 1823, 2078, 1872,
/*  234 */ 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729,
/*  252 */ 1729, 1729, 1729, 1729, 1729, 1729, 2347, 2108, 2109, 1950, 1955, 1823, 2078, 1872, 2067, 2188, 2150, 2880,
/*  270 */ 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  288 */ 1729, 3008, 2326, 2470, 2470, 2470, 2474, 2813, 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776,
/*  306 */ 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2347, 1967,
/*  324 */ 1974, 1979, 1983, 1823, 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117,
/*  342 */ 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2368, 2347, 1995, 2002, 2008, 2012, 1823,
/*  360 */ 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729,
/*  378 */ 1729, 1729, 1729, 1729, 1729, 1729, 2083, 1729, 2347, 1729, 2642, 2024, 2028, 1823, 2078, 2036, 2248, 2188,
/*  396 */ 2294, 3363, 2402, 2396, 2052, 2049, 2060, 2954, 2091, 2591, 2106, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  414 */ 1729, 1729, 1729, 1729, 2347, 1729, 3033, 2117, 2121, 1823, 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205,
/*  432 */ 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  450 */ 2347, 1729, 1729, 2133, 2137, 1823, 1942, 2145, 2067, 2167, 2174, 2200, 2811, 2213, 1750, 2776, 1890, 3416,
/*  468 */ 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3341, 2357, 2352, 2358,
/*  486 */ 2228, 1823, 2078, 1872, 2067, 2188, 2241, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729,
/*  504 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3063, 1782, 1789, 2262, 2270, 2276, 2281, 1882, 2078, 2289,
/*  522 */ 3348, 2188, 2233, 2971, 2632, 2626, 2779, 2302, 2313, 2931, 2334, 3177, 2366, 1729, 1729, 1729, 1729, 1729,
/*  540 */ 1729, 1729, 1729, 1729, 1729, 1729, 2347, 1729, 1729, 1729, 1877, 1823, 2078, 2537, 2067, 2376, 2389, 2413,
/*  558 */ 2811, 2418, 1750, 3378, 1890, 2734, 2426, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  576 */ 2434, 1730, 2254, 1729, 1959, 2447, 2451, 2463, 2078, 1872, 2067, 2188, 2150, 2754, 2811, 2205, 1750, 2155,
/*  594 */ 3171, 3081, 3384, 2159, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2912, 2486, 2494,
/*  612 */ 2519, 2525, 2533, 1823, 2545, 1872, 2557, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117,
/*  630 */ 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3105, 1729, 2347, 1729, 1729, 1729, 1729, 2571,
/*  648 */ 2078, 1872, 2181, 2188, 2150, 3189, 2811, 2579, 2305, 2776, 2599, 3411, 2619, 1913, 2640, 1729, 1729, 1729,
/*  666 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2650, 1987, 2478, 2478, 2657, 1823, 3204, 1872, 2098, 2841,
/*  684 */ 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 2676, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  702 */ 1729, 1729, 1765, 1767, 2693, 1729, 3421, 2700, 2704, 1823, 2716, 2729, 2742, 2750, 2150, 2880, 2811, 2205,
/*  720 */ 1750, 2776, 1890, 3209, 2762, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028,
/*  738 */ 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2845, 2067, 2376, 2389, 2413, 2811, 2418, 1750, 3378, 1890, 2734,
/*  756 */ 2426, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787,
/*  774 */ 2790, 1823, 2078, 2845, 2067, 2376, 2389, 2413, 2926, 2418, 1750, 3378, 1890, 2734, 2426, 3117, 2683, 1729,
/*  792 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2845,
/*  810 */ 2067, 2798, 2389, 2413, 2811, 2418, 2381, 3378, 1890, 2821, 2426, 3117, 2683, 1729, 1729, 1729, 1729, 1729,
/*  828 */ 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2188, 2241, 2880,
/*  846 */ 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  864 */ 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2188, 2241, 2880, 2585, 2205, 1750, 2776,
/*  882 */ 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787,
/*  900 */ 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2188, 2241, 2606, 2811, 2205, 1750, 2994, 1890, 3416, 3384, 3117,
/*  918 */ 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823,
/*  936 */ 2078, 2835, 2067, 2188, 2241, 2936, 2811, 2205, 2769, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729,
/*  954 */ 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2188,
/*  972 */ 2241, 2880, 2811, 2205, 1750, 3140, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/*  990 */ 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2188, 2241, 2880, 2811, 2205,
/* 1008 */ 1750, 2776, 1890, 3406, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028,
/* 1026 */ 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2853, 2241, 2880, 2811, 2205, 1750, 2776, 1890, 3416,
/* 1044 */ 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2907, 3320, 3326, 2016, 2871,
/* 1062 */ 2876, 1823, 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729,
/* 1080 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1799, 1729, 3354, 1729, 1801, 1729, 3359, 3245, 2078, 1872,
/* 1098 */ 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729,
/* 1116 */ 1729, 1729, 1729, 1729, 2859, 1729, 1903, 1729, 1729, 1729, 1729, 1823, 2078, 1728, 2708, 2549, 2888, 1739,
/* 1134 */ 2219, 2920, 1750, 2776, 1890, 3416, 3146, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/* 1152 */ 1729, 1729, 2563, 2667, 2668, 2949, 2967, 1823, 2078, 2979, 3224, 2188, 2150, 2880, 2811, 2205, 1750, 2776,
/* 1170 */ 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787,
/* 1188 */ 2787, 2787, 2790, 1823, 2078, 2845, 2067, 2376, 2389, 2413, 2811, 2418, 2987, 3378, 1890, 2734, 2426, 3117,
/* 1206 */ 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3021, 2787, 2787, 2787, 2790, 1823,
/* 1224 */ 2078, 2845, 2067, 2376, 2389, 2413, 2811, 2418, 1750, 3378, 1890, 2734, 2426, 3117, 2683, 1729, 1729, 1729,
/* 1242 */ 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3041, 2787, 2787, 2787, 2790, 1823, 2041, 2845, 2067, 2376,
/* 1260 */ 2389, 2413, 2811, 2418, 1750, 3378, 1890, 2734, 2426, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/* 1278 */ 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2845, 2067, 3071, 2389, 2413, 2811, 2418,
/* 1296 */ 1750, 3378, 1890, 2734, 2426, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028,
/* 1314 */ 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2188, 3094, 2880, 3102, 2941, 1750, 3113, 3125, 3416,
/* 1332 */ 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787,
/* 1350 */ 2790, 1823, 2078, 2835, 2067, 2188, 2241, 3133, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729,
/* 1368 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835,
/* 1386 */ 2067, 2188, 2241, 2880, 3154, 2205, 1750, 2776, 1890, 3416, 3384, 3164, 2683, 1729, 1729, 1729, 1729, 1729,
/* 1404 */ 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 2188, 2241, 2880,
/* 1422 */ 2811, 2205, 1750, 2776, 1890, 2721, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/* 1440 */ 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2067, 3185, 2241, 2880, 2811, 2205, 1750, 2776,
/* 1458 */ 1890, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787,
/* 1476 */ 2787, 2787, 2790, 2511, 2078, 2835, 2067, 2188, 3197, 2880, 2811, 2611, 1750, 2776, 3217, 3416, 3238, 3117,
/* 1494 */ 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823,
/* 1512 */ 2078, 2835, 2067, 2188, 2241, 2880, 2811, 2205, 1750, 3253, 1890, 3265, 3384, 3117, 2683, 1729, 1729, 1729,
/* 1530 */ 1729, 1729, 1729, 1729, 1729, 1729, 3031, 3301, 3399, 2787, 2787, 2787, 2790, 1823, 2078, 2835, 2320, 2188,
/* 1548 */ 2241, 2880, 3283, 2501, 3447, 2776, 1890, 1908, 3294, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/* 1566 */ 1729, 1729, 3031, 3028, 3399, 2787, 2787, 2787, 2790, 1823, 3013, 3313, 2067, 2188, 3334, 2880, 2811, 2205,
/* 1584 */ 3371, 2776, 3392, 3416, 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 3156,
/* 1602 */ 2347, 3429, 3434, 3439, 3443, 1823, 2078, 1872, 2067, 2188, 2150, 2880, 2811, 2205, 1750, 2776, 1890, 3416,
/* 1620 */ 3384, 3117, 2683, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2347, 1729, 1729, 1729,
/* 1638 */ 1877, 1823, 2078, 1872, 2067, 2188, 2241, 2880, 2811, 2205, 1750, 2776, 1890, 3416, 3384, 3117, 2683, 1729,
/* 1656 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 2192, 1929, 3462, 3455, 3455, 3465, 1729, 1729, 1729,
/* 1674 */ 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729, 1729,
/* 1692 */ 1729, 1729, 1729, 1729, 1084, 1084, 567, 567, 567, 567, 567, 567, 567, 567, 567, 1084, 1084, 0, 0, 567, 567,
/* 1713 */ 567, 1024, 1024, 0, 0, 567, 567, 567, 1084, 1084, 2376, 2376, 567, 567, 567, 35072, 0, 0, 0, 0, 0, 0, 0, 0,
/* 1737 */ 57, 625, 0, 0, 0, 0, 0, 0, 0, 100, 649, 650, 0, 0, 0, 0, 0, 144, 134, 0, 100, 144, 144, 134, 134, 0, 100,
/* 1764 */ 663, 0, 0, 54, 0, 0, 0, 0, 0, 0, 8448, 0, 162, 163, 163, 163, 163, 163, 0, 0, 56, 56, 56, 56, 56, 56, 68, 0,
/* 1792 */ 2376, 2376, 74, 56, 56, 177, 0, 0, 0, 0, 0, 0, 0, 59, 0, 0, 0, 1024, 1024, 567, 567, 567, 567, 567, 567, 0,
/* 1818 */ 0, 567, 0, 635, 0, 0, 0, 0, 0, 0, 0, 63, 64, 649, 663, 0, 0, 0, 0, 0, 144, 134, 149, 100, 0, 162, 174, 174,
/* 1846 */ 174, 174, 174, 0, 0, 79, 0, 0, 0, 0, 79, 79, 79, 0, 79, 79, 79, 79, 0, 0, 0, 0, 0, 3584, 0, 3584, 35072, 0,
/* 1874 */ 0, 0, 96, 0, 0, 0, 0, 821, 0, 0, 0, 0, 4864, 0, 63, 64, 144, 144, 134, 134, 0, 100, 100, 0, 0, 96, 0, 85,
/* 1902 */ 598, 0, 68, 0, 0, 9728, 0, 0, 0, 144, 167, 0, 0, 0, 144, 19856, 173, 166, 144, 63, 63, 63, 63, 63, 63, 63,
/* 1928 */ 63, 0, 0, 0, 0, 0, 3072, 3072, 0, 35072, 0, 0, 0, 97, 0, 0, 0, 68, 68, 0, 0, 92, 0, 3840, 3840, 3840, 0,
/* 1955 */ 3840, 3840, 3840, 3840, 0, 0, 0, 0, 57, 0, 0, 0, 0, 4096, 4096, 0, 0, 0, 0, 4096, 4096, 4096, 4096, 0, 4096,
/* 1980 */ 4096, 4096, 4096, 4096, 4096, 4096, 4096, 0, 0, 0, 0, 67, 67, 0, 0, 0, 4352, 0, 0, 0, 0, 0, 4352, 4352, 0,
/* 2005 */ 4352, 0, 0, 4352, 4352, 4352, 4352, 4352, 4352, 4352, 4352, 0, 0, 0, 0, 77, 9043, 0, 9043, 4608, 0, 0, 0,
/* 2028 */ 4608, 4608, 4608, 4608, 0, 0, 0, 85, 35072, 6229, 0, 0, 96, 0, 0, 0, 68, 68, 90, 0, 0, 101, 637, 0, 0, 0, 0,
/* 2055 */ 0, 145, 134, 0, 150, 145, 145, 157, 134, 0, 101, 101, 0, 0, 96, 0, 100, 598, 0, 68, 0, 73, 73, 0, 0, 0, 68,
/* 2082 */ 68, 0, 0, 0, 0, 0, 0, 0, 61, 0, 145, 164, 164, 163, 164, 164, 0, 0, 96, 0, 100, 598, 0, 66816, 145, 0, 0, 0,
/* 2110 */ 0, 0, 0, 0, 3840, 0, 3840, 5120, 0, 0, 0, 5120, 5120, 5120, 5120, 0, 0, 0, 0, 85, 567, 0, 68, 0, 5376, 0,
/* 2136 */ 5376, 0, 5376, 0, 5376, 821, 0, 0, 0, 35164, 0, 0, 0, 96, 0, 0, 0, 100, 100, 100, 598, 0, 0, 0, 0, 0, 144,
/* 2163 */ 144, 144, 134, 144, 68, 0, 0, 2560, 0, 0, 0, 109, 1890, 0, 100, 100, 100, 598, 0, 0, 96, 0, 100, 598, 6656,
/* 2188 */ 68, 0, 0, 2560, 0, 0, 0, 0, 0, 3072, 0, 0, 0, 116, 0, 0, 119, 0, 0, 100, 636, 636, 636, 636, 0, 0, 135, 100,
/* 2216 */ 636, 636, 636, 636, 0, 0, 0, 0, 0, 110, 0, 112, 5632, 5632, 5632, 5632, 821, 0, 0, 0, 100, 567, 100, 615, 0,
/* 2241 */ 0, 1890, 0, 100, 100, 100, 598, 0, 0, 96, 0, 101, 598, 0, 68, 0, 2376, 2376, 0, 0, 57, 74, 5944, 56, 74, 56,
/* 2267 */ 56, 74, 56, 5962, 74, 5962, 5962, 56, 74, 5962, 74, 74, 74, 5962, 74, 74, 74, 74, 0, 0, 56, 598, 35072, 598,
/* 2291 */ 0, 0, 96, 0, 0, 0, 101, 101, 101, 625, 0, 136, 638, 0, 0, 0, 0, 0, 144, 148, 0, 100, 110, 144, 147, 147, 0,
/* 2318 */ 649, 136, 0, 0, 96, 0, 102, 598, 0, 68, 0, 2376, 2376, 0, 64, 0, 0, 172, 165, 147, 165, 165, 165, 0, 0, 97,
/* 2344 */ 0, 100, 598, 0, 68, 0, 2376, 2376, 0, 0, 0, 0, 5632, 5632, 0, 5632, 5632, 5632, 5632, 5632, 5632, 5632, 172,
/* 2367 */ 0, 0, 0, 0, 0, 0, 0, 4352, 0, 68, 0, 0, 2560, 2154, 0, 0, 0, 143, 144, 134, 0, 100, 0, 1890, 2147, 100, 100,
/* 2394 */ 100, 598, 0, 0, 101, 637, 637, 636, 637, 0, 0, 0, 0, 0, 0, 133, 110, 0, 100, 0, 2154, 0, 0, 119, 0, 122, 100,
/* 2421 */ 636, 636, 636, 636, 0, 0, 144, 163, 163, 163, 163, 163, 168, 0, 6400, 0, 0, 57, 0, 0, 0, 144, 144, 174, 177,
/* 2446 */ 144, 57, 0, 57, 57, 0, 0, 57, 57, 0, 0, 0, 0, 85, 598, 0, 68, 87, 0, 0, 0, 0, 0, 63, 64, 64, 64, 64, 64, 64,
/* 2476 */ 64, 64, 0, 0, 0, 0, 67, 0, 0, 0, 66, 68, 0, 2376, 2376, 75, 76, 66, 76, 65, 0, 76, 81, 81, 76, 0, 0, 102,
/* 2504 */ 636, 636, 636, 636, 0, 0, 130, 0, 0, 0, 0, 0, 10496, 63, 64, 82, 82, 82, 82, 81, 76, 82, 76, 76, 76, 84, 76,
/* 2531 */ 76, 76, 81, 81, 81, 81, 0, 0, 0, 0, 96, 0, 0, 0, 0, 6912, 0, 68, 68, 0, 0, 0, 0, 0, 0, 110, 6912, 0, 96,
/* 2560 */ 6912, 100, 598, 0, 68, 0, 2376, 2376, 0, 0, 1870, 0, 7936, 0, 0, 0, 0, 63, 64, 19712, 0, 100, 636, 636, 636,
/* 2585 */ 636, 0, 0, 0, 0, 132, 0, 0, 0, 176, 145, 145, 164, 145, 144, 144, 148, 19860, 0, 100, 100, 0, 0, 117, 0, 119,
/* 2611 */ 0, 0, 100, 636, 636, 636, 650, 0, 0, 173, 166, 166, 166, 19878, 166, 0, 0, 136, 638, 615, 638, 638, 0, 0, 0,
/* 2636 */ 0, 0, 0, 134, 173, 0, 0, 0, 0, 0, 0, 0, 4608, 0, 67, 68, 0, 2376, 2376, 0, 0, 67, 67, 67, 67, 0, 8704, 0, 0,
/* 2665 */ 0, 1084, 0, 0, 0, 0, 0, 1870, 0, 0, 0, 0, 7424, 7680, 144, 144, 144, 163, 144, 0, 0, 0, 0, 0, 0, 0, 1536, 64,
/* 2693 */ 0, 69, 0, 2376, 2376, 0, 0, 8448, 0, 0, 0, 8448, 8448, 8448, 8448, 0, 0, 0, 0, 100, 598, 0, 68, 7168, 0, 0,
/* 2719 */ 88, 89, 0, 0, 0, 144, 163, 0, 169, 0, 35072, 0, 94, 95, 96, 0, 0, 0, 144, 163, 168, 0, 0, 95, 7262, 96, 7262,
/* 2746 */ 100, 598, 0, 88, 89, 0, 0, 2560, 0, 0, 0, 0, 119, 0, 0, 0, 171, 144, 163, 163, 163, 163, 163, 0, 0, 142, 0,
/* 2773 */ 144, 134, 0, 100, 636, 0, 0, 0, 0, 0, 144, 147, 0, 636, 821, 821, 821, 821, 821, 821, 821, 821, 0, 0, 0, 68,
/* 2799 */ 0, 0, 2560, 2154, 107, 107, 0, 0, 635, 636, 636, 636, 636, 0, 0, 0, 0, 0, 0, 0, 63, 1536, 0, 160, 0, 144,
/* 2825 */ 163, 168, 0, 0, 0, 1084, 0, 0, 63, 64, 35072, 0, 0, 0, 96, 1890, 0, 0, 0, 2560, 0, 0, 0, 0, 96, 1890, 0, 0,
/* 2853 */ 68, 0, 0, 2560, 0, 108, 0, 0, 0, 9728, 0, 0, 0, 0, 119, 110, 0, 112, 0, 9043, 9043, 9043, 77, 9043, 9043,
/* 2878 */ 9043, 9043, 0, 0, 0, 0, 119, 0, 0, 100, 110, 0, 0, 100, 100, 100, 598, 0, 0, 635, 649, 649, 649, 649, 0, 0,
/* 2904 */ 63, 0, 63, 0, 0, 0, 0, 8960, 0, 0, 0, 65, 0, 65, 0, 0, 0, 110, 100, 636, 636, 636, 636, 0, 0, 0, 131, 0, 0,
/* 2933 */ 0, 144, 165, 0, 0, 0, 118, 119, 0, 0, 100, 636, 636, 636, 636, 139, 1870, 0, 0, 0, 1870, 0, 0, 0, 145, 164,
/* 2959 */ 0, 0, 0, 100, 100, 100, 567, 0, 1870, 1870, 1870, 1870, 0, 0, 0, 0, 119, 120, 0, 100, 35072, 0, 0, 0, 96, 0,
/* 2985 */ 0, 9216, 140, 0, 0, 0, 144, 134, 0, 100, 636, 0, 0, 0, 0, 155, 144, 144, 110, 110, 0, 100, 663, 0, 0, 64, 0,
/* 3012 */ 64, 0, 0, 0, 68, 68, 0, 91, 0, 0, 68, 70, 2376, 2376, 821, 821, 0, 0, 821, 821, 0, 0, 0, 0, 0, 0, 0, 5120, 0,
/* 3041 */ 0, 68, 71, 2376, 2376, 821, 821, 0, 0, 3584, 0, 0, 0, 0, 3584, 3584, 3584, 0, 3584, 3584, 3584, 3584, 0, 0,
/* 3065 */ 0, 0, 56, 56, 56, 0, 68, 104, 0, 2560, 2154, 0, 0, 0, 156, 157, 0, 0, 0, 0, 163, 0, 0, 0, 0, 567, 567, 567,
/* 3093 */ 1024, 0, 1890, 0, 100, 100, 100, 598, 114, 636, 0, 129, 0, 0, 0, 0, 0, 58, 0, 0, 100, 636, 0, 153, 0, 0, 0,
/* 3120 */ 144, 144, 144, 163, 144, 144, 144, 134, 134, 0, 100, 100, 159, 115, 0, 0, 0, 119, 0, 0, 100, 636, 0, 0, 0,
/* 3145 */ 154, 0, 144, 163, 163, 163, 163, 163, 110, 636, 128, 0, 0, 0, 0, 0, 0, 10752, 0, 9984, 0, 0, 144, 144, 144,
/* 3170 */ 163, 144, 144, 134, 134, 0, 100, 0, 0, 0, 163, 144, 172, 165, 174, 68, 0, 105, 2560, 0, 0, 0, 0, 119, 121, 0,
/* 3196 */ 100, 0, 1890, 0, 100, 100, 112, 598, 0, 0, 8192, 68, 8704, 0, 0, 0, 144, 163, 0, 0, 170, 144, 156, 134, 134,
/* 3221 */ 0, 100, 100, 0, 0, 9312, 0, 100, 598, 0, 68, 0, 2376, 2376, 0, 63, 0, 0, 144, 163, 163, 163, 163, 175, 0, 0,
/* 3247 */ 9472, 0, 0, 0, 63, 64, 100, 636, 152, 0, 0, 0, 0, 144, 144, 174, 175, 144, 10240, 0, 0, 144, 163, 0, 0, 0,
/* 3273 */ 156, 162, 0, 0, 0, 0, 567, 567, 567, 1084, 639, 0, 0, 0, 0, 0, 0, 0, 79, 0, 79, 0, 146, 163, 163, 163, 163,
/* 3300 */ 163, 0, 62, 821, 821, 0, 0, 0, 0, 133, 134, 0, 100, 35165, 0, 0, 0, 96, 1890, 99, 0, 68, 0, 2376, 2376, 0,
/* 3326 */ 77, 0, 9040, 77, 77, 77, 77, 9040, 111, 1890, 0, 100, 100, 100, 598, 0, 68, 0, 2376, 2376, 0, 5632, 0, 0, 96,
/* 3351 */ 0, 100, 615, 0, 68, 0, 2376, 2376, 0, 0, 59, 59, 0, 0, 0, 0, 119, 0, 0, 101, 0, 141, 0, 0, 144, 134, 0, 100,
/* 3379 */ 636, 0, 0, 2957, 0, 0, 144, 163, 163, 163, 163, 163, 0, 144, 144, 134, 134, 158, 100, 100, 0, 68, 0, 2376,
/* 3403 */ 2376, 821, 821, 0, 0, 161, 144, 163, 0, 0, 0, 144, 166, 0, 0, 0, 144, 163, 0, 0, 0, 0, 8448, 0, 8448, 0, 0,
/* 3430 */ 10752, 0, 10752, 0, 0, 10752, 10752, 10752, 0, 10752, 10752, 10752, 10752, 10752, 10752, 10752, 10752, 0, 0,
/* 3449 */ 0, 0, 146, 134, 0, 100, 3072, 3072, 3072, 3072, 3072, 3072, 3072, 3072, 0, 0, 3072, 3072, 3072, 3072, 0, 0,
/* 3471 */ 0, 0
};

const int EbnfParser::EXPECTED[] =
{
/*   0 */ 89, 99, 156, 96, 103, 110, 114, 118, 122, 126, 130, 134, 138, 142, 150, 160, 164, 167, 106, 179, 187, 203,
/*  22 */ 167, 191, 200, 144, 207, 215, 146, 213, 216, 144, 211, 215, 145, 212, 221, 217, 225, 223, 214, 221, 225, 221,
/*  44 */ 194, 234, 255, 258, 229, 233, 238, 170, 242, 173, 175, 246, 248, 252, 183, 264, 182, 196, 182, 182, 153, 182,
/*  66 */ 92, 182, 182, 182, 180, 182, 92, 182, 182, 182, 180, 182, 91, 181, 182, 182, 180, 91, 182, 182, 262, 182, 182,
/*  89 */ 4, 16777216, 0, 0, 0, 64, 128, 34, 134219778, 65538, 33554434, 1073741826, 2, 262152, -2080374782, 24, 8,
/* 106 */ 1920, 8388610, 805306368, 268435456, 1920, 813697030, 270538790, -2046820286, 278927398, 138510374, 2138278,
/* 117 */ 278927398, -1809835994, -1809835930, 278943782, 2203814, 952207398, 948013094, 952141862, 952207398,
/* 126 */ -1776281498, 278984870, 952862758, 279050406, 986417254, 280098982, 312604838, 313653414, -1125410714,
/* 135 */ 280754342, 313260198, 314308774, -1800668954, -1799620378, -1767114522, -1766065946, 4, 0, 2, 2, 2, 0, 0,
/* 149 */ 1024, 33554432, 1073741824, 0, 8, 0, 0, 8, 8, 38, 134217734, 262144, 0, 32, 32, 134217728, 67108864,
/* 166 */ (int) 0x80000000, 16, 0, 0, 512, 0, 0, 512, 17, 524, 513, 524, 524, 4096, 64, 128, 0, 0, 0, 0, 16, 335544320,
/* 188 */ 939524096, 4096, 1006632960, 1152, 805306368, 268435456, 4096, 0, 0, 2, 64, 128, 4096, 64, 128, 2, 2,
/* 205 */ 33554432, 16, 0, 1152, 268435456, 536870912, 0, 1024, 268435456, 536870912, 4096, 4096, 4096, 2, 2, 0, 4096,
/* 222 */ 4096, 4096, 4096, 0, 268435456, 536870912, 4096, 1, 0, 2, 192, 0, 32, 0, 0, 16, 17, 0, 512, 12, 524, 0, 512,
/* 245 */ 512, 524, 513, 525, 525, 525, 541, 541, 0, 2, 0, 2, 256, 0, 4, 0, 512, 0, 64, 0, 0, 256, 0
};

const wchar_t *EbnfParser::TOKEN[] =
{
  L"(0)",
  L"Whitespace",
  L"Name",
  L"Space",
  L"DirPIContents",
  L"StringLiteral",
  L"CaretName",
  L"CharCode",
  L"Char",
  L"CharRange",
  L"CharCodeRange",
  L"EOF",
  L"EquivalenceLookAhead",
  L"'$'",
  L"'&'",
  L"'('",
  L"')'",
  L"'*'",
  L"'*/'",
  L"'+'",
  L"'-'",
  L"'.'",
  L"'/'",
  L"'/*'",
  L"':'",
  L"'::='",
  L"'<<'",
  L"'<?'",
  L"'<?ENCORE?>'",
  L"'<?TOKENS?>'",
  L"'=='",
  L"'>>'",
  L"'?'",
  L"'?>'",
  L"'['",
  L"'[^'",
  L"'\\\\'",
  L"']'",
  L"'definition'",
  L"'explicit'",
  L"'ws'",
  L"'|'"
};

#endif

// End
