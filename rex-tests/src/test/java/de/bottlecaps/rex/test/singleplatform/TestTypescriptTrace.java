package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

/**
 * Tests for TypeScript code generation with option -trace, but without
 * -main. The generated trace code must not depend on anything that is
 * only defined in the main program.
 */
public class TestTypescriptTrace extends RExRunner
{
  private static NamedFile grammar(String expression)
  {
    return new NamedFile(
      "TraceNoMain.ebnf",
      "S ::= E EOF",
      "E ::= " + expression,
      "<?TOKENS?>",
      "EOF ::= $");
  }

  @ParameterizedTest
  @ValueSource(strings = {
    "-ll 1",
    "-ll 1 -tree",
    "-lr 1",
    "-lr 1 -tree",
  })
  public void testTraceWithoutMain(String options)
  {
    compileWithTrace(options, "'a' ('+' 'a')*");
  }

  // an ambiguous grammar, so that the GLR parsing threads are actually generated
  @ParameterizedTest
  @ValueSource(strings = {
    "-glr 1",
    "-glr 1 -tree",
    "-glalr 1",
  })
  public void testGlrTraceWithoutMain(String options)
  {
    compileWithTrace(options, "E '+' E | 'a'");
  }

  private void compileWithTrace(String options, String expression)
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-typescript -trace " + options + " TraceNoMain.ebnf", grammar(expression)), runner.summary());
      runner.compile("TraceNoMain.ts");
      Pass.passNormally(runner);
    });
  }
}
