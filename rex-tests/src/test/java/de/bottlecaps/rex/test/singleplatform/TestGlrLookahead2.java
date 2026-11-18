package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

/**
 * Tests for XQuery and XSLT code generation with GLR parsing and lookahead
 * of more than one token, where the lookahead and predict functions must
 * all be called with the parsing thread id.
 */
public class TestGlrLookahead2 extends RExRunner
{
  // lookahead 2 resolves the reduce/reduce conflict for 'b', while E is ambiguous
  private static NamedFile grammar()
  {
    return new NamedFile(
      "Lookahead2.ebnf",
      "S ::= ( B 'x' 'y' | C 'x' 'z' | E ) EOF",
      "B ::= 'b'",
      "C ::= 'b'",
      "E ::= E '+' E | 'a'",
      "<?TOKENS?>",
      "EOF ::= $");
  }

  @ParameterizedTest
  @ValueSource(strings = {
    "-xquery -glalr 2",
    "-xquery -glalr 2 -ambiguity shift -tree",
    "-xquery -glr 2",
    "-xslt -glalr 2",
    "-xslt -glalr 2 -ambiguity shift -tree",
    "-xslt -glr 2",
  })
  public void testGlrLookahead2(String options)
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, options + " Lookahead2.ebnf", grammar()), runner.summary());
      runner.compile("Lookahead2" + (options.startsWith("-xslt") ? ".xslt" : ".xquery"));
      Pass.passNormally(runner);
    });
  }
}
