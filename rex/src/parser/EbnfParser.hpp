// This file was generated on Mon Feb 10, 2025 22:32 (UTC+01) by REx v6.2-SNAPSHOT which is Copyright (c) 1979-2025 by Gunther Rademacher <grd@gmx.net>
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
        lookahead2W(41);            // Whitespace | Name | StringLiteral | CaretName | EOF | '(' | ')' | '*' | '+' |
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
    lookahead1W(39);                // Whitespace | Name | StringLiteral | EOF | '(' | ')' | '*' | '+' | '/' | '/*' |
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
    lookahead1W(38);                // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
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
      lookahead1W(38);              // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
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
      lookahead1W(37);              // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '(' | '.' | '/*' | '<?ENCORE?>' | '[' | '[^' | '|'
      parse_LexicalSequence();
                                                            #line 129 "EbnfParser.ebnf"
                                                            Node *rhs = currentNode->isolateLastChild();
                                                            currentNode->addChild(new Context(currentNode->isolateLastChild(), rhs));
                                                            #line 657 "EbnfParser.hpp"
    }
  }

  void parse_LexicalSequence()
  {
                                                            #line 133 "EbnfParser.ebnf"
                                                            descend(new Sequence());
                                                            #line 665 "EbnfParser.hpp"
    switch (l1)
    {
    case 2:                         // Name
      lookahead2W(52);              // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '-' | '.' | '/*' |
                                    // '::=' | '<<' | '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '\\' | '|'
      switch (lk)
      {
      case 2050:                    // Name '?'
        lookahead3W(44);            // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '-' | '.' | '/*' | '::=' | '<?ENCORE?>' | '[' | '[^' | '|'
        break;
      }
      break;
    case 5:                         // StringLiteral
      lookahead2W(50);              // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '-' | '.' | '/*' |
                                    // '<<' | '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '|'
      break;
    case 21:                        // '.'
      lookahead2W(48);              // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '*' | '+' | '-' | '.' | '/*' | '::=' | '<?ENCORE?>' | '?' |
                                    // '[' | '[^' | '|'
      switch (lk)
      {
      case 2069:                    // '.' '?'
        lookahead3W(44);            // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
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
        lookahead1W(42);            // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
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
                                                            #line 738 "EbnfParser.hpp"
          }
          break;
        default:
          for (;;)
          {
            lookahead1W(40);        // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '.' | '/*' | '<?ENCORE?>' | '[' | '[^' | '|'
            switch (l1)
            {
            case 2:                 // Name
              lookahead2W(51);      // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '.' | '/*' | '::=' |
                                    // '<<' | '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '\\' | '|'
              switch (lk)
              {
              case 2050:            // Name '?'
                lookahead3W(43);    // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '.' | '/*' | '::=' | '<?ENCORE?>' | '[' | '[^' | '|'
                break;
              }
              break;
            case 5:                 // StringLiteral
              lookahead2W(49);      // Whitespace | Name | StringLiteral | CaretName | CharCode | EOF |
                                    // EquivalenceLookAhead | '$' | '&' | '(' | ')' | '*' | '+' | '.' | '/*' | '<<' |
                                    // '<?ENCORE?>' | '>>' | '?' | '[' | '[^' | '|'
              break;
            case 21:                // '.'
              lookahead2W(47);      // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
                                    // '&' | '(' | ')' | '*' | '+' | '.' | '/*' | '::=' | '<?ENCORE?>' | '?' | '[' |
                                    // '[^' | '|'
              switch (lk)
              {
              case 2069:            // '.' '?'
                lookahead3W(43);    // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
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
                                                            #line 811 "EbnfParser.hpp"
  }

  void parse_LexicalItem()
  {
    parse_LexicalPrimary();
    lookahead1W(46);                // Whitespace | Name | StringLiteral | CharCode | EOF | EquivalenceLookAhead | '$' |
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
                                                            #line 831 "EbnfParser.hpp"
        }
        break;
      case 17:                      // '*'
        {
          consume(17);              // '*'
                                                            #line 146 "EbnfParser.ebnf"
                                                            wrap(new ZeroOrMore());
                                                            #line 839 "EbnfParser.hpp"
        }
        break;
      default:
        {
          consume(19);              // '+'
                                                            #line 147 "EbnfParser.ebnf"
                                                            wrap(new OneOrMore());
                                                            #line 847 "EbnfParser.hpp"
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
                                                            #line 872 "EbnfParser.hpp"
      }
      break;
    case 5:                         // StringLiteral
      {
        consume(5);                 // StringLiteral
                                                            #line 150 "EbnfParser.ebnf"
                                                            currentNode->addChild(new String(currentToken().copy()));
                                                            #line 880 "EbnfParser.hpp"
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
                                                            #line 895 "EbnfParser.hpp"
      }
      break;
    case 7:                         // CharCode
      {
        consume(7);                 // CharCode
                                                            #line 153 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharCode(charCodeValue(currentChar() + 1)));
                                                            #line 903 "EbnfParser.hpp"
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
                                                            #line 921 "EbnfParser.hpp"
        lookahead1W(45);            // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
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
                                                            #line 936 "EbnfParser.hpp"
        lookahead1W(45);            // Whitespace | Name | StringLiteral | CaretName | EOF | EquivalenceLookAhead |
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
                                                            #line 954 "EbnfParser.hpp"
  }

  void parse_CharClass()
  {
                                                            #line 160 "EbnfParser.ebnf"
                                                            bool complement = false;
                                                            #line 961 "EbnfParser.hpp"
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
                                                            #line 972 "EbnfParser.hpp"
      }
      break;
    }
                                                            #line 163 "EbnfParser.ebnf"
                                                            descend(new CharClass());
                                                            #line 978 "EbnfParser.hpp"
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
                                                            #line 989 "EbnfParser.hpp"
        }
        break;
      case 7:                       // CharCode
        {
          consume(7);               // CharCode
                                                            #line 165 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharCode(charCodeValue(currentChar() + 1)));
                                                            #line 997 "EbnfParser.hpp"
        }
        break;
      case 9:                       // CharRange
        {
          consume(9);               // CharRange
                                                            #line 166 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharRange(b0, *currentChar(), *(currentChar() + 2)));
                                                            #line 1005 "EbnfParser.hpp"
        }
        break;
      default:
        {
          consume(10);              // CharCodeRange
                                                            #line 168 "EbnfParser.ebnf"
                                                            int minValue = charCodeValue(currentChar() + 1);
                                                            currentNode->addChild(new CharCodeRange(b0, minValue, charCodeValue(wcschr(currentChar(), L'-') + 2)));
                                                            #line 1014 "EbnfParser.hpp"
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
                                                            #line 1026 "EbnfParser.hpp"
    consume(37);                    // ']'
                                                            #line 173 "EbnfParser.ebnf"
                                                            if (complement)
                                                            {
                                                              currentNode->addChild(new Complement(static_cast<CharClass *>(currentNode->isolateLastChild())));
                                                            }
                                                            #line 1033 "EbnfParser.hpp"
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
                                                            #line 1067 "EbnfParser.hpp"
      }
      break;
    default:
      {
        consume(38);                // 'definition'
                                                            #line 183 "EbnfParser.ebnf"
                                                            Production *p = static_cast<Production *>(currentNode->lastChild);
                                                            p->wsExplicit = true;
                                                            setWhitespaceDefinition(p);
                                                            #line 1077 "EbnfParser.hpp"
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
                                                            #line 1098 "EbnfParser.hpp"
    lookahead1W(16);                // Whitespace | '<<' | '>>'
    switch (l1)
    {
    case 31:                        // '>>'
      {
        consume(31);                // '>>'
                                                            #line 193 "EbnfParser.ebnf"
                                                            preference->addLhs(currentNode->isolateLastChild());
                                                            #line 1107 "EbnfParser.hpp"
        for (;;)
        {
          lookahead1W(10);          // Whitespace | Name | StringLiteral
          parse_NameOrString();
                                                            #line 194 "EbnfParser.ebnf"
                                                            preference->addRhs(currentNode->isolateLastChild());
                                                            #line 1114 "EbnfParser.hpp"
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
                                                            #line 1171 "EbnfParser.hpp"
        for (;;)
        {
          lookahead1W(10);          // Whitespace | Name | StringLiteral
          parse_NameOrString();
                                                            #line 197 "EbnfParser.ebnf"
                                                            preference->addLhs(currentNode->isolateLastChild());
                                                            #line 1178 "EbnfParser.hpp"
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
                                                            #line 1233 "EbnfParser.hpp"
  }

  void parse_Delimiter()
  {
    consume(2);                     // Name
                                                            #line 200 "EbnfParser.ebnf"
                                                            Delimiter *delimiter = new Delimiter(new Ref(currentToken().copy()));
                                                            #line 1241 "EbnfParser.hpp"
    lookahead1W(6);                 // Whitespace | '\\'
    consume(36);                    // '\\'
    for (;;)
    {
      lookahead1W(10);              // Whitespace | Name | StringLiteral
      parse_NameOrString();
                                                            #line 201 "EbnfParser.ebnf"
                                                            delimiter->addRhs(currentNode->isolateLastChild());
                                                            #line 1250 "EbnfParser.hpp"
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
                                                            #line 1302 "EbnfParser.hpp"
  }

  void parse_Equivalence()
  {
    consume(12);                    // EquivalenceLookAhead
                                                            #line 203 "EbnfParser.ebnf"
                                                            Equivalence *equivalence = new Equivalence();
                                                            #line 1310 "EbnfParser.hpp"
    lookahead1W(12);                // Whitespace | StringLiteral | '['
    parse_EquivalenceCharRange();
                                                            #line 204 "EbnfParser.ebnf"
                                                            equivalence->setLhs(currentNode->isolateLastChild());
                                                            #line 1315 "EbnfParser.hpp"
    lookahead1W(5);                 // Whitespace | '=='
    consume(30);                    // '=='
    lookahead1W(12);                // Whitespace | StringLiteral | '['
    parse_EquivalenceCharRange();
                                                            #line 207 "EbnfParser.ebnf"
                                                            equivalence->setRhs(currentNode->isolateLastChild());
                                                            currentNode->addChild(equivalence);
                                                            #line 1323 "EbnfParser.hpp"
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
                                                            #line 1335 "EbnfParser.hpp"
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
                                                            #line 1349 "EbnfParser.hpp"
          }
          break;
        case 7:                     // CharCode
          {
            consume(7);             // CharCode
                                                            #line 214 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharCode(charCodeValue(currentChar() + 1)));
                                                            #line 1357 "EbnfParser.hpp"
          }
          break;
        case 9:                     // CharRange
          {
            consume(9);             // CharRange
                                                            #line 215 "EbnfParser.ebnf"
                                                            currentNode->addChild(new CharRange(b0, *currentChar(), *(currentChar() + 2)));
                                                            #line 1365 "EbnfParser.hpp"
          }
          break;
        default:
          {
            consume(10);            // CharCodeRange
                                                            #line 217 "EbnfParser.ebnf"
                                                            int minValue = charCodeValue(currentChar() + 1);
                                                            currentNode->addChild(new CharCodeRange(b0, minValue, charCodeValue(wcschr(currentChar(), L'-') + 2)));
                                                            #line 1374 "EbnfParser.hpp"
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
                                                            #line 1390 "EbnfParser.hpp"
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
                                                            #line 1402 "EbnfParser.hpp"
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
    int i0 = t * 178 + s - 1;
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
/* 30 */ 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53
};

const int EbnfParser::TRANSITION[] =
{
/*    0 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*   18 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 3181, 1696, 3187, 1698,
/*   36 */ 1698, 1698, 1766, 3201, 3057, 1706, 3299, 3061, 2749, 2218, 1716, 3127, 1922, 1726, 1737, 2743, 1745, 2667,
/*   54 */ 1753, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 3038, 1763, 3044, 1698, 1698, 1698, 1766, 1883,
/*   72 */ 3057, 1706, 2757, 3061, 3320, 2218, 1774, 3152, 1850, 1786, 1798, 2876, 1806, 2262, 1753, 1883, 1883, 1883,
/*   90 */ 1883, 1883, 1883, 1883, 1883, 1883, 3181, 1696, 1823, 1698, 1698, 1698, 1766, 3264, 2036, 1831, 2779, 2040,
/*  108 */ 2749, 3388, 1716, 3127, 1922, 1726, 1737, 2743, 1745, 2667, 1753, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  126 */ 1883, 1883, 1883, 1883, 1845, 1883, 1883, 1883, 1883, 1708, 2036, 1831, 2573, 2040, 2749, 3362, 1865, 2905,
/*  144 */ 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 3269,
/*  162 */ 1892, 2158, 2158, 2158, 2161, 3063, 2036, 1831, 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284,
/*  180 */ 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1917, 1930, 3137, 1937,
/*  198 */ 1943, 1708, 2036, 1956, 2827, 2040, 2749, 3362, 1974, 2905, 1979, 1864, 1858, 2284, 1873, 2175, 1881, 1883,
/*  216 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1845, 1987, 2585, 1994, 2000, 1708, 2036, 1831,
/*  234 */ 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883,
/*  252 */ 1883, 1883, 1883, 1883, 1883, 1883, 1845, 2399, 2399, 2013, 2019, 1708, 2036, 1831, 2573, 2040, 2749, 3362,
/*  270 */ 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  288 */ 1883, 2032, 2048, 2062, 2062, 2062, 2065, 1708, 2073, 1831, 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864,
/*  306 */ 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1845, 2085,
/*  324 */ 2092, 2097, 2100, 1708, 2036, 1831, 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175,
/*  342 */ 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1815, 1845, 2114, 2108, 2122, 2125, 1708,
/*  360 */ 2036, 1831, 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883,
/*  378 */ 1883, 1883, 1883, 1883, 1883, 1883, 2805, 1883, 1845, 1883, 1718, 2133, 2138, 2151, 2036, 2169, 2772, 2040,
/*  396 */ 1837, 3362, 2192, 2183, 2143, 2191, 2200, 2661, 2208, 3112, 2216, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  414 */ 1883, 1883, 1883, 1883, 1845, 1883, 1755, 2226, 2231, 1708, 2036, 1831, 2573, 2040, 2749, 3362, 1865, 2905,
/*  432 */ 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  450 */ 1845, 1883, 1883, 2244, 2248, 1708, 2036, 2256, 2573, 2040, 2270, 2278, 1865, 2310, 1948, 1864, 1858, 2284,
/*  468 */ 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2318, 2324, 3288, 2324,
/*  486 */ 2327, 1708, 2036, 1831, 2573, 2040, 2335, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883,
/*  504 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2968, 2375, 2350, 2343, 2358, 2364, 2370, 2785, 2036, 2383,
/*  522 */ 2566, 2040, 2882, 3206, 2397, 2302, 2005, 3134, 2407, 3460, 2415, 3091, 1813, 1883, 1883, 1883, 1883, 1883,
/*  540 */ 1883, 1883, 1883, 1883, 1883, 1883, 1845, 1883, 1883, 1883, 1909, 1708, 2036, 3399, 2573, 2551, 2423, 2431,
/*  558 */ 1865, 2439, 1948, 3454, 1858, 3466, 1873, 3472, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  576 */ 2447, 1884, 2460, 1883, 1904, 2466, 2470, 2478, 2036, 1831, 2573, 2040, 2749, 3362, 2486, 2905, 1948, 2754,
/*  594 */ 1966, 2452, 1873, 1962, 1882, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2834, 2496, 2504,
/*  612 */ 2519, 2525, 2533, 1708, 2547, 1831, 2559, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175,
/*  630 */ 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1729, 1883, 1845, 1883, 1883, 1883, 1883, 2593,
/*  648 */ 2036, 1831, 2511, 2040, 2749, 3274, 1865, 2601, 2024, 1864, 2609, 2840, 2623, 2852, 2631, 1883, 1883, 1883,
/*  666 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2641, 2989, 1790, 1789, 2647, 1708, 2655, 1831, 2573, 2675,
/*  684 */ 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2693, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  702 */ 1883, 1883, 3438, 3440, 2701, 1883, 3376, 2707, 2712, 1708, 2725, 2737, 2765, 2729, 2749, 3362, 1865, 2905,
/*  720 */ 1948, 1864, 1858, 2284, 2793, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801,
/*  738 */ 2813, 2860, 2860, 2860, 2862, 1708, 2036, 3237, 2573, 2551, 2423, 2431, 1865, 2439, 1948, 3454, 1858, 3466,
/*  756 */ 1873, 3472, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860,
/*  774 */ 2862, 1708, 2036, 3237, 2573, 2551, 2423, 2431, 2870, 2439, 1948, 3454, 1858, 3466, 1873, 3472, 1881, 1883,
/*  792 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 3237,
/*  810 */ 2573, 2890, 2423, 2431, 1865, 2439, 2296, 3454, 1858, 2898, 1873, 3472, 1881, 1883, 1883, 1883, 1883, 1883,
/*  828 */ 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2040, 2335, 3362,
/*  846 */ 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  864 */ 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2040, 2335, 3362, 2928, 2905, 1948, 1864,
/*  882 */ 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860,
/*  900 */ 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2040, 2335, 3085, 1865, 2905, 1948, 2615, 1858, 2284, 1873, 2175,
/*  918 */ 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708,
/*  936 */ 2036, 2913, 2573, 2040, 2335, 2290, 1865, 2905, 3078, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883,
/*  954 */ 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2040,
/*  972 */ 2335, 3362, 1865, 2905, 1948, 3342, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/*  990 */ 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2040, 2335, 3362, 1865, 2905,
/* 1008 */ 1948, 1864, 1858, 3106, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801,
/* 1026 */ 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2077, 2335, 3362, 1865, 2905, 1948, 1864, 1858, 2284,
/* 1044 */ 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2580, 2943, 2949, 3250, 2957,
/* 1062 */ 2963, 1708, 2036, 1831, 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883,
/* 1080 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1776, 1883, 2976, 1883, 1778, 1883, 1899, 3167, 2036, 1831,
/* 1098 */ 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883,
/* 1116 */ 1883, 1883, 1883, 1883, 3233, 1883, 2984, 1883, 1883, 1883, 1883, 1708, 2036, 1706, 3218, 3061, 2997, 1883,
/* 1134 */ 3005, 3010, 1948, 1864, 1858, 2284, 1873, 3018, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/* 1152 */ 1883, 1883, 3026, 2538, 2539, 3032, 3052, 1708, 2036, 1831, 3071, 2040, 2749, 3362, 1865, 2905, 1948, 1864,
/* 1170 */ 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860,
/* 1188 */ 2860, 2860, 2862, 1708, 2036, 3237, 2573, 2551, 2423, 2431, 1865, 2439, 3099, 3454, 1858, 3466, 1873, 3472,
/* 1206 */ 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 3120, 2860, 2860, 2860, 2862, 1708,
/* 1224 */ 2036, 3237, 2573, 2551, 2423, 2431, 1865, 2439, 1948, 3454, 1858, 3466, 1873, 3472, 1881, 1883, 1883, 1883,
/* 1242 */ 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 3145, 2860, 2860, 2860, 2862, 1708, 3160, 3237, 2573, 2551,
/* 1260 */ 2423, 2431, 1865, 2439, 1948, 3454, 1858, 3466, 1873, 3472, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/* 1278 */ 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 3237, 2573, 3175, 2423, 2431, 1865, 2439,
/* 1296 */ 1948, 3454, 1858, 3466, 1873, 3472, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801,
/* 1314 */ 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2040, 2335, 3195, 3214, 2905, 3226, 3245, 1858, 3258,
/* 1332 */ 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860,
/* 1350 */ 2862, 1708, 2036, 2913, 2573, 2040, 2335, 3282, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883,
/* 1368 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913,
/* 1386 */ 2573, 2040, 2335, 3362, 3296, 2905, 1948, 1864, 1858, 2284, 1873, 3307, 1881, 1883, 1883, 1883, 1883, 1883,
/* 1404 */ 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 2040, 2335, 3362,
/* 1422 */ 1865, 2905, 1948, 1864, 1858, 2389, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/* 1440 */ 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2573, 3315, 2335, 3362, 1865, 2905, 1948, 1864,
/* 1458 */ 1858, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860,
/* 1476 */ 2860, 2860, 2862, 2488, 2036, 2913, 2573, 2040, 3328, 3362, 1865, 2920, 1948, 1864, 3336, 2284, 3350, 2175,
/* 1494 */ 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708,
/* 1512 */ 2036, 2913, 2573, 2040, 2335, 3362, 1865, 2905, 1948, 3358, 1858, 3370, 1873, 2175, 1881, 1883, 1883, 1883,
/* 1530 */ 1883, 1883, 1883, 1883, 1883, 1883, 2804, 3384, 2813, 2860, 2860, 2860, 2862, 1708, 2036, 2913, 2820, 2040,
/* 1548 */ 2335, 3362, 3396, 2935, 2236, 1864, 1858, 2846, 3407, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/* 1566 */ 1883, 1883, 2804, 2801, 2813, 2860, 2860, 2860, 2862, 1708, 2054, 3415, 2573, 2040, 3423, 3362, 1865, 2905,
/* 1584 */ 3431, 1864, 3448, 2284, 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2633,
/* 1602 */ 1845, 3480, 3485, 3490, 3493, 1708, 2036, 1831, 2573, 2040, 2749, 3362, 1865, 2905, 1948, 1864, 1858, 2284,
/* 1620 */ 1873, 2175, 1881, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1845, 1883, 1883, 1883,
/* 1638 */ 1909, 1708, 2036, 1831, 2573, 2040, 2335, 3362, 1865, 2905, 1948, 1864, 1858, 2284, 1873, 2175, 1881, 1883,
/* 1656 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 2680, 2717, 2685, 3501, 3501, 3504, 1883, 1883, 1883,
/* 1674 */ 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883, 1883,
/* 1692 */ 1883, 1883, 1883, 1883, 1085, 1085, 568, 568, 568, 568, 568, 568, 568, 568, 0, 35072, 0, 0, 0, 0, 0, 0, 0,
/* 1715 */ 64, 113, 626, 0, 0, 0, 0, 0, 0, 0, 4608, 101, 650, 651, 0, 0, 0, 0, 0, 59, 0, 0, 145, 145, 145, 135, 135, 0,
/* 1743 */ 101, 664, 0, 0, 163, 164, 164, 164, 164, 164, 145, 178, 0, 0, 0, 0, 0, 0, 0, 5120, 1024, 1024, 568, 568, 568,
/* 1768 */ 568, 568, 568, 0, 0, 568, 113, 636, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 101, 650, 664, 0, 0, 0, 0, 0, 68, 0, 0, 0,
/* 1798 */ 145, 145, 145, 111, 111, 0, 101, 664, 0, 0, 163, 175, 175, 175, 175, 175, 173, 0, 0, 0, 0, 0, 0, 4352, 0,
/* 1823 */ 568, 1085, 1085, 2377, 2377, 568, 568, 568, 0, 35072, 0, 0, 0, 97, 0, 0, 0, 0, 102, 102, 102, 626, 0, 69, 0,
/* 1848 */ 2377, 2377, 0, 0, 0, 0, 0, 134, 111, 0, 145, 145, 145, 135, 135, 0, 101, 101, 637, 0, 0, 0, 0, 0, 0, 0, 0,
/* 1875 */ 145, 164, 164, 164, 164, 164, 145, 145, 0, 0, 0, 0, 0, 0, 0, 0, 58, 0, 69, 0, 2377, 2377, 0, 64, 0, 0, 0, 60,
/* 1903 */ 60, 0, 0, 0, 0, 58, 0, 0, 0, 0, 0, 822, 0, 0, 0, 69, 0, 74, 74, 0, 0, 0, 0, 0, 134, 135, 0, 0, 0, 80, 0, 0,
/* 1935 */ 0, 0, 80, 0, 80, 80, 80, 0, 80, 80, 80, 80, 80, 0, 0, 0, 0, 0, 145, 135, 0, 0, 35072, 0, 0, 0, 98, 0, 0, 0,
/* 1965 */ 0, 145, 145, 145, 135, 135, 0, 101, 0, 101, 637, 0, 0, 131, 0, 0, 0, 0, 0, 145, 135, 150, 0, 0, 3584, 0, 0,
/* 1992 */ 0, 0, 3584, 0, 3584, 3584, 3584, 0, 3584, 3584, 3584, 3584, 3584, 0, 0, 0, 0, 0, 145, 148, 0, 3840, 0, 3840,
/* 2016 */ 3840, 3840, 0, 3840, 3840, 3840, 3840, 3840, 0, 0, 0, 0, 0, 145, 149, 0, 0, 0, 65, 0, 65, 0, 0, 0, 69, 69, 0,
/* 2043 */ 0, 2560, 0, 0, 0, 0, 69, 0, 2377, 2377, 0, 65, 0, 0, 0, 69, 69, 0, 92, 65, 65, 65, 65, 65, 65, 65, 65, 0, 0,
/* 2072 */ 0, 1536, 0, 0, 0, 69, 69, 0, 0, 2560, 0, 109, 0, 0, 4096, 4096, 0, 0, 0, 0, 4096, 4096, 4096, 4096, 0, 4096,
/* 2098 */ 4096, 4096, 4096, 4096, 4096, 4096, 4096, 0, 0, 0, 4352, 4352, 0, 4352, 0, 0, 0, 4352, 0, 0, 0, 0, 0, 4352,
/* 2122 */ 4352, 4352, 4352, 4352, 4352, 4352, 4352, 4352, 0, 0, 0, 0, 4608, 0, 0, 0, 4608, 4608, 4608, 4608, 4608, 0,
/* 2144 */ 0, 0, 0, 0, 146, 135, 0, 86, 0, 0, 0, 0, 0, 0, 64, 64, 64, 64, 64, 64, 64, 64, 0, 0, 0, 0, 35072, 6230, 0, 0,
/* 2174 */ 97, 0, 0, 0, 0, 145, 145, 145, 164, 134, 0, 0, 102, 638, 638, 637, 638, 151, 102, 638, 0, 0, 0, 0, 0, 0, 146,
/* 2201 */ 146, 146, 158, 135, 0, 102, 102, 0, 0, 146, 165, 165, 164, 165, 165, 146, 146, 0, 0, 0, 0, 0, 0, 111, 0, 0,
/* 2227 */ 5120, 0, 0, 0, 5120, 5120, 5120, 5120, 5120, 0, 0, 0, 0, 0, 147, 135, 0, 0, 0, 5376, 0, 5376, 0, 5376, 0,
/* 2252 */ 5376, 822, 0, 0, 93, 35165, 0, 0, 0, 97, 0, 0, 0, 0, 145, 145, 175, 178, 110, 110, 1891, 0, 101, 101, 101,
/* 2277 */ 599, 0, 0, 117, 0, 0, 120, 0, 0, 0, 0, 145, 164, 0, 0, 0, 0, 119, 120, 0, 0, 0, 0, 144, 145, 135, 0, 0, 137,
/* 2306 */ 639, 616, 639, 639, 0, 0, 136, 101, 637, 637, 637, 637, 0, 69, 0, 2377, 2377, 0, 5632, 0, 5632, 5632, 5632,
/* 2329 */ 5632, 5632, 5632, 822, 0, 0, 0, 0, 1891, 0, 101, 101, 101, 599, 75, 5945, 57, 75, 57, 57, 75, 57, 69, 0,
/* 2353 */ 2377, 2377, 75, 57, 57, 5963, 75, 5963, 5963, 57, 75, 75, 5963, 75, 75, 75, 5963, 75, 75, 75, 75, 75, 0, 0,
/* 2377 */ 57, 57, 57, 57, 57, 57, 0, 35072, 599, 0, 0, 97, 0, 0, 0, 0, 145, 164, 0, 170, 101, 639, 0, 0, 0, 0, 0, 0,
/* 2405 */ 3840, 0, 145, 111, 145, 148, 148, 0, 650, 137, 0, 0, 173, 166, 148, 166, 166, 166, 0, 0, 1891, 2148, 101,
/* 2428 */ 101, 101, 599, 0, 0, 2155, 0, 0, 120, 0, 123, 0, 0, 123, 101, 637, 637, 637, 637, 0, 6400, 0, 0, 58, 0, 0, 0,
/* 2455 */ 0, 0, 164, 0, 0, 0, 69, 0, 2377, 2377, 0, 0, 58, 0, 58, 58, 0, 0, 58, 58, 0, 0, 0, 0, 88, 0, 0, 0, 0, 0, 64,
/* 2486 */ 0, 637, 0, 0, 0, 0, 0, 0, 10496, 64, 67, 69, 0, 2377, 2377, 76, 77, 67, 77, 66, 0, 77, 82, 82, 77, 0, 0, 0,
/* 2514 */ 97, 0, 101, 599, 6656, 83, 83, 83, 83, 82, 77, 77, 83, 77, 77, 77, 85, 77, 77, 77, 82, 82, 82, 82, 0, 0, 0,
/* 2541 */ 0, 0, 1871, 0, 0, 0, 65, 0, 6912, 0, 69, 69, 0, 0, 2560, 2155, 0, 0, 0, 6912, 0, 97, 6912, 101, 599, 0, 0, 0,
/* 2569 */ 97, 0, 101, 616, 0, 0, 0, 97, 0, 101, 599, 0, 0, 0, 0, 8960, 0, 0, 0, 0, 0, 3584, 3584, 0, 0, 0, 7936, 0, 0,
/* 2598 */ 0, 0, 64, 0, 19712, 0, 101, 637, 637, 637, 637, 145, 145, 145, 149, 19861, 0, 101, 101, 637, 0, 0, 0, 0, 156,
/* 2623 */ 0, 0, 174, 167, 167, 167, 19879, 167, 145, 174, 0, 0, 0, 0, 0, 0, 10752, 0, 68, 69, 0, 2377, 2377, 0, 0, 68,
/* 2649 */ 68, 68, 68, 0, 8704, 0, 65, 0, 0, 8192, 69, 8704, 0, 0, 0, 0, 146, 165, 0, 0, 0, 0, 145, 145, 175, 176,
/* 2675 */ 66816, 0, 0, 0, 2560, 0, 0, 0, 0, 0, 3072, 0, 0, 3072, 3072, 3072, 3072, 0, 0, 0, 7424, 7680, 145, 145, 145,
/* 2700 */ 164, 0, 70, 0, 2377, 2377, 0, 0, 8448, 0, 0, 0, 8448, 8448, 8448, 8448, 8448, 0, 0, 0, 0, 0, 3072, 3072, 0,
/* 2725 */ 65, 7168, 0, 0, 89, 90, 0, 0, 2560, 0, 0, 0, 0, 35072, 0, 95, 96, 97, 0, 0, 0, 0, 157, 158, 0, 0, 0, 0, 101,
/* 2754 */ 101, 101, 599, 0, 0, 0, 0, 0, 86, 568, 0, 0, 96, 7263, 97, 7263, 101, 599, 0, 0, 0, 97, 0, 102, 599, 0, 0, 0,
/* 2782 */ 97, 0, 86, 599, 0, 0, 0, 0, 4864, 0, 64, 171, 172, 145, 164, 164, 164, 164, 164, 0, 0, 822, 822, 0, 0, 0, 0,
/* 2809 */ 0, 0, 0, 62, 0, 69, 0, 2377, 2377, 822, 822, 0, 0, 0, 97, 0, 103, 599, 0, 0, 0, 98, 0, 101, 599, 0, 0, 0, 66,
/* 2838 */ 0, 66, 0, 0, 0, 0, 145, 167, 0, 0, 0, 0, 145, 168, 0, 0, 0, 0, 145, 19857, 174, 167, 822, 822, 822, 822, 822,
/* 2865 */ 822, 822, 822, 0, 0, 101, 637, 0, 0, 0, 132, 0, 0, 0, 0, 157, 163, 0, 0, 0, 0, 101, 568, 101, 616, 69, 69, 0,
/* 2893 */ 0, 2560, 2155, 108, 108, 0, 0, 161, 0, 145, 164, 169, 0, 0, 0, 101, 637, 637, 637, 637, 0, 35072, 0, 0, 0,
/* 2918 */ 97, 1891, 0, 0, 0, 101, 637, 637, 637, 651, 101, 637, 0, 0, 0, 0, 133, 0, 0, 0, 103, 637, 637, 637, 637, 0,
/* 2944 */ 69, 0, 2377, 2377, 0, 78, 0, 9041, 78, 78, 78, 78, 9041, 9044, 0, 9044, 9044, 9044, 78, 9044, 9044, 9044,
/* 2966 */ 9044, 9044, 0, 0, 0, 0, 57, 57, 57, 0, 0, 69, 0, 2377, 2377, 0, 0, 60, 0, 69, 0, 0, 9728, 0, 0, 0, 0, 68, 68,
/* 2995 */ 0, 0, 111, 111, 0, 0, 101, 101, 101, 599, 101, 637, 0, 0, 0, 0, 0, 111, 101, 637, 637, 637, 637, 111, 0, 0,
/* 3021 */ 0, 145, 145, 145, 164, 0, 69, 0, 2377, 2377, 0, 0, 1871, 0, 0, 0, 1871, 0, 0, 0, 0, 568, 568, 568, 1024,
/* 3046 */ 1024, 0, 0, 568, 568, 568, 0, 1871, 1871, 1871, 1871, 0, 0, 0, 0, 69, 69, 0, 0, 0, 0, 0, 0, 0, 1536, 9216, 0,
/* 3073 */ 0, 9313, 0, 101, 599, 0, 0, 0, 143, 0, 145, 135, 0, 0, 0, 118, 0, 120, 0, 0, 0, 0, 164, 145, 173, 166, 0,
/* 3100 */ 141, 0, 0, 0, 145, 135, 0, 0, 0, 162, 145, 164, 0, 0, 0, 0, 177, 146, 146, 165, 0, 69, 71, 2377, 2377, 822,
/* 3126 */ 822, 0, 0, 0, 636, 637, 637, 637, 637, 137, 639, 0, 0, 0, 0, 0, 80, 80, 0, 0, 69, 72, 2377, 2377, 822, 822,
/* 3152 */ 0, 0, 0, 636, 650, 650, 650, 650, 65, 0, 0, 0, 69, 69, 91, 0, 0, 0, 9472, 0, 0, 0, 64, 69, 69, 105, 0, 2560,
/* 3180 */ 2155, 0, 0, 0, 0, 568, 568, 568, 1085, 1085, 0, 0, 568, 568, 568, 115, 0, 0, 0, 0, 120, 0, 0, 0, 0, 1085, 0,
/* 3207 */ 0, 0, 0, 0, 120, 121, 0, 101, 637, 0, 130, 0, 0, 0, 0, 0, 101, 599, 0, 140, 0, 0, 0, 0, 145, 135, 0, 0, 0,
/* 3236 */ 9728, 0, 0, 0, 0, 0, 97, 1891, 0, 101, 101, 637, 0, 154, 0, 0, 0, 0, 78, 9044, 9044, 0, 160, 0, 0, 0, 145,
/* 3263 */ 164, 0, 0, 0, 0, 1085, 0, 0, 64, 0, 64, 0, 0, 0, 0, 0, 120, 122, 0, 0, 116, 0, 0, 0, 120, 0, 0, 0, 0, 5632,
/* 3293 */ 5632, 5632, 0, 101, 637, 129, 0, 0, 0, 0, 0, 86, 599, 0, 0, 9984, 0, 0, 145, 145, 145, 164, 69, 69, 0, 106,
/* 3319 */ 2560, 0, 0, 0, 0, 101, 101, 101, 568, 0, 0, 1891, 0, 101, 101, 113, 599, 145, 145, 157, 135, 135, 0, 101,
/* 3343 */ 101, 637, 0, 0, 0, 155, 0, 0, 0, 145, 164, 164, 164, 164, 176, 101, 101, 637, 153, 0, 0, 0, 0, 0, 120, 0, 0,
/* 3370 */ 0, 10240, 0, 0, 145, 164, 0, 0, 0, 0, 8448, 0, 0, 8448, 0, 63, 822, 822, 0, 0, 0, 0, 0, 120, 111, 0, 101,
/* 3397 */ 640, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0, 0, 147, 164, 164, 164, 164, 164, 0, 35166, 0, 0, 0, 97, 1891, 100, 0,
/* 3424 */ 112, 1891, 0, 101, 101, 101, 599, 0, 0, 142, 0, 0, 145, 135, 0, 0, 55, 0, 0, 0, 0, 0, 0, 8448, 145, 145, 145,
/* 3451 */ 135, 135, 159, 101, 101, 637, 0, 0, 2958, 0, 0, 0, 0, 145, 166, 0, 0, 0, 0, 145, 164, 169, 0, 0, 0, 145, 145,
/* 3478 */ 145, 164, 0, 10752, 0, 10752, 0, 0, 10752, 10752, 10752, 0, 10752, 10752, 10752, 10752, 10752, 10752, 10752,
/* 3497 */ 10752, 0, 0, 0, 3072, 3072, 3072, 3072, 3072, 3072, 3072, 3072, 0, 0, 0
};

const int EbnfParser::EXPECTED[] =
{
/*   0 */ 89, 102, 95, 99, 106, 109, 113, 117, 121, 125, 129, 133, 137, 141, 173, 153, 156, 160, 167, 180, 259, 171,
/*  22 */ 160, 177, 184, 144, 216, 250, 146, 248, 189, 144, 246, 250, 145, 247, 188, 190, 210, 251, 249, 188, 262, 188,
/*  44 */ 252, 244, 194, 91, 241, 205, 238, 214, 220, 223, 228, 226, 232, 235, 147, 208, 197, 149, 201, 148, 162, 163,
/*  66 */ 148, 201, 148, 148, 199, 148, 148, 201, 148, 148, 199, 148, 148, 200, 148, 148, 199, 148, 256, 148, 198, 148,
/*  88 */ 148, 4, 16777216, 0, 0, 4, 0, 8, 8, 38, 134217734, 34, 134219778, 65538, 33554434, 1073741826, 2, 262152,
/* 106 */ -2080374782, 24, 8, 1920, 813697030, 270538790, -2046820286, 278927398, 138510374, 2138278, 278927398,
/* 117 */ -1809835994, -1809835930, 278943782, 2203814, 952207398, 948013094, 952141862, 952207398, -1776281498,
/* 126 */ 278968486, 278984870, 952862758, 279050406, 986417254, 280098982, 312604838, 313653414, -1125410714,
/* 135 */ 280754342, 313260198, 314308774, -1800668954, -1799620378, -1767114522, -1766065946, 4, 0, 2, 2, 2, 2, 0, 0,
/* 150 */ 0, 0, 2, 8, 262144, 0, 32, 134217728, 67108864, (int) 0x80000000, 16, 16, 0, 0, 8, 0, 0, 512, 1920, 8388610,
/* 170 */ 805306368, 1006632960, 2, 2, 33554432, 1073741824, 0, 512, 1152, 805306368, 268435456, 4096, 64, 128, 4096,
/* 185 */ 4096, 64, 128, 4096, 4096, 4096, 4096, 2, 2, 16, 0, 2, 256, 0, 0, 0, 64, 128, 0, 0, 192, 0, 32, 0, 16, 0, 0,
/* 212 */ 268435456, 536870912, 12, 512, 0, 0, 1152, 268435456, 512, 524, 0, 512, 512, 17, 524, 524, 524, 513, 524, 513,
/* 232 */ 525, 525, 525, 525, 541, 541, 0, 17, 0, 512, 1, 0, 2, 32, 0, 0, 1024, 268435456, 536870912, 4096, 4096, 4096,
/* 254 */ 0, 0, 0, 64, 0, 0, 335544320, 939524096, 4096, 0, 268435456, 536870912
};

const wchar_t *EbnfParser::TOKEN[] =
{
  L"%ERROR",
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
