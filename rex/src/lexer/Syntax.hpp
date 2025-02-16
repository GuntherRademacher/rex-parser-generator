/*
 * Syntax.hpp
 *
 *  Created on: 24.04.2010
 *      Author: Gunther
 */

#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include "CharSet.hpp"
#include "SymbolTable.hpp"
#include "../common/WString.hpp"
#include "../common/Format.hpp"
#include "../common/Decoder.hpp"
#include "../common/Encoder.hpp"
#include <set>
#include <map>

class Rule;
class NfaState;
class DfaState;

enum SymbolType
{
  nonterminal,
  charset,
  charstring,
  compound,
  exclusion,
  slash,
  dollar
};

enum ClosureType {none, closure, positiveclosure, optional, quantity};
enum RuleType {mainrule,subrule};

class Symbol
{
public:
  Symbol() : nextsymbol(0), operation(none), min(0), max(0), kind(dollar), effectiveCharSet(0) {}
  ~Symbol() {}

  Symbol *nextsymbol;
  ClosureType operation;
  int min;
  int max;
  SymbolType kind;

  const GrammarCharSet *effectiveCharSet;

  union
  {
    SymbolTableEntry *name;           // case nonterminal, charstring
    GrammarCharSet *specification;    // case charset
    Rule *subrule;                    // case compound
    struct {Symbol *lhs, *rhs;};      // case exclusion
    /* empty */                       // case endofinput, contextseparator
  } u;

  inline static void deletesymbols(Symbol *s);
};

class Rule
{
public:
  Rule() : firstsymbol(0), link(0), rule(mainrule), main(0), effectiveCharSet(0) {}
  ~Rule() {}

  Symbol *firstsymbol;
  Rule *link;
  RuleType rule;
  Rule *main;
  const GrammarCharSet *effectiveCharSet;

  static void deleterules(Rule *r)
  {
    for (Rule *nextrule; r; r = nextrule)
    {
      nextrule = r->link;
      Symbol::deletesymbols(r->firstsymbol);
      delete r;
    }
  }

  static Rule *close(Rule *rules)
  {
    Rule *r = rules;
    if (r)
    {
      rules = r->link;
      r->link = 0;
    }
    return rules;
  }
};

inline void Symbol::deletesymbols(Symbol *s)
{
  for (Symbol *nextsymbol; s; s = nextsymbol)
  {
    nextsymbol = s->nextsymbol;

    switch (s->kind)
    {
    case compound:
      Rule::deleterules(s->u.subrule);
      break;
    case exclusion:
    case slash:
      deletesymbols(s->u.lhs);
      deletesymbols(s->u.rhs);
      break;
    case charset:
      delete s->u.specification;
      break;
    case nonterminal:
    case charstring:
    case dollar:
      break;
    }

    delete s;
  }
}

enum orig {undefined, named, numbered};

enum entrytype {tokencode, tokenname};

class entryrec
{
public:
  bool named;
  int tokencode;
  SymbolTableEntry *ntptr;
};

class preferencerec
{
public:
  entryrec *preferred;
  entryrec *nonpreferred;
};

class delimiterrec
{
public:
  SymbolTableEntry *delimiter;
  entryrec *delimited;
};

class List
{
public:
  List *link;                     /* list element pointer           */
  union
  {
    NfaState *nfa;                     /* for NFA state sets as used by  */
                                    /*    the subset construction     */
    struct
    {
      int code;                     /* for final state code lists     */
                                    /*    and entry lists             */
      int contextsize;
    };
    SymbolTableEntry *ntptr;        /* for nonterminal lists          */
    entryrec *eptr;
    preferencerec *pptr;
    delimiterrec *dptr;
  }
  u;

  static List *deletelist(List *first)
  {
    List *l = first;
    for (List *next; l; l = next == first ? 0 : next)
    {
      next = l->link;
      free(l);
    }
    return 0;
  }
};

class entrylist
{
public:
  entrylist *link;     /* list element pointer             */
  List *elist;          /* for entry list lists             */
  DfaState *dfa;

  static entrylist *deletelist(entrylist *first)
  {
    entrylist *l = first;
    for (entrylist *next; l; l = next == first ? 0 : next)
    {
      List *e = l->elist;
      for (List *n; e; e = n == l->elist ? 0 : n)
      {
        n = e->link;
        free(e->u.eptr);
        free(e);
      }

      next = l->link;
      free(l);
    }
    return 0;
  }
};

typedef int TokenId;

class OverruleSet : private std::set<TokenId, std::less<TokenId>, Alloc<TokenId> >
{                   typedef std::set<TokenId, std::less<TokenId>, Alloc<TokenId> >
                    super;
public:
  OverruleSet()
  : super(std::less<TokenId>(), Alloc<TokenId>(__FILE__, __LINE__))
  {}

  void insert(const TokenId &v) {super::insert(v);}
  bool contains(TokenId t) {return super::find(t) != super::end();}
};

class ConflictSet : private std::set<TokenId, std::less<TokenId>, Alloc<TokenId> >
{                   typedef std::set<TokenId, std::less<TokenId>, Alloc<TokenId> >
                    super;
public:
  ConflictSet()
  : super(std::less<TokenId>(), Alloc<TokenId>(__FILE__, __LINE__))
  {}

  typedef super::const_iterator const_iterator;
  const_iterator begin() {return super::begin();}
  const_iterator end() {return super::end();}
  size_t size() const {return super::size();}
  bool empty() const {return super::empty();}
  const_iterator find(TokenId i) const {return super::find(i);}

  void insert(TokenId i) {super::insert(i);}
  void erase(TokenId i) {super::erase(i);}
};

class TokenDescriptor
{
public:
  TokenDescriptor()
  : lexaction(0),
    nongreedy(false),
    nfa(0),
    conflicts(0),
    overrules(0),
    used(false),
    minlength(-1),
    maxlength(0),
    definition(undefined),
    exclusionError(false)
  {
  }

  SymbolTableEntry *lexaction;
  bool nongreedy;
  NfaState *nfa;
  ConflictSet *conflicts;
  OverruleSet *overrules;
  bool used;
  int minlength;
  int maxlength;
  orig definition;
  bool exclusionError;

  union
  {
                /* case Undefined     */
    SymbolTableEntry *nonterminal;    /* case Named       */
    struct                    /* case Numbered      */
    {
      Rule *rules;
      const GrammarCharSet *effectiveCharSet;
      SymbolTableEntry *trailingcontext;
    };
  } u;
};

class TokenDescriptors : private std::map<TokenId, TokenDescriptor, std::less<TokenId>, Alloc<std::pair<const TokenId, TokenDescriptor> > >
{                        typedef std::map<TokenId, TokenDescriptor, std::less<TokenId>, Alloc<std::pair<const TokenId, TokenDescriptor> > >
                         super;
public:
  TokenDescriptors()
  : super(key_compare(), Alloc<std::pair<const TokenId, TokenDescriptor> >(__FILE__, __LINE__)),
    currenttoken(0),
    currentnonterminal(0),
    errorcode(-1),
    selfContained(false),
    embedded(false)
  {}

  CString tokenDescription(TokenId id)
  {
    TokenDescriptors::const_iterator i(find(id));
    TokenDescriptor dummy;
    const TokenDescriptor &t(i == end() ? dummy : i->second);

    if (t.definition == named)
    {
      return tokenName(id);
    }
    else
    {
      return tokenString(id);
    }
  }

  CString tokenName(TokenId id)
  {
    Format format;
    CString tokenName;
    TokenDescriptors::const_iterator i = find(id);
    if (i == end())
    {
      tokenName += '_';
      tokenName += format.toString<char>(id);
    }
    else
    {
      const TokenDescriptor &t(i->second);
      if (t.definition == named)
      {
        tokenName += tokenPrefix;
        tokenName += t.u.nonterminal->name;
      }
      else if (tokenPrefix.size() > 0)
      {
        tokenName += tokenPrefix;
        tokenName += format.toString<char>(id);
      }
      else
      {
        tokenName += '_';
        tokenName += format.toString<char>(id);
      }
    }

    for (int i = (int) tokenName.size() - 1; i >= 0; --i)
    {
      if (tokenName[i] == '^') tokenName[i] = '_';
    }

    return tokenName;
  }

  CString tokenString(TokenId id)
  {
    Format format;
    TokenDescriptors::const_iterator i(find(id));
    TokenDescriptor dummy;
    const TokenDescriptor &t(i == end() ? dummy : i->second);

    CString tokenString;
    Character buffer[128];
    Rule *r = 0;
    int size = 0;
    bool isConstant;
    const Character quoteCharacter = selfContained ? '\'' : '"';

    switch (t.definition)
    {
    case named:     r = t.u.nonterminal->rules; break;
    case numbered:  r = t.u.rules;              break;
    case undefined:                             break;
    }

    isConstant = getPrefix(r, buffer, sizeof buffer / sizeof *buffer, &size);

    if (isConstant)
    {
      bool nonWhitespace = false;
      for (int i = 0; i < size; i++)
      {
        if (! isprintable(buffer[i]))
        {
          isConstant = false;
          break;
        }
        else if (buffer[i] != 9 && buffer[i] != 10 && buffer[i] != 13 && buffer[i] != 32)
        {
          nonWhitespace = true;
          if (buffer[i] == quoteCharacter && t.definition == named)
          {
            isConstant = false;
            break;
          }
        }
      }
      isConstant = isConstant && nonWhitespace;
    }

    if (isConstant && size > 0)
    {
      tokenString += quoteCharacter;
      for (int i = 0; i < size; i++)
      {
        if (buffer[i] == quoteCharacter)
        {
          tokenString += quoteCharacter;
          tokenString += quoteCharacter;
        }
        else if (isprintable(buffer[i]))
        {
          char encoded[] = {0, 0, 0, 0, 0};
          Encoder::encode_utf8(buffer[i], encoded);
          tokenString += encoded;
        }
        else
        {
          tokenString += "\\u";
          tokenString += format.toString<char>(buffer[i], 16, 4, 4);
        }
      }
      tokenString += quoteCharacter;
    }
    else if (t.definition == named)
    {
      const char *name = t.u.nonterminal->name;
      const char *circumflex = strchr(name, '^');
      size_t size = circumflex ? circumflex - name : strlen(name);
      tokenString.append(name, size);
    }
    else if (id == errorcode)
    {
      tokenString += "ERROR";
    }
    else if (id == 0 && ! selfContained)
    {
      tokenString += "[whitespace]";
    }
    else if (id == 1 && ! selfContained)
    {
      tokenString += "[eof]";
    }
    else if (! selfContained)
    {
      tokenString += '[';
      tokenString += format.toString<char>(id);
      tokenString += ']';
    }
    else if (id == 0)
    {
      tokenString += "%ERROR";
    }
    else
    {
      tokenString += "'(";
      tokenString += format.toString<char>(id);
      tokenString += ")'";
    }

  //    printf("token %d: %s\n", tokenStrings.size(), tokenString.c_str());

    return tokenString;
  }

  bool getPrefix(Rule *r,
                 Character *buffer,
                 int bufSize,
                 int *usedSize)
  {
    const Character blank = ' ';
    int ruleCount = 0;
    int nonBlank = 0;
    int ruleSize = 0;

    while (r)
    {
      *usedSize -= ruleSize;
      ruleSize = 0;

      Symbol *s = r->firstsymbol;
      if (s && s->kind == slash)
      {
        s = s->u.lhs;
      }

      for (; s; s = s->nextsymbol)
      {
        int symbolSize = *usedSize;

        switch (s->kind)
        {
        case nonterminal:
          if (! getPrefix (s->u.name->rules, buffer, bufSize, usedSize))
          {
            return false;
          }
          break;

        case compound:
          if (! getPrefix (s->u.subrule, buffer, bufSize, usedSize))
          {
            return false;
          }
          break;

        case charstring:
          {
            const char *string = s->u.name->name;
            size_t stringSize = strlen (string) - 2;
            Character quote = (Character) *string++;

            while (stringSize > 0)
            {
              size_t encodedSize;
              Character codepoint = Decoder::decode_utf8_char(string, &encodedSize);

              if (   codepoint == '\t'
                  || codepoint == '\n'
                  || codepoint == '\r')
              {
                codepoint = blank;
              }

              if (codepoint < blank || *usedSize >= bufSize)
              {
                return false;
              }
              else if (quote == (buffer[(*usedSize)++] = codepoint))
              {
                stringSize -= 2;
                string += 2;
              }
              else
              {
                stringSize -= encodedSize;
                string += encodedSize;
              }
            }
          }
          break;

        case charset:
        case exclusion:
          {
            GrammarCharSet gcs;
            if (s->kind == charset)
            {
              gcs = *s->u.specification;
            }
            else
            {
              if (! getcharset(currenttoken, currentnonterminal, s, gcs))
              {
                return false;
              }
            }

            if (*usedSize >= bufSize)
            {
              return false;
            }
            else
            {
              GrammarCharSet::CharIterator i(gcs.charBegin());
              Character n(*i);
              Character c = n == '\t'
                         || n == '\n'
                         || n == '\r'
                          ? blank
                          : n;

              while (++i != gcs.charEnd())
              {
                n = *i;
                Character d = n == '\t'
                           || n == '\n'
                           || n == '\r'
                            ? blank
                            : n;
                if (d != c)
                {
                  return false;
                }
              }

              if (c < blank)
                return false;
              else
                buffer [(*usedSize)++] = c;
            }
          }
          break;

        case dollar:
          s = 0;
          break;

        case slash:
          internalerr();
          break;
        }

        if (s == 0)
        {
          break;
        }
        else
        {
          symbolSize = *usedSize - symbolSize;
          bool isWhitespace = symbolSize == 0
                           || (symbolSize == 1 && (*usedSize == 0 || buffer[*usedSize - 1] == blank));
          switch (s->operation)
          {
          case none:
            break;

          case positiveclosure:
            if (! isWhitespace)
            {
              return false;
            }
            break;

          case optional:
          case closure:
            *usedSize -= symbolSize;
            if (! isWhitespace)
            {
              return false;
            }
            break;

          case quantity:
            if (! isWhitespace )
            {
              if (s->min == 0)
              {
                *usedSize -= symbolSize;
              }
              else for (int i = 1; i < s->min; ++i)
              {
                Character *string = &buffer[*usedSize - symbolSize];
                for (int stringSize = symbolSize; stringSize > 0; --stringSize)
                {
                  if (*usedSize >= bufSize)
                  {
                    return false;
                  }
                  buffer[(*usedSize)++] = *string++;
                }
              }
              return false;
            }
            break;

          default:
            internalerr();
            break;
          }
        }

        ruleSize += symbolSize;
      }

      ruleCount++;
      if (    ruleSize > 1
          || (ruleSize == 1 && *usedSize > 0 && (buffer[*usedSize - 1] != blank))
         )
      {
        nonBlank = 1;
      }
      r = r->link;
    }

    if (    ruleCount == 0
        || (ruleCount > 1 && nonBlank)
       )
    {
      return false;
    }

    return true;
  }

  bool getcharset(TokenId t,
                  SymbolTableEntry *nt,
                  Symbol *s,
                  GrammarCharSet &cs)
  {
    currenttoken = t;
    currentnonterminal = nt;

    bool valid = false;

    if (   (s->operation == none)
        || (s->operation == quantity && s->min == 1 && s->max == 1))
    {
      switch (s->kind)
      {
      case charset:
        valid = true;
        cs += *s->u.specification;
        break;

      case charstring:
        {
          const char *string = s->u.name->name;
          size_t encodedSize;
          Character codepoint = Decoder::decode_utf8_char(string + 1, &encodedSize);
          size_t stringSize = strlen(string) - 2;
          if (    stringSize == encodedSize
              || (stringSize == 2 && string[1] == string[0] && string[2] == string[0]))
          {
            valid = true;
            cs += CharacterRange(codepoint);
          }
        }
        break;

      case nonterminal:
        if (s->u.name->stack)
        {
          s->u.name->recursive = true;
          break;
        }

        s->u.name->used = true;
        s->u.name->stack = currentnonterminal;
        currentnonterminal = s->u.name;

        // no break

      case compound:
        {
          Rule *r = s->kind == nonterminal
                     ? s->u.name->rules
                     : s->u.subrule;
          if (r)
          {
            valid = true;
            for ( ; r; r = r->link)
            {
              if (   r->firstsymbol == 0
                  || r->firstsymbol->nextsymbol != 0
                  || ! getcharset(currenttoken, currentnonterminal, r->firstsymbol, cs))
              {
                valid = false;
                break;
              }
            }
          }

          if (s->kind == nonterminal)
          {
            currentnonterminal = s->u.name->stack;
            s->u.name->stack = 0;
          }
        }
        break;

      case exclusion:
        {
          if (s->u.lhs == 0)
          {
            internalerr();
          }

          valid = getcharset(currenttoken, currentnonterminal, s->u.lhs, cs);
          GrammarCharSet rhs;
          valid = valid && getcharset(currenttoken, currentnonterminal, s->u.rhs, rhs);
          if (valid)
          {
            cs -= rhs;
            if (cs.empty())
            {
              if (currentnonterminal)
              {
                currentnonterminal->exclusionError = true;
              }
              else
              {
                (*this)[currenttoken].exclusionError = true;
              }
              cs += CharacterRange(0);
            }
          }
        }
        break;

      case slash:
      case dollar:
        valid = false;
        break;
      }
    }
    return valid;
  }

  typedef super::const_iterator const_iterator;
  typedef super::const_reverse_iterator const_reverse_iterator;
  const_iterator find(TokenId i) const {return super::find(i);}
  const_iterator begin() const {return super::begin();}
  const_iterator end() const {return super::end();}
  const_reverse_iterator rbegin() const {return super::rbegin();}
  const_reverse_iterator rend() const {return super::rend();}
  void clear() {super::clear();}

  TokenDescriptor &operator[](TokenId i) {return super::operator[](i);}

  const TokenDescriptor &get(TokenId i) const
  {
    const_iterator t(find(i));
    if (t == end())
    {
      internalerr();
    }
    return t->second;
  }

  TokenDescriptor &get(TokenId i)
  {
    super::iterator t(super::find(i));
    if (t == end())
    {
      internalerr();
    }
    return t->second;
  }

  int getErrorCode() {return errorcode;}
  void setErrorCode(int e) {errorcode = e;}

  const CString &getTokenPrefix() {return tokenPrefix;}
  void setTokenPrefix(CString t) {tokenPrefix = t;}

  bool getSelfContained() {return selfContained;}
  void setSelfContained(bool s) {selfContained = s;}

  bool getEmbedded() {return embedded;}
  void setEmbedded(bool e) {embedded = e;}

private:
  TokenId currenttoken;
  SymbolTableEntry *currentnonterminal;
  int errorcode;
  CString tokenPrefix;
  bool selfContained;
  bool embedded;
};

#endif

