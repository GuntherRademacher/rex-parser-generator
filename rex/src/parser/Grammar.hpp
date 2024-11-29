#ifndef GRAMMAR_HPP_
#define GRAMMAR_HPP_

#include "../common/Error.hpp"
#include "../common/WString.hpp"
#include "../common/Format.hpp"

#include <list>
#include <deque>
#include <map>
#include "CompressedTokenSet.hpp"
#include "Exceptions.hpp"
#include "OrderedTokenSequenceVector.hpp"
#include "TokenSequenceSet.hpp"
#include "TokenSequenceSets.hpp"
#include "WcsSet.hpp"
#include "Naming.hpp"

enum GrammarSection {GRAMMAR, PROLOG, EPILOG, NONTERMINALS, TERMINALS, AUTOMATIC};
enum Whitespace {EXPLICIT, IMPLICIT};
enum MatchType {NOMATCH, IF, IFNOT, CASE, DEFAULT};

enum ASIKind
{
  NONE       = 0x00,
  SEMICOLON  = 0x01,
  PLUSPLUS   = 0x02,
  MINUSMINUS = 0x04,
  CONTINUE   = 0x08,
  BREAK      = 0x10,
  RETURN     = 0x20,
  THROW      = 0x40,
  ALL        = 0x7F,
};

enum Distance
{
  UNKNOWN = -2,
  VARIABLE = -1,
};

enum ReduceType
{
  reduceUnknown,
  reduceByCount,
  reduceByLookback
};

class Node;
class NodeWithChildren;
class NodeWithContext;
class Grammar;
class Production;
class CharClass;
class Choice;
class Sequence;
class Predicate;
class Optional;
class ZeroOrMore;
class OneOrMore;
class Ref;
class String;
class ProcessingInstruction;
class Exclusion;
class Context;
class EndOfFile;
class Char;
class CharCode;
class CharRange;
class CharCodeRange;
class Complement;
class Preference;
class Delimiter;
class Equivalence;
class Reduce;
class TiledMap2D;
class ItemSet;
class LrStates;

class Visitor
{
public:
  Visitor() : section(GRAMMAR) {}
  virtual ~Visitor() {}
  virtual void visitNodePreOrder(Node *node) {}
  virtual void visitNodePostOrder(Node *node) {}
  virtual void visitNode(Node *node);
  virtual void visitNodeList(Node *node);
  virtual void visitNodeWithChildren(NodeWithChildren *node);
  virtual void visitNodeWithContext(NodeWithContext *node);
  virtual void visitGrammar(Grammar *node);
  virtual void visitChoice(Choice *node);
  virtual void visitExclusion(Exclusion *node);
  virtual void visitPredicate(Predicate *node);
  virtual void visitContext(Context *node);
  virtual void visitComplement(Complement *node);
  virtual void visitProcessingInstruction(ProcessingInstruction *node);
  virtual void visitEndOfFile(EndOfFile *node);
  virtual void visitChar(Char *node);
  virtual void visitCharCode(CharCode *node);
  virtual void visitCharRange(CharRange *node);
  virtual void visitCharCodeRange(CharCodeRange *node);
  virtual void visitPreference(Preference *node);
  virtual void visitDelimiter(Delimiter *node);
  virtual void visitEquivalence(Equivalence *node);
  virtual void visitRef(Ref *node);
  virtual void visitString(String *node);
  virtual void visitProduction(Production *node);
  virtual void visitCharClass(CharClass *node);
  virtual void visitSequence(Sequence *node);
  virtual void visitOptional(Optional *node);
  virtual void visitZeroOrMore(ZeroOrMore *node);
  virtual void visitOneOrMore(OneOrMore *node);

protected:
  GrammarSection section;
};

class ReverseVisitor : public Visitor
{
public:
  ReverseVisitor() {}
  virtual void visitNode(Node *node);
  virtual void visitNodeList(Node *node);
  virtual void visitNodeWithChildren(NodeWithChildren *node);

  virtual void visitGrammar(Grammar *node);

  virtual void visitExclusion(Exclusion *node) {internalerr();}
  virtual void visitContext(Context *node) {internalerr();}
  virtual void visitComplement(Complement *node) {internalerr();}
  virtual void visitPredicate(Predicate *node) {internalerr();}
  virtual void visitEndOfFile(EndOfFile *node) {internalerr();}
  virtual void visitChar(Char *node) {internalerr();}
  virtual void visitCharCode(CharCode *node) {internalerr();}
  virtual void visitCharRange(CharRange *node) {internalerr();}
  virtual void visitCharCodeRange(CharCodeRange *node) {internalerr();}
  virtual void visitPreference(Preference *node) {internalerr();}
  virtual void visitDelimiter(Delimiter *node) {internalerr();}
  virtual void visitEquivalence(Equivalence *node) {internalerr();}
  virtual void visitCharClass(CharClass *node) {internalerr();}
};

class ProductionTable : public std::multimap <wchar_t *, Production *, LtWcs>
{
public:
  Production *byStringValue(const wchar_t *value) const;
  Production *byNodeType(const wchar_t *nodeType) const;
};

class NodeIdLess
{
public:
  bool operator()(const Node *lhs, const Node *rhs) const;
};

typedef std::set<Node *, NodeIdLess> NodeSet;
typedef std::set<Node *> NodePointerSet;
typedef std::list<Production *> ProductionList;
typedef std::set<const Production *> ProductionSet;
typedef std::map<std::pair<std::pair<const TokenSequenceSet *, const TokenSequenceSetAccessor *>, size_t>, const TokenSequenceSet *> FirstFollowMemoizer;
typedef std::deque<Node *> NodeQueue;
typedef std::map<Production *, NodeSet> RestrictionsByProduction;
typedef std::map<Node *, Node *, NodeIdLess> NodeMap;

class Node
{
public:
  Node()
  : production(0),
    grammar(0),
    precedingSibling(0), followingSibling(0),
    precedingElementSibling(0), followingElementSibling(0),
    k(0),
    conflictsK(0), kConflicts(0),
    firstK(0), kFirst(0),
    followK(0), kFollow(0),
    followItemK(0), kFollowItem(0),
    involvedInConflict(false),
    caseId(-1),
    whitespaceAllowance(EXPLICIT),
    findsLookahead(true),
    leavesLookahead(true),
    leftRecursive(false),
    id(-1),
    reduceItem(0),
    automaticSemicolonInsertion(NONE),
    firstAccessor(this),
    followAccessor(this),
    followItemAccessor(this),
    match(0),
    matchComplement(0),
    conflictMatch(0),
    conflictMatchComplement(0),
    parent(0),
    symbolSequenceNumber(-1),
    lookahead(0)
  {}

  virtual ~Node()
  {
    for (size_t i = 0; i < kConflicts; ++i)
    {
      delete conflictsK[i];
    }
    free(conflictsK);

    free(firstK);
    free(followK);
    free(followItemK);

    delete lookahead;
  }

  class FirstAccessor : public TokenSequenceSetAccessor
  {
  public:
    FirstAccessor(Node *node) : node(node) {}
    const TokenSequenceSet *get() const {internalerr(); return 0;}
    const TokenSequenceSet *get(size_t k) const {return &node->first(k);}
  private:
    Node *node;
  };

  class FollowAccessor : public TokenSequenceSetAccessor
  {
  public:
    FollowAccessor(Node *node) : node(node) {}
    const TokenSequenceSet *get() const {internalerr(); return 0;}
    const TokenSequenceSet *get(size_t k) const {return &node->follow(k);}
  private:
    Node *node;
  };

  class FollowItemAccessor : public TokenSequenceSetAccessor
  {
  public:
    FollowItemAccessor(Node *node) : node(node) {}
    const TokenSequenceSet *get() const {internalerr(); return 0;}
    const TokenSequenceSet *get(size_t k) const {return &node->followItem(k);}
  private:
    Node *node;
  };

  virtual const wchar_t *getNodeType() const = 0;
  virtual void accept(Visitor &v) = 0;

  const TokenSequenceSet &first(size_t k);
  const TokenSequenceSet &follow(size_t k);
  const TokenSequenceSet &followItem(size_t k);
  const TokenSequenceSet &expect(size_t k);
  const TokenSequenceSet *blackList(size_t k);

  const TokenSequenceSet &first(size_t k, const TokenSequenceSetAccessor &lookaheadAccessor);
  const TokenSequenceSet &follow(size_t k, const TokenSequenceSetAccessor &lookaheadAccessor);

  void saturate(size_t k, TokenSequenceSet *&result, void (*callee)(Node*, size_t, TokenSequenceSet&));
  void saturatePass(size_t k, TokenSequenceSet &result, void (*callee)(Node*, size_t, TokenSequenceSet&));

  const TokenSequenceSet *conflicts(size_t k) const;
  bool setConflicts(size_t k, TokenSequenceSet *conflicts);

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    throw Complaint(L"internal error: calculateFirst() not implemented for node type ", getNodeType());
  }

  virtual Node *element() {return this;}

  virtual void fastFollow(size_t k, TokenSequenceSet &result, NodePointerSet &transitive);
  void fastFollowers(size_t k, const TokenSequenceSet *firstSet, Node *origin, TokenSequenceSet &result, NodePointerSet &transitive);

  virtual void fastFollowItem(size_t k, TokenSequenceSet &result, NodePointerSet &transitive);
  void fastFollowersItem(size_t k, const TokenSequenceSet &firstSet, Node *origin, TokenSequenceSet &result, NodePointerSet &transitive);

  virtual bool isNodeWithChildren() const {return false;}
  virtual bool isNodeWithContext() const {return false;}
  virtual bool isProduction() const {return false;}
  virtual bool isOneOrMore() const {return false;}
  virtual bool isZeroOrMore() const {return false;}
  virtual bool isOptional() const {return false;}
  virtual bool isChoice() const {return false;}
  virtual bool isSequence() const {return false;}
  virtual bool isCharClass() const {return false;}
  virtual bool isChar() const {return false;}
  virtual bool isCharRange() const {return false;}
  virtual bool isCharCode() const {return false;}
  virtual bool isCharCodeRange() const {return false;}
  virtual bool isElement() const {return true;}
  virtual bool isActive() const {return true;}
  virtual bool isRef() const {return false;}
  virtual bool isTerminalShift() const {return false;}
  virtual bool isString() const {return false;}
  virtual bool isReduce() const {return false;}
  virtual bool isEndOfFile() const {return false;}
  virtual bool isProcessingInstruction() const {return false;}

  bool isRestrictedCase() const;
  Node *closestRestrictedCaseAncestorOrSelf();
  void collectRestrictedCaseNodes(const ItemSet* shiftItems, NodeSet &restrictions, RestrictionsByProduction &restrictionsByProduction);

  virtual Node *simplified() {return this;}
  virtual bool isLL(size_t k) {throw Complaint(L"internal error: isLL() not implemented for node type ", getNodeType());}
  virtual bool isLeftRecursive() {return leftRecursive;}
  virtual bool derivesToEmptySequence() const {return false;}
  virtual bool hasActiveProcessingInstruction() const {return false;}
  virtual Production *shiftSymbol() {return 0;}

  const CompressedTokenSet *getLookahead() {return lookahead;}
  virtual void setLookahead(const CompressedTokenSet *cts) {lookahead = cts;}
  virtual void setConflictId(int id) {}

  void setParent(Node *p)
  {
    if (id >= 0)
    {
      internalerr();
    }
    parent = p;
  }

  virtual Node *getParent() const {return parent;}

  const TokenSequenceSet &getMatch() const;
  const TokenSequenceSet &getMatch(MatchType &m);
  const TokenSequenceSet &getConflictMatch() const;
  const TokenSequenceSet &getConflictMatch(MatchType &m);

  void setMatch(const TokenSequenceSet *tss) {match = tss;}
  void setMatchComplement(const TokenSequenceSet *tss) {matchComplement = tss;}
  void setConflictMatch(const TokenSequenceSet *tss) {conflictMatch = tss;}
  void setConflictMatchComplement(const TokenSequenceSet *tss) {conflictMatchComplement = tss;}

  Node *followingActiveSibling() const
  {
    for (Node *followingActiveSibling = followingSibling; followingActiveSibling; followingActiveSibling = followingActiveSibling->followingSibling)
      if (followingActiveSibling->isActive())
        return followingActiveSibling;
    return 0;
  }

  Production *production;
  Grammar *grammar;
  Node *precedingSibling;
  Node *followingSibling;
  Node *precedingElementSibling;
  Node *followingElementSibling;

  size_t k;

  TokenSequenceSet **conflictsK;
  size_t kConflicts;

  TokenSequenceSet **firstK;
  size_t kFirst;

  TokenSequenceSet **followK;
  size_t kFollow;

  TokenSequenceSet **followItemK;
  size_t kFollowItem;

  bool involvedInConflict;

  int caseId;

  Whitespace whitespaceAllowance;

  bool findsLookahead;
  bool leavesLookahead;

  bool leftRecursive;
  int id;
  Reduce *reduceItem;
  ASIKind automaticSemicolonInsertion;

  FirstAccessor firstAccessor;
  FollowAccessor followAccessor;
  FollowItemAccessor followItemAccessor;

  NodePointerSet precedents;

private:
  friend class MatchCodeVisitor;

  const TokenSequenceSet *match;
  const TokenSequenceSet *matchComplement;

  const TokenSequenceSet *conflictMatch;
  const TokenSequenceSet *conflictMatchComplement;

  Node *parent;
  FirstFollowMemoizer firstFollowMemoizer;

  int symbolSequenceNumber;
  const CompressedTokenSet *lookahead;
};

class NodeList : public std::list<Node *>
{
public:
  NodeList(bool o = true) : ownNodes(o) {}

  ~NodeList()
  {
    if (ownNodes)
    {
      iterator next = begin();
      for (iterator i = next; i != end(); i = next)
      {
        ++next;
        delete *i;
      }
    }
  }

private:
  bool ownNodes;
};

class NodeWithChildren : public Node
{
public:
  NodeWithChildren()
  : firstChild(0)
  , lastChild(0)
  , firstElementChild(0)
  , lastElementChild(0)
  {}

  virtual ~NodeWithChildren()
  {
    freeNodeList(firstChild);
  }

  virtual bool isNodeWithChildren() const {return true;}

  virtual bool hasActiveProcessingInstruction() const
  {
    for (const Node *node = firstChild; node; node = node->followingSibling)
    {
      if (node->hasActiveProcessingInstruction()) return true;
    }
    return false;
  }

  template<class NODE>
  NODE *addChild(NODE *node)
  {
    if (firstChild == 0)
    {
      firstChild = node;
    }
    else
    {
      lastChild->followingSibling = node;
    }
    node->setParent(this);
    node->precedingSibling = lastChild;
    node->followingSibling = 0;
    lastChild = node;
    return node;
  }

  virtual void endChildren() {}

  virtual bool isLeftRecursive()
  {
    if (! leftRecursive && firstElementChild)
    {
      firstElementChild->isLeftRecursive();
    }
    return leftRecursive;
  }

  virtual bool derivesToEmptySequence() const
  {
    for (Node *child = firstElementChild; child; child = child->followingElementSibling)
    {
      if (! child->derivesToEmptySequence()) return false;
    }
    return true;
  }

  bool isLLOptionalOrMultiple(size_t k);

  Node *firstActiveChild() const
  {
    if (firstChild == 0 || firstChild->isActive())
      return firstChild;
    else
      return firstChild->followingActiveSibling();
  }

protected:
  void freeNodeList(Node *&node)
  {
    for (Node *next = node; node; node = next)
    {
      next = node->followingSibling;
      delete node;
    }
    node = 0;
  }

private:
  Node *isolate(Node *child)
  {
    if (child == firstChild) firstChild = child->followingSibling;
    if (child == lastChild)  lastChild  = child->precedingSibling;
    child->setParent(0);

    if (child->precedingSibling) child->precedingSibling->followingSibling = child->followingSibling;
    if (child->followingSibling) child->followingSibling->precedingSibling = child->precedingSibling;
    child->precedingSibling = 0;
    child->followingSibling = 0;

    return child;
  }

public:
  Node *isolateFirstChild() {return isolate(firstChild);}
  Node *isolateLastChild() {return isolate(lastChild);}

  Node *firstChild;
  Node *lastChild;

  Node *firstElementChild;
  Node *lastElementChild;
};

class NodeWithContext : public Node
{
public:
  NodeWithContext() : context(0), lexical(0), reduceType(reduceUnknown), distance(UNKNOWN) {}

  virtual ~NodeWithContext()
  {
    free(context);
  }

  bool isNodeWithContext() const {return true;}

  wchar_t *context;
  Production *lexical;
  ReduceType reduceType;

  virtual int getDistance() const
  {
    if (distance == UNKNOWN)
    {
      internalerr();
    }
    return distance;
  }

  virtual void setDistance(int d);

private:
  int distance;
};

class MatchCodeDescriptor
{
public:
  MatchCodeDescriptor() : prefix(false), match(0), code(0) {}

  void setCode(int c)
  {
    if (code != 0)
    {
      internalerr();
    }
    code = c;
  }

  int getCode() const {return code;}

  void setPrefix() {prefix = true;}
  bool isPrefix() const {return prefix;}

  void setMatch() {match = true;}
  bool isMatch() const {return match;}

private:
  /**
   * This matchcode is a prefix of some other matchcode.
   */
  bool prefix;
  /**
   * This matchcode is actually used in a match (not just as a prefix).
   */
  bool match;
  /**
   * This matchcode's code.
   */
  int code;
};

class MatchCode : public std::map<TokenSequence, MatchCodeDescriptor, TokenSequence::Order, Alloc<std::pair<const TokenSequence, MatchCodeDescriptor> > >
{                typedef std::map<TokenSequence, MatchCodeDescriptor, TokenSequence::Order, Alloc<std::pair<const TokenSequence, MatchCodeDescriptor> > >
                 super;
public:
  MatchCode()
  : super(TokenSequence::Order(), Alloc<std::pair<const TokenSequence, MatchCodeDescriptor> >(__FILE__, __LINE__))
  {}

  void add(const TokenSequenceSet *match, TokenSequenceFactory *tokenSequenceFactory)
  {
    for (TokenSequenceSet::const_iterator i = match->begin(); i != match->end(); ++i)
    {
      const TokenSequence &ts(*i);

      bool isPrefix = false;
      for (size_t k = ts.size(); k >= 1; --k)
      {
        const TokenSequence subSequence = tokenSequenceFactory->tokenSequence(ts, 0, k);

        MatchCodeDescriptor &md((*this)[subSequence]);
        if (isPrefix)
        {
          md.setPrefix();
        }
        else
        {
          md.setMatch();
          isPrefix = true;
        }
      }
    }
  }

  int get(const TokenSequence &ts) const
  {
    const_iterator i(find(ts));
    if (i == end())
    {
      internalerr();
    }
    return i->second.getCode();
  }

//  const TokenSequence sequentialSearchForCode(int code) const
//  {
//    for (const_iterator i = begin(); i != end(); ++i)
//    {
//      if (i->second.getCode() == code)
//        return i->first;
//    }
//    return TokenSequence::VOID;
//  }
};

class DecisionPoint
{
public:
  DecisionPoint(size_t k, const CompressedTokenSet *s, int n) : k(k), lookahead(s), dpiKey(n) {}
  size_t k;
  const CompressedTokenSet *lookahead;
  int dpiKey;
};

class DecisionPointLess
{
public:
  bool operator()(const DecisionPoint &lhs,
                  const DecisionPoint &rhs) const
  {
    if (lhs.k > 1 && rhs.k == 1) return true;
    if (rhs.k > 1 && lhs.k == 1) return false;
    return lhs.dpiKey < rhs.dpiKey;
  }
};

class DecisionPoints : public std::set<DecisionPoint, DecisionPointLess, Alloc<DecisionPoint> >
{                     typedef std::set<DecisionPoint, DecisionPointLess, Alloc<DecisionPoint> >
                      super;
public:
  DecisionPoints()
  : super(DecisionPointLess(), Alloc<DecisionPoint>(__FILE__, __LINE__))
  {}
};

typedef std::map<const wchar_t *, Reduce *, PtrLess<wchar_t> > EmbeddedReduceItems;

class Grammar : public NodeWithChildren
{
public:
  Grammar()
  : prolog(0),
    nonTerminals(0),
    terminals(0),
    epilog(0),
    whitespace(0),
    firstTokenCode(Token::eFIRST),
    maxTokenCode(Token::eFIRST - 1),
    externalTokenCode(0),
    maxNonterminalCode(-1),
    maxImplicitNonterminalCode(-1),
    currentPass(0),
    cyclicSetSize(0),
    emptySet(0),
    epsilon(0),
    tokenSequenceFactory(0),
    conflictCount(0),
    matchcodeTable(0),
    caseidTable(0),
    states(0),
    faster(false),
    smaller(false),
    hasBacktracking(false),
    noThrow(false),
    noLexer(false),
    singleLexer(false),
    basex(false),
    tables(0),
    cyclic(TokenSequence::VOID),
    tokenSequenceSets(0),
    verbose(false),
    quiet(false),
    maxK(0),
    maxDistance(UNKNOWN),
    variant(0),
    useGlr(false)
  {}

  enum
  {
    FINALPASS = 0x7fffffff
  };

  virtual ~Grammar();

  const wchar_t *getNodeType() const {return L"grammar";}
  virtual void accept(Visitor &v) {v.visitGrammar(this);}

  void setProlog()
  {
    prolog = firstChild;
    firstChild = 0;
    lastChild = 0;
  }

  void setNonTerminals()
  {
    nonTerminals = firstChild;
    firstChild = 0;
    lastChild = 0;
  }

  void setTerminals()
  {
    terminals = firstChild;
    firstChild = 0;
    lastChild = 0;
  }

  void setEpilog()
  {
    epilog = firstChild;
    firstChild = 0;
    lastChild = 0;
  }

  void renumber()
  {
    size_t setNo = 0;
    for (Lookahead::iterator i = lookaheadSets.begin(); i != lookaheadSets.end(); ++i)
    {
      for (OrderedTokenSequenceVector::const_iterator j = i->first.begin(); j != i->first.end(); ++j)
      {
        lookaheadAll.insert(*j);
      }
      i->second = setNo++;
    }
    if (lookaheadAll.contains(tokenSequence(Token::eEND)))
    {
      firstTokenCode = Token::eEND;
    }

    // set external token code. possibly redefined later when preparing tables.

    grammar->externalTokenCode = ALLOCATE_ARRAY(Token::Code, grammar->maxTokenCode + 1);
    memset(grammar->externalTokenCode, 0, sizeof(Token::Code) * (grammar->maxTokenCode + 1));
    for (int i = grammar->firstTokenCode; i <= grammar->maxTokenCode; ++i)
    {
      // EPSILON(0)
      // error(1)
      // END(2)
      // firstToken(3)
      // ...

      grammar->externalTokenCode[i] = i - grammar->firstTokenCode + 1;
    }
  }

  Production *startSymbol() const;

  virtual bool derivesToEmptySequence() const;

  const TokenSequence &tokenSequence(const Token::Code &code) const {return tokenSequenceFactory->tokenSequence(code);}

  Node *prolog;
  Node *nonTerminals;
  Node *terminals;
  Node *epilog;

  Production *whitespace;

  ProductionTable nonTerminalByName;
  ProductionTable terminalByName;
  ProductionTable lexicalByName;
  ProductionTable stringByName;

  std::map <Token::Code, Production *> terminalProductionByCode;
  std::map <int, Production *> nonterminalProductionByCode;

  Naming naming;

  Token::Code firstTokenCode;
  Token::Code maxTokenCode;
  Token::Code *externalTokenCode;

  int maxNonterminalCode;
  int maxImplicitNonterminalCode;

  size_t currentPass;
  size_t cyclicSetSize;

  TokenSequenceSet lookaheadAll;
  Lookahead lookaheadSets;

  TokenSequenceSet whitespaceIntroducers;
  TokenSequenceSet simpleWhitespaceIntroducers;
  TokenSequenceSet complexWhitespaceIntroducers;

  const TokenSequenceSet *emptySet;
  const TokenSequenceSet *epsilon;

  TokenSequenceFactory *tokenSequenceFactory;

  int conflictCount;

  MatchCode matchCode;
  DecisionPoints decisionPoints;

  TiledMap2D *matchcodeTable;
  TiledMap2D *caseidTable;

  LrStates *states;

  bool faster;
  bool smaller;
  bool hasBacktracking;
  bool noThrow;
  bool noLexer;
  bool singleLexer;
  bool basex;

  size_t tables;
  TokenSequence cyclic;

  TokenSequenceSets *tokenSequenceSets;

  bool verbose;
  bool quiet;
  size_t maxK;
  int maxDistance;
  const wchar_t *variant;
  bool useGlr;

  EmbeddedReduceItems embeddedReduceItems;
  std::vector<ProcessingInstruction *> distinctCodeAnnotations;
};

class Sequence : public NodeWithChildren
{
public:
  const wchar_t *getNodeType() const {return L"sequence";}
  virtual void accept(Visitor &v) {v.visitSequence(this);}
  virtual bool isLL(size_t k) {return true;}

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    if (firstElementChild == 0)
    {
      result.insert(grammar->tokenSequenceFactory->emptySequence());
    }
    else
    {
      result.insertAll(firstElementChild->first(k));
    }
  }

  virtual bool isSequence() const {return true;}

  Node *simplified()
  {
    if (firstChild && firstChild == lastChild && firstChild->isElement())
    {
      return isolateLastChild();
    }
    else
    {
      return this;
    }
  }
};

class ReduceArguments
{
public:
  ReduceArguments(int nonterminalCode, int count, int targetCodeId, Node *restrictedCase)
  : nonterminalCode(nonterminalCode)
  , count(count)
  , targetCodeId(targetCodeId)
  , restrictedCase(restrictedCase)
  {}

  bool operator<(const ReduceArguments &rhs) const
  {
    if (nonterminalCode < rhs.nonterminalCode) return true;
    if (nonterminalCode > rhs.nonterminalCode) return false;
    if (count < rhs.count) return true;
    if (count > rhs.count) return false;
    if (targetCodeId < rhs.targetCodeId) return true;
    if (targetCodeId > rhs.targetCodeId) return false;
    if ((restrictedCase != 0) < (rhs.restrictedCase != 0)) return true;
    if ((restrictedCase != 0) > (rhs.restrictedCase != 0)) return false;
    int comp = restrictedCase == 0 ? 0 : restrictedCase->id - rhs.restrictedCase->id;
    return comp < 0;
  }

  int getNonterminalCode() const {return nonterminalCode;}
  int getTargetCodeId() const {return targetCodeId;}

private:
  int nonterminalCode;
  int count;
  int targetCodeId;
  Node *restrictedCase;
};

typedef std::map<ReduceArguments, Reduce *, std::less<ReduceArguments> > ReduceItems;

class Production : public NodeWithChildren
{
public:
  Production(GrammarSection aSection, bool aNonGreedy, wchar_t *aName, wchar_t *aContext = 0)
  : section(aSection),
    nonGreedy(aNonGreedy),
    name(aName),
    context(aContext),
    constant(false),
    startSym(false),
    state(0),
    wsExplicit(false),
    tokenCode(-2),
    nonterminalCode(-2),
    uniqueRoot(0),
    runPayload(false),
    runOffLoad(false)
  {}

  virtual ~Production();

  const wchar_t *getNodeType() const {return L"production";}
  void accept(Visitor &v) {v.visitProduction(this);}
  virtual bool isProduction() const {return true;}

  bool isStartSymbol() const {return startSym;}

  virtual void fastFollow(size_t k, TokenSequenceSet &result, NodePointerSet &transitive);
  virtual void fastFollowItem(size_t k, TokenSequenceSet &result, NodePointerSet &transitive);

  virtual bool isLL(size_t k) {return true;}

  void calculateUniqueRoot();

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    if (firstElementChild == 0)
    {
      result.insert(grammar->tokenSequenceFactory->emptySequence());
    }
    else
    {
      result.insertAll(firstElementChild->first(k));
    }
  }

  int getStateId() const;

  ReduceItems reduceItems;
  GrammarSection section;
  bool nonGreedy;
  wchar_t *name;
  wchar_t *context;
  bool constant;
  bool startSym;
  ItemSet *state;
  bool wsExplicit;
  Token::Code tokenCode;
  int nonterminalCode;
  NodePointerSet references;
  const Production *uniqueRoot;
  bool runPayload;
  bool runOffLoad;
};

class CheckLL : public Visitor
{
public:
  CheckLL() : k(0), grammar(0) {}

  enum
  {
    DEFAULTMAXLL = 3
  };

  void visitGrammar(Grammar *node)
  {
    grammar = node;
    for (k = 1;; ++k)
    {
      grammar->conflictCount = 0;
      visitNodeList(node->nonTerminals);
      if (grammar->conflictCount == 0 || k == grammar->maxK)
      {
        node->k = k;
        break;
      }
    }
  }

  void visitNodePreOrder(Node *node)
  {
    if (node->isLL(k))
    {
      node->setConflictId(-1);
    }
    else
    {
      node->setConflictId(grammar->conflictCount);
      grammar->conflictCount++;
      if (k == grammar->maxK)
      {
        node->k = k;
      }
    }
  }

private:
  size_t k;
  Grammar *grammar;
};

class CharClass : public NodeWithChildren
{
public:
  const wchar_t *getNodeType() const {return L"charClass";}
  virtual void accept(Visitor &v) {v.visitCharClass(this);}
  virtual bool isCharClass() const {return true;}
};

class Choice : public Node
{
public:
  Choice(Node *aNode) : defaultCase(0), conflictCaseId(-1), conflictId(-1), ordered(false) {addCase(aNode);}
  virtual ~Choice() {}

  void addCase(Node *aNode)
  {
    aNode->setParent(this);
    cases.push_back(aNode);
  }

  const wchar_t *getNodeType() const {return L"choice";}
  virtual void accept(Visitor &v) {v.visitChoice(this);}
  virtual bool isChoice() const {return true;}
  void setOrdered() {ordered = true;}
  bool getOrdered() {return ordered;}

  virtual bool hasActiveProcessingInstruction() const
  {
    for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
    {
      Node *node = *i;
      if (node->hasActiveProcessingInstruction()) return true;
    }
    return false;
  }

  virtual bool isLL(size_t k)
  {
    if (this->k > 0)
    {
      return this->k <= k;
    }

    NodeList::iterator i = cases.begin();
    Node *element = (*i++)->element();
    const TokenSequenceSet &expect(element->expect(k));
    TokenSequenceSet unionSet(expect);

    int empty = k == 1 && element->first(1).contains(grammar->tokenSequenceFactory->emptySequence())
              ? 1
              : 0;

    TokenSequenceSet *conflicts = new TokenSequenceSet();

    for (int j = 2; ; ++j)
    {
      element = (*i++)->element();
      const TokenSequenceSet &caseSet(element->expect(k));
      conflicts->insertIntersectionOf(unionSet, caseSet);

      if (k == 1 && element->first(1).contains(grammar->tokenSequenceFactory->emptySequence()))
      {
        if (empty == 0)
        {
          empty = j;
        }
        else
        {
          WString msg(L"ambiguous choice: ");
          Format format;
          msg += format.toString<wchar_t>(empty, 10, 0, 0, 0, "0123456789ABCDEF", true);
          msg += L" and ";
          msg += format.toString<wchar_t>(j, 10, 0, 0, 0, "0123456789ABCDEF", true);
          msg += L" alternative may be empty in production ";
          throw Complaint(msg, production->name);
        }
      }

      if (i == cases.end())
      {
        break;
      }

      unionSet.insertAll(caseSet);
    }

    return setConflicts(k, conflicts);
  }

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    for (NodeList::iterator i = cases.begin(); i != cases.end(); ++i)
    {
      result.insertAll((*i)->element()->first(k));
    }
  }

  Node *simplified()
  {
    for (NodeList::iterator i = cases.begin(); i != cases.end(); ++i)
    {
      Node *child = *i;
      if (! child->isCharCode() && ! child->isCharClass())
      {
        return this;
      }
    }
    CharClass *charClass = new CharClass();
    while (! cases.empty())
    {
      Node *node = cases.front();
      cases.pop_front();
      if (! node->isCharClass())
      {
        charClass->addChild(node);
      }
      else
      {
        NodeWithChildren *child = static_cast <NodeWithChildren *> (node);
        while (child->firstChild)
        {
          charClass->addChild(child->isolateFirstChild());
        }
        delete child;
      }
    }
    return charClass;
  }

  virtual bool isLeftRecursive()
  {
    if (! leftRecursive)
    {
      for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
      {
        Node *c = *i;
        if (c)
        {
          c->isLeftRecursive();
        }
      }
    }
    return leftRecursive;
  }

  virtual bool derivesToEmptySequence() const
  {
    for (NodeList::const_iterator i = cases.begin(); i != cases.end(); ++i)
    {
      Node *c = *i;
      if (c)
      {
        if (! c->derivesToEmptySequence()) return false;
      }
    }
    return true;
  }

  virtual void setConflictId(int id) {conflictId = id;}

  NodeList cases;
  Node *defaultCase;

  int conflictCaseId;
  int conflictId;

  bool ordered;
};

class Predicate : public Node
{
public:
  Predicate(Node *aLhs, Node *aRhs) : lhs(aLhs), rhs(aRhs)
  {
    lhs->setParent(this);
    rhs->setParent(this);
  }

  virtual ~Predicate()
  {
    delete lhs;
    delete rhs;
  }

  const wchar_t *getNodeType() const {return L"predicate";}
  virtual void accept(Visitor &v) {v.visitPredicate(this);}
  virtual bool isLL(size_t k) {return rhs->isLL(k);}

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    result.insertAll(rhs->first(k));
  }

  virtual bool isLeftRecursive()
  {
    if (! leftRecursive)
    {
      lhs->isLeftRecursive();
      rhs->isLeftRecursive();
    }
    return leftRecursive;
  }

  Node *lhs;
  Node *rhs;
};

class Optional : public NodeWithChildren
{
public:
  Optional() : conflictCaseId(-1), conflictId(-1) {}
  virtual ~Optional() {}

  const wchar_t *getNodeType() const {return L"optional";}
  void accept(Visitor &v) {v.visitOptional(this);}
  bool isOptional() const {return true;}
  bool isLL(size_t k) {return isLLOptionalOrMultiple(k);}
  bool derivesToEmptySequence() const {return true;}
  virtual void setConflictId(int id) {conflictId = id;}

  void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    if (firstElementChild)
    {
      result.insertAll(firstElementChild->first(k));
    }
    result.insert(grammar->tokenSequenceFactory->emptySequence());
  }

  int conflictCaseId;
  int conflictId;
};

class ZeroOrMore : public NodeWithChildren
{
public:
  ZeroOrMore() : conflictCaseId(-1), conflictId(-1), loopId(0), runOffLoad(false) {}
  virtual ~ZeroOrMore() {}

  const wchar_t *getNodeType() const {return L"zeroOrMore";}
  virtual void accept(Visitor &v) {v.visitZeroOrMore(this);}
  virtual bool isZeroOrMore() const {return true;}
  virtual bool isLL(size_t k) {return isLLOptionalOrMultiple(k);}
  virtual bool derivesToEmptySequence() const {return true;}
  virtual void setConflictId(int id) {conflictId = id;}

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    if (firstElementChild != 0)
    {
      const TokenSequenceSet f = firstElementChild->first(k);
      result.insertAll(f);
      result.insertUpsized(f, firstAccessor, k, grammar->tokenSequenceFactory);
    }
    result.insert(grammar->tokenSequenceFactory->emptySequence());
  }

  int conflictCaseId;
  int conflictId;

  int loopId;
  bool runOffLoad;
};

class OneOrMore : public NodeWithChildren
{
public:
  OneOrMore() : conflictCaseId(-1), conflictId(-1), loopId(0), runOffLoad(false) {}
  virtual ~OneOrMore() {}

  const wchar_t *getNodeType() const {return L"oneOrMore";}
  virtual void accept(Visitor &v) {v.visitOneOrMore(this);}
  virtual bool isOneOrMore() const {return true;}
  virtual bool isLL(size_t k) {return isLLOptionalOrMultiple(k);}
  virtual void setConflictId(int id) {conflictId = id;}

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    if (firstElementChild != 0)
    {
      const TokenSequenceSet f = firstElementChild->first(k);
      result.insertAll(f);
      result.insertUpsized(f, firstAccessor, k, grammar->tokenSequenceFactory);
    }
    else
    {
      result.insert(grammar->tokenSequenceFactory->emptySequence());
    }
  }

  int conflictCaseId;
  int conflictId;

  int loopId;
  bool runOffLoad;
};

class Ref : public NodeWithContext
{
public:
  Ref(wchar_t *aName) : name(aName), nonTerminal(0) {}

  virtual ~Ref()
  {
    free(name);
  }

  const wchar_t *getNodeType() const {return L"ref";}
  virtual bool isRef() const {return true;}
  virtual void accept(Visitor &v) {v.visitRef(this);}
  virtual bool isLL(size_t k) {return true;}
  virtual bool isTerminalShift() const {return lexical != 0;}

  virtual Production *shiftSymbol()
  {
    if (lexical)
    {
      return lexical;
    }
    else
    {
      return nonTerminal;
    }
  }

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    if (lexical)
    {
      result.insert(grammar->tokenSequence(lexical->tokenCode));
    }
    else
    {
      result.insertAll(nonTerminal->first(k));
    }
  }

  virtual bool isLeftRecursive()
  {
    if (lexical == 0)
    {
      if (leftRecursive)
      {
        nonTerminal->leftRecursive = true;
      }
      else
      {
        leftRecursive = true;
        nonTerminal->isLeftRecursive();
        leftRecursive = false;
      }
    }
    return leftRecursive;
  }

  wchar_t *name;
  Production *nonTerminal;
};

class String : public NodeWithContext
{
public:
  String(wchar_t *aValue) : value(aValue) {}

  virtual ~String()
  {
    free(value);
  }

  const wchar_t *getNodeType() const {return L"string";}
  virtual void accept(Visitor &v) {v.visitString(this);}
  virtual bool isLL(size_t k) {return true;}
  virtual bool isString() const {return true;}
  virtual bool isTerminalShift() const {return true;}

  virtual Production *shiftSymbol()
  {
    return lexical;
  }

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    if (lexical == 0)
    {
      internalerr();
    }
    result.insert(grammar->tokenSequence(lexical->tokenCode));
  }

  wchar_t *value;
};

class ProcessingInstruction : public NodeWithContext
{
public:
  ProcessingInstruction(wchar_t *aTarget, int aLine, const wchar_t *aFileName, wchar_t *aContent)
  : target(aTarget),
    line(aLine),
    fileName(aFileName),
    content(aContent),
    active(false),
    contentId(-1)
  {}

  virtual ~ProcessingInstruction()
  {
    free(target);
    free(content);
  }

  const wchar_t *getNodeType() const {return L"processing-instruction";}
  virtual void accept(Visitor &v) {v.visitProcessingInstruction(this);}
  bool isElement() const {return false;}
  bool isActive() const {return active;}
  bool isLL(size_t k) {return true;}
  bool derivesToEmptySequence() const {return true;}

  virtual void calculateFirst(size_t k, TokenSequenceSet &result)
  {
    result.insert(grammar->tokenSequenceFactory->emptySequence());
  }

//  void fastFollow(size_t k, TokenSequenceSet &result, NodePointerSet &transitive) {throw Complaint(L"internal error: fastFollow() not implemented for node type ", getNodeType());}
//  void fastFollowItem(size_t k, TokenSequenceSet &result, NodePointerSet &transitive) {throw Complaint(L"internal error: fastFollowItem() not implemented for node type ", getNodeType());}

  Node *element() {return followingElementSibling;}

  bool isProcessingInstruction() const {return true;}
  bool hasActiveProcessingInstruction() const {return isActive();}

  int getContentId() const {return contentId;}

  wchar_t *target;
  int line;
  const wchar_t *fileName;
  wchar_t *content;

  friend class Relink;

private:
  bool active;
  int contentId;
};

class Exclusion : public Node
{
public:
  Exclusion(Node *aLhs, Node *aRhs) : lhs(aLhs), rhs(aRhs)
  {
    lhs->setParent(this);
    rhs->setParent(this);
  }

  virtual ~Exclusion()
  {
    delete lhs;
    delete rhs;
  }

  const wchar_t *getNodeType() const {return L"subtract";}
  virtual void accept(Visitor &v) {v.visitExclusion(this);}
  Node *lhs;
  Node *rhs;
};

class Context : public Node
{
public:
  Context(Node *anExpr, Node *aContext) : expr(anExpr), context(aContext)
  {
    expr->setParent(this);
    context->setParent(this);
  }

  virtual ~Context()
  {
    delete expr;
    delete context;
  }

  const wchar_t *getNodeType() const {return L"context";}
  virtual void accept(Visitor &v) {v.visitContext(this);}
  Node *expr;
  Node *context;
};

class EndOfFile : public Node
{
public:
  EndOfFile() {}
  const wchar_t *getNodeType() const {return L"endOfFile";}
  virtual void accept(Visitor &v) {v.visitEndOfFile(this);}
  virtual bool isEndOfFile() const {return true;}
};

class Char : public Node
{
public:
  Char(wchar_t aCharacter) : character(aCharacter) {}
  const wchar_t *getNodeType() const {return L"char";}
  virtual void accept(Visitor &v) {v.visitChar(this);}
  virtual bool isChar() const {return true;}
  wchar_t character;
};

class CharCode : public Node
{
public:
  CharCode(int aValue) : value(aValue) {}
  const wchar_t *getNodeType() const {return L"charCode";}
  virtual void accept(Visitor &v) {v.visitCharCode(this);}
  virtual bool isCharCode() const {return true;}
  int value;
};

class CharRange : public Node
{
public:
  CharRange(int offset, wchar_t aMinChar, wchar_t aMaxChar) : minChar(aMinChar), maxChar(aMaxChar)
  {
    if (minChar > maxChar)
    {
      throw Complaint(L"invalid character range, lower bound exceeds upper", L"", offset);
    }
  }

  const wchar_t *getNodeType() const {return L"charRange";}
  virtual void accept(Visitor &v) {v.visitCharRange(this);}
  virtual bool isCharRange() const {return true;}
  wchar_t minChar;
  wchar_t maxChar;
};

class CharCodeRange : public Node
{
public:
  CharCodeRange(int offset, int aMinValue, int aMaxValue) : minValue(aMinValue), maxValue(aMaxValue)
  {
    if (minValue > maxValue)
    {
      throw Complaint(L"invalid codepoint range, lower bound exceeds upper", L"", offset);
    }
  }

  const wchar_t *getNodeType() const {return L"charCodeRange";}
  virtual void accept(Visitor &v) {v.visitCharCodeRange(this);}
  virtual bool isCharCodeRange() const {return true;}
  int minValue;
  int maxValue;
};

class Complement : public Node
{
public:
  Complement(CharClass *aCharClass) : charClass(aCharClass) {}

  virtual ~Complement()
  {
    delete charClass;
  }

  const wchar_t *getNodeType() const {return L"complement";}
  virtual void accept(Visitor &v) {v.visitComplement(this);}
  CharClass *charClass;
};

class Preference : public Node
{
public:
  void addLhs(Node *aLhs)
  {
    aLhs->setParent(this);
    lhs.push_back(aLhs);
  }

  void addRhs(Node *aRhs)
  {
    aRhs->setParent(this);
    rhs.push_back(aRhs);
  }

  const wchar_t *getNodeType() const {return L"preference";}
  virtual void accept(Visitor &v) {v.visitPreference(this);}
  NodeList lhs;
  NodeList rhs;
};

class Delimiter : public Node
{
public:
  Delimiter(Node *aLhs) : lhs(aLhs)
  {
    lhs->setParent(this);
  }

  virtual ~Delimiter()
  {
    delete lhs;
  }

  void addRhs(Node *aRhs)
  {
    aRhs->setParent(this);
    rhs.push_back(aRhs);
  }

  const wchar_t *getNodeType() const {return L"delimiter";}
  virtual void accept(Visitor &v) {v.visitDelimiter(this);}
  Node *lhs;
  NodeList rhs;
};

class Equivalence : public Node
{
public:
  Equivalence() : lhs(0), rhs(0) {}

  virtual ~Equivalence()
  {
    delete lhs;
    delete rhs;
  }

  void setLhs(Node *aLhs)
  {
    lhs = aLhs;
  }

  void setRhs(Node *aRhs)
  {
    rhs = aRhs;
  }

  const wchar_t *getNodeType() const {return L"equivalence";}
  virtual void accept(Visitor &v) {v.visitEquivalence(this);}
  Node *lhs;
  Node *rhs;
};

class Reduce : public NodeWithContext
{
public:
  Reduce(int nonterminalCode,
         int count,
         ProcessingInstruction *processingInstruction,
         bool isImplicit,
         Node *restrictedCase,
         Grammar *grammar)
  : nonterminalCode(nonterminalCode)
  , processingInstruction(processingInstruction)
  , reduceCase(-1)
  , isImplicit(isImplicit)
  , restrictedCase(restrictedCase)
  {
    this->grammar = grammar;
    NodeWithContext::setDistance(count);
  }

  virtual ~Reduce() {}
  const wchar_t *getNodeType() const {return L"reduce";}
  virtual void accept(Visitor &v) {internalerr();}

  virtual bool isReduce() const {return true;}
  virtual void calculateFirst(size_t k, TokenSequenceSet &result) {internalerr();}
  virtual void setDistance(int d) {internalerr();}

  virtual Node *getParent() const
  {
    return restrictedCase;
  }

  Node *closestRestrictedCaseAncestor()
  {
    return restrictedCase;
  }

  int nonterminalCode;
  ProcessingInstruction *processingInstruction;
  int reduceCase;
  bool isImplicit;
  Node *restrictedCase;
};

#endif
