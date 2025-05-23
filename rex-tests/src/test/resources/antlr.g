header {
package antlr;
}

{
import java.util.Enumeration;
import java.io.DataInputStream;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.IOException;
}

/* ANTLR Translator Generator
 * Project led by Terence Parr at http://www.cs.usfca.edu
 * Software rights: http://www.antlr.org/license.html
 *
 * $Id: //depot/code/org.antlr/release/antlr-2.7.7/antlr/antlr.g#2 $
 */

class ANTLRParser extends Parser;
options {
   exportVocab=ANTLR;
   defaultErrorHandler=false;
   k=2;
}

tokens {
   "tokens";
}

{
   private static final boolean DEBUG_PARSER = false;

   ANTLRGrammarParseBehavior behavior;
   Tool antlrTool;
   protected int blockNesting= -1;

   public ANTLRParser(
      TokenBuffer tokenBuf,
      ANTLRGrammarParseBehavior behavior_,
      Tool tool_
   ) {
      super(tokenBuf, 1);
      tokenNames = _tokenNames;
      behavior = behavior_;
      antlrTool = tool_;
   }

        public void reportError(String s) {
            antlrTool.error(s, getFilename(), -1, -1);
        }

        public void reportError(RecognitionException e) {
            reportError(e, e.getErrorMessage());
        }

        public void reportError(RecognitionException e, String s) {
            antlrTool.error(s, e.getFilename(), e.getLine(), e.getColumn());
        }

        public void reportWarning(String s) {
            antlrTool.warning(s, getFilename(), -1, -1);
        }

   private boolean lastInRule() throws TokenStreamException {
      if ( blockNesting==0 && (LA(1)==SEMI || LA(1)==LITERAL_exception || LA(1)==OR) ) {
         return true;
      }
      return false;
   }

   private void checkForMissingEndRule(Token label) {
      if ( label.getColumn()==1 ) {
         antlrTool.warning("did you forget to terminate previous rule?", getFilename(), label.getLine(), label.getColumn());
      }
   }
}

grammar
   :
   (  {
         n = null;   // RK: prevent certain orders of header actions
                     // overwriting eachother.
      }
      "header"
      (n:STRING_LITERAL)?
      h:ACTION
      {
         // store the header action
         // FIXME: 'n' should be checked for validity
         behavior.refHeaderAction(n,h);
      }
   )*
   ( fileOptionsSpec )?
   ( classDef )*
   EOF
   ;
   exception catch [RecognitionException ex] {
        reportError(ex, "rule grammar trapped:\n"+ex.toString());
      consumeUntil(EOF);
   }

classDef
{String doc=null;}
   :
   ( a:ACTION { behavior.refPreambleAction(a);} )?
   ( d:DOC_COMMENT {doc=d.getText();} )?
   (  ("lexclass" | "class" id "extends" "Lexer" ) => lexerSpec[doc]
   |  ( "class" id "extends" "TreeParser" ) => treeParserSpec[doc]
   |  parserSpec[doc]
   )
   rules
   { behavior.endGrammar(); }
   ;
   exception catch [RecognitionException ex] {
      if ( ex instanceof NoViableAltException ) {
         NoViableAltException e = (NoViableAltException)ex;
         // RK: These probably generate inconsequent error messages...
         // have to see how this comes out..
         if ( e.token.getType()==DOC_COMMENT ) {
            reportError(ex, "JAVADOC comments may only prefix rules and grammars");
         }
         else {
            reportError(ex, "rule classDef trapped:\n"+ex.toString());
         }
      }
      else {
         reportError(ex, "rule classDef trapped:\n"+ex.toString());
      }
      behavior.abortGrammar();
      boolean consuming = true;
      // consume everything until the next class definition or EOF
      while (consuming) {
         consume();
         switch(LA(1)) {
         case LITERAL_class:
         case LITERAL_lexclass:
         case EOF:
            consuming = false;
            break;
         }
      }
   }

fileOptionsSpec
{ Token idTok; Token value; }
   :  OPTIONS
      (
         idTok = id
         ASSIGN
         value = optionValue
         { behavior.setFileOption(idTok, value,getInputState().filename); }
         SEMI
      )*
      RCURLY
   ;

parserOptionsSpec
{ Token idTok; Token value; }
   :  OPTIONS
      (
         idTok = id
         ASSIGN
         value = optionValue
         { behavior.setGrammarOption(idTok, value); }
         SEMI
      )*
      RCURLY
   ;

treeParserOptionsSpec
{ Token idTok; Token value; }
   :  OPTIONS
      (
         idTok = id
         ASSIGN
         value = optionValue
         { behavior.setGrammarOption(idTok, value); }
         SEMI
      )*
      RCURLY
   ;

lexerOptionsSpec
{ Token idTok; Token value; BitSet b; }
   :
   OPTIONS
   (  // Special case for vocabulary option because it has a bit-set
      "charVocabulary"
      ASSIGN
      b = charSet
      SEMI
      { behavior.setCharVocabulary(b); }

   |  idTok = id
      ASSIGN
      value = optionValue
      { behavior.setGrammarOption(idTok, value); }
      SEMI
   )*
   RCURLY
   ;

subruleOptionsSpec
{ Token idTok; Token value; }
   :  OPTIONS
      (  idTok = id
         ASSIGN
         value = optionValue
         { behavior.setSubruleOption(idTok, value); }
         SEMI
      )*
      RCURLY
   ;

// optionValue returns a Token which may be one of several things:
//    STRING_LITERAL -- a quoted string
//    CHAR_LITERAL -- a single quoted character
//    INT -- an integer
//    RULE_REF or TOKEN_REF -- an identifier
optionValue
returns [ Token retval ]
{ retval = null; }
   :  retval = qualifiedID
   |  sl:STRING_LITERAL { retval = sl; }
   |  cl:CHAR_LITERAL { retval = cl; }
   |  il:INT { retval = il; }
   ;

charSet
returns [ BitSet b ]
{
   b = null;
   BitSet tmpSet = null;
}
   :
      // TODO: generate a bit set
      b = setBlockElement
      (
         OR
         tmpSet = setBlockElement
         { b.orInPlace(tmpSet); }
      )*
   ;

setBlockElement
returns [ BitSet b ]
{
   b = null;
   int rangeMin = 0;
}
   :
   c1:CHAR_LITERAL
   {
      rangeMin = ANTLRLexer.tokenTypeForCharLiteral(c1.getText());
      b = BitSet.of(rangeMin);
   }
   (
      RANGE c2:CHAR_LITERAL
      {
         int rangeMax = ANTLRLexer.tokenTypeForCharLiteral(c2.getText());
         if (rangeMax < rangeMin) {
            antlrTool.error("Malformed range line ", getFilename(), c1.getLine(), c1.getColumn());
         }
         for (int i = rangeMin+1; i <= rangeMax; i++) {
            b.add(i);
         }
      }
   )?
   ;

tokensSpec
   :  TOKENS
         (  (  {s1=null;}
               t1:TOKEN_REF
               ( ASSIGN s1:STRING_LITERAL )?
               {behavior.defineToken(t1, s1);}
               (tokensSpecOptions[t1])?
            |  s3:STRING_LITERAL
               {behavior.defineToken(null, s3);}
               (tokensSpecOptions[s3])?
            )
            SEMI
         )+
      RCURLY
   ;

tokensSpecOptions[Token t]
{
   Token o=null, v=null;
}
   :  OPEN_ELEMENT_OPTION
      o=id ASSIGN v=optionValue
      {behavior.refTokensSpecElementOption(t,o,v);}
      (
         SEMI
         o=id ASSIGN v=optionValue
         {behavior.refTokensSpecElementOption(t,o,v);}
      )*
      CLOSE_ELEMENT_OPTION
   ;

superClass returns [String sup]
{sup=null;}
   :  LPAREN
         {
         sup = LT(1).getText();
         sup = StringUtils.stripFrontBack(sup, "\"", "\"");
         }
         (STRING_LITERAL)
      RPAREN
   ;

parserSpec[String doc]
{
   Token idTok;
   String sup=null;
}
   :  "class"
      idTok = id
      (  "extends" "Parser"
         (sup=superClass)?
      |  {
         antlrTool.warning("use 'class X extends Parser'", getFilename(), idTok.getLine(), idTok.getColumn());
//       System.out.println("warning: line " +
//          idTok.getLine() + ": use 'class X extends Parser'");
         }
      )
      {behavior.startParser(getFilename(), idTok, sup, doc);}
      SEMI
      (parserOptionsSpec)?
      { behavior.endOptions(); }
      (tokensSpec)?
      ( a:ACTION {behavior.refMemberAction(a);} )?
   ;

lexerSpec[String doc]
{
   Token idTok;
   String sup=null;
}
   :   ( lc:"lexclass"
         idTok = id
         {
            antlrTool.warning("lexclass' is deprecated; use 'class X extends Lexer'",
                         getFilename(), lc.getLine(), lc.getColumn());
//          System.out.println("warning: line " + lc.getLine() + ": 'lexclass' is deprecated; use 'class X extends Lexer'");
         }
      |  "class"
         idTok = id
         "extends"
         "Lexer"
         (sup=superClass)?
      )
      {behavior.startLexer(getFilename(), idTok,sup,doc);}
      SEMI
      (lexerOptionsSpec)?
      { behavior.endOptions(); }
      (tokensSpec)?
      ( a:ACTION {behavior.refMemberAction(a);} )?
   ;

treeParserSpec[String doc]
{
   Token idTok;
   String sup=null;
}
   :  "class"
      idTok = id
      "extends"
      "TreeParser"
      (sup=superClass)?
      {behavior.startTreeWalker(getFilename(), idTok,sup,doc);}
      SEMI
      (treeParserOptionsSpec)?
      { behavior.endOptions(); }
      (tokensSpec)?
      ( a:ACTION {behavior.refMemberAction(a);} )?
   ;

rules
    :   (
         options {
            // limitation of appox LL(k) says ambig upon
            // DOC_COMMENT TOKEN_REF, but that's an impossible sequence
            warnWhenFollowAmbig=false;
         }
      :  rule
      )+
    ;

rule
{
   String access="public";
   Token idTok;
   String doc=null;
   boolean ruleAutoGen = true;
   blockNesting = -1;   // block increments, so -1 to make rule at level 0
}
   :
   (  d:DOC_COMMENT  {doc=d.getText();}
   )?
   (  p1:"protected" {access=p1.getText();}
   |  p2:"public"    {access=p2.getText();}
   |  p3:"private"   {access=p3.getText();}
   )?
   idTok = id
   ( BANG { ruleAutoGen = false; } )?
   {
      behavior.defineRuleName(idTok, access, ruleAutoGen, doc);
   }
   ( aa:ARG_ACTION { behavior.refArgAction(aa); }  )?
   ( "returns" rt:ARG_ACTION { behavior.refReturnAction(rt); } )?
   ( throwsSpec )?
   ( ruleOptionsSpec )?
   (a:ACTION {behavior.refInitAction(a);})?
   COLON block SEMI
   ( exceptionGroup )?
   {behavior.endRule(idTok.getText());}
   ;
/*
   //
   // for now, syntax error in rule aborts the whole grammar
   //
   exception catch [ParserException ex] {
      behavior.abortRule(idTok);
      behavior.hasError();
      // Consume until something that looks like end of a rule
      consume();
      while (LA(1) != SEMI && LA(1) != EOF) {
         consume();
      }
      consume();
   }
*/

ruleOptionsSpec
{ Token idTok; Token value; }
   :  OPTIONS
      (
         idTok = id
         ASSIGN
         value = optionValue
         { behavior.setRuleOption(idTok, value); }
         SEMI
      )*
      RCURLY
   ;

throwsSpec
{
   String t=null;
   Token a,b;
}
   :  "throws" a=id {t=a.getText();}
      ( COMMA b=id {t+=","+b.getText();} )*
      { behavior.setUserExceptions(t); }
   ;

block
    :   {blockNesting++;}
      alternative ( OR alternative )*
      {blockNesting--;}
    ;

alternative
{ boolean altAutoGen = true; }
    :
      (BANG { altAutoGen=false;} )?
      {behavior.beginAlt(altAutoGen);}
      ( element )* ( exceptionSpecNoLabel )?
      {behavior.endAlt();}
    ;

exceptionGroup
   :  { behavior.beginExceptionGroup(); }
      ( exceptionSpec )+
      { behavior.endExceptionGroup(); }
   ;

exceptionSpec
{ Token labelAction = null; }
   :
   "exception"
   ( aa:ARG_ACTION { labelAction = aa; } )?
   { behavior.beginExceptionSpec(labelAction); }
   ( exceptionHandler )*
   { behavior.endExceptionSpec(); }
   ;

exceptionSpecNoLabel
   :
   "exception"
   { behavior.beginExceptionSpec(null); }
   ( exceptionHandler )*
   { behavior.endExceptionSpec(); }
   ;

exceptionHandler
{ Token exType; Token exName; }
   :
   "catch"
   a1:ARG_ACTION
   a2:ACTION
   { behavior.refExceptionHandler(a1, a2); }
   ;

element
   :  elementNoOptionSpec (elementOptionSpec)?
   ;

elementOptionSpec
{
   Token o=null, v=null;
}
   :  OPEN_ELEMENT_OPTION
      o=id ASSIGN v=optionValue
      {behavior.refElementOption(o,v);}
      (
         SEMI
         o=id ASSIGN v=optionValue
         {behavior.refElementOption(o,v);}
      )*
      CLOSE_ELEMENT_OPTION
   ;

elementNoOptionSpec
{
   Token label = null;
   Token assignId = null;
   Token args = null;
   int autoGen = GrammarElement.AUTO_GEN_NONE;
}
   :  assignId=id
      ASSIGN
      ( label=id COLON {checkForMissingEndRule(label);} )?
      (  rr:RULE_REF
         ( aa:ARG_ACTION { args=aa; } )?
         ( BANG { autoGen = GrammarElement.AUTO_GEN_BANG; } )?
         { behavior.refRule(assignId, rr, label, args, autoGen); }
      |  // this syntax only valid for lexer
         tr:TOKEN_REF
         ( aa2:ARG_ACTION { args=aa2; } )?
         { behavior.refToken(assignId, tr, label, args, false, autoGen, lastInRule()); }
      )
   |
      (label=id COLON {checkForMissingEndRule(label);} )?
      (  r2:RULE_REF
         ( aa3:ARG_ACTION { args=aa3; } )?
         ( BANG { autoGen = GrammarElement.AUTO_GEN_BANG; } )?
         { behavior.refRule(assignId, r2, label, args, autoGen); }
      |
         range [label]
      |
         terminal [label]
      |
         NOT_OP
         (  notTerminal[label]
         |  ebnf[label,true]
         )
      |
         ebnf[label,false]
      )
   |
      a:ACTION { behavior.refAction(a);}
   |
      p:SEMPRED   { behavior.refSemPred(p);}
   |
      tree
   ;

tree :
   lp:TREE_BEGIN
   { behavior.beginTree(lp); }
   rootNode
   {behavior.beginChildList();}
   ( element )+
   {behavior.endChildList();}
   RPAREN
   { behavior.endTree(); }
   ;

rootNode
{ Token label = null; }
   :
      (label=id COLON {checkForMissingEndRule(label);} )?
      terminal[label]
// |  range[null]
   ;

ebnf
[ Token label, boolean not ]
   :  lp:LPAREN
      {behavior.beginSubRule(label, lp, not);}

      (
         // 2nd alt and optional branch ambig due to
         // linear approx LL(2) issue.  COLON ACTION
         // matched correctly in 2nd alt.
         options {
            warnWhenFollowAmbig = false;
         }
      :
         subruleOptionsSpec
         ( aa:ACTION {behavior.refInitAction(aa);} )?
         COLON
      |  ab:ACTION {behavior.refInitAction(ab);}
         COLON
      )?

      block
      RPAREN

      (  (  QUESTION{behavior.optionalSubRule();}
         |  STAR  {behavior.zeroOrMoreSubRule();}
         |  PLUS  {behavior.oneOrMoreSubRule();}
         )?
         ( BANG {behavior.noASTSubRule(); } )?
      |
         IMPLIES  {behavior.synPred();}
      )
      {behavior.endSubRule();}
   ;

ast_type_spec
returns [ int autoGen ]
{ autoGen = GrammarElement.AUTO_GEN_NONE; }
   :  (  CARET { autoGen = GrammarElement.AUTO_GEN_CARET; }
      |  BANG { autoGen = GrammarElement.AUTO_GEN_BANG; }
      )?
   ;

range
[ Token label ]
{
   Token trLeft=null;
   Token trRight=null;
   int autoGen=GrammarElement.AUTO_GEN_NONE;
}
   :  crLeft:CHAR_LITERAL RANGE crRight:CHAR_LITERAL
      ( BANG { autoGen = GrammarElement.AUTO_GEN_BANG; } )?
      { behavior.refCharRange(crLeft, crRight, label, autoGen, lastInRule()); }
   |
      (t:TOKEN_REF{trLeft=t;}|u:STRING_LITERAL{trLeft=u;})
      RANGE
      (v:TOKEN_REF{trRight=v;}|w:STRING_LITERAL{trRight=w;})
      autoGen = ast_type_spec
      { behavior.refTokenRange(trLeft, trRight, label, autoGen, lastInRule()); }
   ;

terminal
[ Token label ]
{
   int autoGen=GrammarElement.AUTO_GEN_NONE;
   Token args=null;
}
   :
      cl:CHAR_LITERAL
      ( BANG { autoGen = GrammarElement.AUTO_GEN_BANG; } )?
      {behavior.refCharLiteral(cl, label, false, autoGen, lastInRule());}
   |
      tr:TOKEN_REF
      autoGen = ast_type_spec
      // Args are only valid for lexer
      ( aa:ARG_ACTION { args=aa; } )?
      { behavior.refToken(null, tr, label, args, false, autoGen, lastInRule()); }
   |
      sl:STRING_LITERAL
      autoGen = ast_type_spec
      {behavior.refStringLiteral(sl, label, autoGen, lastInRule());}
   |
      wi:WILDCARD
      autoGen = ast_type_spec
      {behavior.refWildcard(wi, label, autoGen);}
   ;

notTerminal
[ Token label ]
{ int autoGen=GrammarElement.AUTO_GEN_NONE; }
   :
      cl:CHAR_LITERAL
      ( BANG { autoGen = GrammarElement.AUTO_GEN_BANG; } )?
      {behavior.refCharLiteral(cl, label, true, autoGen, lastInRule());}
   |
      tr:TOKEN_REF
      autoGen = ast_type_spec
      {behavior.refToken(null, tr, label, null, true, autoGen, lastInRule());}
   ;

/** Match a.b.c.d qualified ids; WILDCARD here is overloaded as
 *  id separator; that is, I need a reference to the '.' token.
 */
qualifiedID returns [Token qidTok=null]
{
   StringBuffer buf = new StringBuffer(30);
   Token a;
}
   :  a=id {buf.append(a.getText());}
      (  WILDCARD a=id
         {buf.append('.'); buf.append(a.getText());}
      )*
      {
       // can use either TOKEN_REF or RULE_REF; should
       // really create a QID or something instead.
       qidTok = new CommonToken(TOKEN_REF, buf.toString());
       qidTok.setLine(a.getLine());
      }
   ;

id
returns [ Token idTok ]
{ idTok = null; }
   :  a:TOKEN_REF       {idTok = a;}
   |  b:RULE_REF        {idTok = b;}
   ;

class ANTLRLexer extends Lexer;
options {
   k=2;
   exportVocab=ANTLR;
   testLiterals=false;
   interactive=true;
   charVocabulary='\003'..'\377';
}

tokens {
   "options";
}

{
   /**Convert 'c' to an integer char value. */
   public static int escapeCharValue(String cs) {
      //System.out.println("escapeCharValue("+cs+")");
      if ( cs.charAt(1)!='\\' ) return 0;
      switch ( cs.charAt(2) ) {
      case 'b' : return '\b';
      case 'r' : return '\r';
      case 't' : return '\t';
      case 'n' : return '\n';
      case 'f' : return '\f';
      case '"' : return '\"';
      case '\'' :return '\'';
      case '\\' :return '\\';

      case 'u' :
         // Unicode char
         if (cs.length() != 8) {
            return 0;
         }
         else {
            return
               Character.digit(cs.charAt(3), 16) * 16 * 16 * 16 +
               Character.digit(cs.charAt(4), 16) * 16 * 16 +
               Character.digit(cs.charAt(5), 16) * 16 +
               Character.digit(cs.charAt(6), 16);
         }

      case '0' :
      case '1' :
      case '2' :
      case '3' :
         if ( cs.length()>5 && Character.isDigit(cs.charAt(4)) ) {
            return (cs.charAt(2)-'0')*8*8 + (cs.charAt(3)-'0')*8 + (cs.charAt(4)-'0');
         }
         if ( cs.length()>4 && Character.isDigit(cs.charAt(3)) ) {
            return (cs.charAt(2)-'0')*8 + (cs.charAt(3)-'0');
         }
         return cs.charAt(2)-'0';

      case '4' :
      case '5' :
      case '6' :
      case '7' :
         if ( cs.length()>4 && Character.isDigit(cs.charAt(3)) ) {
            return (cs.charAt(2)-'0')*8 + (cs.charAt(3)-'0');
         }
         return cs.charAt(2)-'0';

      default :
         return 0;
      }
   }

   public static int tokenTypeForCharLiteral(String lit) {
      if ( lit.length()>3 ) {  // does char contain escape?
         return escapeCharValue(lit);
      }
      else {
         return lit.charAt(1);
      }
   }
}

WS :  (  /* '\r' '\n' can be matched in one alternative or by matching
            '\r' in one iteration and '\n' in another.  I am trying to
            handle any flavor of newline that comes in, but the language
            that allows both "\r\n" and "\r" and "\n" to all be valid
            newline is ambiguous.  Consequently, the resulting grammar
            must be ambiguous.  I'm shutting this warning off.
          */
         options {
            generateAmbigWarnings=false;
         }
      :  ' '
      |  '\t'
      |  '\r' '\n'   {newline();}
      |  '\r'     {newline();}
      |  '\n'     {newline();}
      )
      { $setType(Token.SKIP); }
   ;

COMMENT :
   ( SL_COMMENT | t:ML_COMMENT {$setType(t.getType());} )
   {if ( _ttype != DOC_COMMENT ) $setType(Token.SKIP);}
   ;

protected
SL_COMMENT :
   "//"
   ( ~('\n'|'\r') )*
   (
      /* '\r' '\n' can be matched in one alternative or by matching
         '\r' and then in the next token.  The language
         that allows both "\r\n" and "\r" and "\n" to all be valid
         newline is ambiguous.  Consequently, the resulting grammar
         must be ambiguous.  I'm shutting this warning off.
       */
         options {
            generateAmbigWarnings=false;
         }
      :  '\r' '\n'
      |  '\r'
      |  '\n'
   )
   { newline(); }
   ;

protected
ML_COMMENT :
   "/*"
   (  { LA(2)!='/' }? '*' {$setType(DOC_COMMENT);}
   |
   )
   (
      /* '\r' '\n' can be matched in one alternative or by matching
         '\r' and then in the next token.  The language
         that allows both "\r\n" and "\r" and "\n" to all be valid
         newline is ambiguous.  Consequently, the resulting grammar
         must be ambiguous.  I'm shutting this warning off.
       */
      options {
         greedy=false;  // make it exit upon "*/"
         generateAmbigWarnings=false; // shut off newline errors
      }
   :  '\r' '\n'   {newline();}
   |  '\r'     {newline();}
   |  '\n'     {newline();}
   |  ~('\n'|'\r')
   )*
   "*/"
   ;

OPEN_ELEMENT_OPTION
   :  '<'
   ;

CLOSE_ELEMENT_OPTION
   :  '>'
   ;

COMMA : ',';

QUESTION :  '?' ;

TREE_BEGIN : "#(" ;

LPAREN:  '(' ;

RPAREN:  ')' ;

COLON :  ':' ;

STAR: '*' ;

PLUS: '+' ;

ASSIGN : '=' ;

IMPLIES : "=>" ;

SEMI: ';' ;

CARET : '^' ;

BANG : '!' ;

OR :  '|' ;

WILDCARD : '.' ;

RANGE : ".." ;

NOT_OP : '~' ;

RCURLY:  '}'   ;

CHAR_LITERAL
   :  '\'' (ESC|~'\'') '\''
   ;

STRING_LITERAL
   :  '"' (ESC|~'"')* '"'
   ;

protected
ESC   :  '\\'
      (  'n'
      |  'r'
      |  't'
      |  'b'
      |  'f'
      |  'w'
      |  'a'
      |  '"'
      |  '\''
      |  '\\'
      |  ('0'..'3')
         ( options { warnWhenFollowAmbig = false; }: '0'..'7'
         ( options { warnWhenFollowAmbig = false; }: '0'..'7'
         )?
         )?
      |  ('4'..'7')
         ( options { warnWhenFollowAmbig = false; }: '0'..'7' )?
      |  'u' XDIGIT XDIGIT XDIGIT XDIGIT
      )
   ;

protected
DIGIT
   :  '0'..'9'
   ;

protected
XDIGIT :
      '0' .. '9'
   |  'a' .. 'f'
   |  'A' .. 'F'
   ;

INT   :  ('0'..'9')+
   ;

ARG_ACTION
   :
   NESTED_ARG_ACTION
   { setText(StringUtils.stripFrontBack(getText(), "[", "]")); }
   ;

protected
NESTED_ARG_ACTION :
   '['
   (
      /* '\r' '\n' can be matched in one alternative or by matching
         '\r' and then '\n' in the next iteration.
       */
      options {
         generateAmbigWarnings=false; // shut off newline errors
      }
   :  NESTED_ARG_ACTION
   |  '\r' '\n'   {newline();}
   |  '\r'     {newline();}
   |  '\n'     {newline();}
   |  CHAR_LITERAL
   |  STRING_LITERAL
   |  ~']'
   )*
   ']'
   ;

ACTION
{int actionLine=getLine(); int actionColumn = getColumn(); }
   :  NESTED_ACTION
      (  '?'   {_ttype = SEMPRED;} )?
      {
         if ( _ttype==ACTION ) {
            setText(StringUtils.stripFrontBack(getText(), "{", "}"));
         }
         else {
            setText(StringUtils.stripFrontBack(getText(), "{", "}?"));
         }
         CommonToken t = new CommonToken(_ttype,$getText);
         t.setLine(actionLine);        // set action line to start
         t.setColumn(actionColumn);
         $setToken(t);
      }
   ;

protected
NESTED_ACTION :
   '{'
   (
      options {
         greedy = false; // exit upon '}'
      }
   :
      (
         options {
            generateAmbigWarnings = false; // shut off newline warning
         }
      :  '\r' '\n'   {newline();}
      |  '\r'     {newline();}
      |  '\n'     {newline();}
      )
   |  NESTED_ACTION
   |  CHAR_LITERAL
   |  COMMENT
   |  STRING_LITERAL
   |  .
   )*
   '}'
   ;

TOKEN_REF
options { testLiterals = true; }
   :  'A'..'Z'
      (  // scarf as many letters/numbers as you can
         options {
            warnWhenFollowAmbig=false;
         }
      :
         'a'..'z'|'A'..'Z'|'_'|'0'..'9'
      )*
   ;

// we get a warning here when looking for options '{', but it works right
RULE_REF
{
   int t=0;
}
   :  t=INTERNAL_RULE_REF {_ttype=t;}
      (  {t==LITERAL_options}? WS_LOOP ('{' {_ttype = OPTIONS;})?
      |  {t==LITERAL_tokens}? WS_LOOP ('{' {_ttype = TOKENS;})?
      |
      )
   ;

protected
WS_LOOP
   :  (  // grab as much WS as you can
         options {
            greedy=true;
         }
      :
         WS
      |  COMMENT
      )*
   ;

protected
INTERNAL_RULE_REF returns [int t]
{
   t = RULE_REF;
}
   :  'a'..'z'
      (  // scarf as many letters/numbers as you can
         options {
            warnWhenFollowAmbig=false;
         }
      :
         'a'..'z'|'A'..'Z'|'_'|'0'..'9'
      )*
      {t = testLiteralsTable(t);}
   ;

protected
WS_OPT :
   (WS)?
   ;
