import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;

/**
 * An external lexer (or rather set of lexers) for the the XML grammar.
 */
public class XmlXlLexer implements XmlXl.Lexer {
  /** The end-of-input index. */
  private int endOfInput = 0;
  /** The list of matchers. */
  private Matcher[] matchers = new Matcher[lexers.length];

  @Override
  public void reset(CharSequence input) {
    this.endOfInput = input.length();
    // create new matchers for this instance
    for (int tokenSet = 0; tokenSet < lexers.length; ++tokenSet)
      this.matchers[tokenSet] = lexers[tokenSet].pattern.matcher(input);
  }

  @Override
  public void match(int tokenSet, XmlXl.Token token) {
    // get the token set's matcher
    Matcher matcher = matchers[tokenSet];
    // point matcher to input position
    matcher.region(token.begin, endOfInput);
    // do the actual matching
    matcher.lookingAt();
    // find matching token
    TokenDescriptor[] tokenDescriptors = lexers[tokenSet].tokenDescriptors;
    for (int i = 0; i < tokenDescriptors.length; ++i) {
      int end = matcher.end(i + 1);
      if (end >= 0) {
        token.code = tokenDescriptors[i].code;
        token.end = end;
        return;
      }
    }
    // no match
    token.code = -1;
    token.end = token.begin;
    return;
  }

  // regex fragments
  private static final String cLP = "(";     // capturing group left parenthesis
  private static final String cRP = ")";     // capturing group right parenthesis
  private static final String ncLP = "(?:";  // non-capturing group left parenthesis
  private static final String ncRP = ")";    // non-capturing group right parenthesis
  private static final String EOF = "$";
  private static final String S = "[ \\t\\n\\r]+";
  private static final String NameStartChar = "[:A-Z_a-z\u00C0-\u00D6\u00D8-\u00F6\u00F8-\u02FF\u0370-\u037D\u037F-\u1FFF\u200C-\u200D\u2070-\u218F\u2C00-\u2FEF\u3001-\uD7FF\uF900-\uFDCF\uFDF0-\uFFFD]";
  private static final String NameChar = NameStartChar.substring(0, NameStartChar.length() - 1) + "-\\.0-9\u00B7\u0300-\u036F\u203F-\u2040]";
  private static final String Name = NameStartChar + NameChar + "*";
  private static final String EntityRef = "&" + Name + ";";
  private static final String CharRef = "&#[0-9]+;|&#x[0-9a-fA-F]+;";
  private static final String Reference = EntityRef + "|" + CharRef;
  private static final String AttValue = "\"" + ncLP + "[^<&\"]|" + Reference + ncRP + "*\"|'" + ncLP + "[^<&']|" + Reference + ncRP + "*'";
  private static final String CharData = ncLP + "[^<&\\]]|\\]>|\\]+[^><&\\]]" + ncRP + "*\\]*";
  private static final String Comment = "<!--" + ncLP + "[^-]|-[^-]" + ncRP + "*-?-->";
  private static final String PI = "<\\?" + Name + ncLP + S + ncLP + "[^?]|\\?+[^?>]" + ncRP + "*\\?*" + ncRP + "?\\?>";
  private static final String CDStart = "<!\\[CDATA\\[";
  private static final String CData = ncLP + "[^\\]]|\\]>|\\]+[^>\\]]" + ncRP + "*\\]*";
  private static final String CDEnd = "\\]\\]>";
  private static final String CDSect = CDStart + CData + CDEnd;
  private static final String VersionNum = "1\\.[0-9]+";
  private static final String PubidChar = "[ \\r\\na-zA-Z0-9-'()+,./:=?;!*#@$_%]";
  private static final String PubidCharNoApos = "[ \\r\\na-zA-Z0-9-()+,./:=?;!*#@$_%]";
  private static final String Nmtoken = NameChar + "+";
  private static final String PEReference = "%" + Name + ";";
  private static final String EntityValue = "\"" + ncLP + "[^%&\"]|" + PEReference + "|" + ncLP + Reference + ncRP + ncRP + "*\"";
  private static final String SystemLiteral = ncLP + "\\\"[^\\\"]*\\\"" + ncRP + "|" + ncLP + "'[^']*'" + ncRP + "";
  private static final String PubidLiteral = ncLP + "\\\"" + PubidChar + "*\\\"" + ncRP + "|" + ncLP + "'" + PubidCharNoApos + "*'" + ncRP + "";
  private static final String EncName = "[A-Za-z][-A-Za-z0-9._]*";

  private static final ContextSpecificLexer[] lexers = new ContextSpecificLexer[XmlXl.getTokenSetCount()];

  static {
    final Map<String, String> regexByName = new HashMap<>();
    regexByName.put("(0)", "");
    regexByName.put("EOF", EOF);
    regexByName.put("S", S);
    regexByName.put("Name", Name);
    regexByName.put("AttValue", AttValue);
    regexByName.put("CharData", CharData);
    regexByName.put("Comment", Comment);
    regexByName.put("PI", PI);
    regexByName.put("CDSect", CDSect);
    regexByName.put("CharRef", CharRef);
    regexByName.put("Nmtoken", Nmtoken);
    regexByName.put("EntityValue", EntityValue);
    regexByName.put("SystemLiteral", SystemLiteral);
    regexByName.put("PubidLiteral", PubidLiteral);
    regexByName.put("VersionNum", VersionNum);
    regexByName.put("PEReference", PEReference);
    regexByName.put("EncName", EncName);

    // setup token descriptors
    final Map<String, TokenDescriptor> tokenDescriptorByName = new HashMap<String, TokenDescriptor>();
    for (int code = 0; code < XmlXl.getTokenCount(); ++code) {
      String tokenName = XmlXl.getTokenName(code);
      tokenDescriptorByName.put(tokenName, new TokenDescriptor(tokenName, code, regexByName.get(tokenName)));
    }

    // create a lexer for each token set
    for (int tokenSet = 0; tokenSet < lexers.length; ++tokenSet) {
      // get token names in this set
      Stream<String> expectedTokenset = Arrays.stream(XmlXl.getTokenSet(tokenSet));
      // arrange token descriptors of this set as an ordered list
      TokenDescriptor[] tokenDescriptors = expectedTokenset
        .map(tokenDescriptorByName::get)  // map token name to token descriptor
        .sorted()                         // descending sort enforces "longest token first" for literals
        .toArray(TokenDescriptor[]::new);
      lexers[tokenSet] = new ContextSpecificLexer(tokenDescriptors);
    }
  }

  /**
   * This class represents a descriptor for a single token.
   */
  private static class TokenDescriptor implements Comparable<TokenDescriptor> {
    /** The token code. */
    int code;
    /** The regular expression recognizing this token. */
    String regex;
    /** The sort key of this token. A descending sort of literals enforces "longest first". */
    String sortKey;

    /**
     * Constructor.
     * @param name the token name (or token literal)
     * @param code the token code
     * @param regex the regular expression recognizing this token
     */
    TokenDescriptor(String name, int code, String regex) {
      this.code = code;
      if (name.startsWith("'")) {
        // unquote literal
        String literal = name.substring(1, name.length() - 1).replaceAll("''", "'");
        // add pattern quoting
        this.regex = Pattern.quote(literal);
        // lower preference than named tokens
        this.sortKey = " " + literal;
      }
      else {
        this.regex = regex;
        this.sortKey = name;
      }
    }

    @Override
    public int compareTo(TokenDescriptor t) {
      return - sortKey.compareTo(t.sortKey);
    }
  }

  /**
   * This class represents a "context specific" lexer. It has {@link ContextSpecificLexer#pattern},
   * a pattern that is able to recognize exactly the tokens in some token set, which is the set of
   * valid tokens in some parser state. The pattern's capturing groups correspond to these tokens,
   * and array {@link ContextSpecificLexer#tokenDescriptors} enumerates their token descriptors in
   * the same order. The logic in method {@link XmlXlLexer#match(int, XmlXl.Token)} populates these 
   * descriptors after invoking {link {@link Matcher#lookingAt()}.
   */
  private static class ContextSpecificLexer {
    /** The pattern with one capturing group per token known by this lexer. */
    Pattern pattern;
    /** The descriptors of tokens known by this lexer, in the same order as in {@link #pattern}. */
    TokenDescriptor[] tokenDescriptors;

    /**
     * Constructor.
     * @param tokenDecriptors ordered descriptors of tokens
     */
    ContextSpecificLexer(TokenDescriptor[] tokenDescriptors) {
      this.tokenDescriptors = tokenDescriptors;
      // assemble combined regex with capturing groups in the order of the token descriptors
      String regex = "";
      for (TokenDescriptor td : tokenDescriptors) {
        regex += (regex.isEmpty() ? "" : "|") + cLP + td.regex + cRP;
      }
      this.pattern = Pattern.compile(regex);
    }
  }
}