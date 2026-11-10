package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

/**
 * Tests for Java code generation with option -nolexer in combination with
 * GLR parsing, where the generated parser must hold the external lexer
 * in a place that is accessible to the parsing threads.
 */
public class TestNoLexerGlr extends RExRunner
{
  private static NamedFile grammar()
  {
    return new NamedFile(
      "NoLexerGlr.ebnf",
      "S ::= E EOF",
      "E ::= E '+' E | 'a'");
  }

  @ParameterizedTest
  @ValueSource(strings = {
    "-glr 1",
    "-glr 1 -tree",
    "-glr 1 -ambiguity minimal",
    "-glalr 1",
    "-glalr 1 -tree",
  })
  public void testNoLexerGlr(String options)
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-java -nolexer " + options + " NoLexerGlr.ebnf", grammar()), runner.summary());
      runner.compile("NoLexerGlr.java");
      Pass.passNormally(runner);
    });
  }
}
