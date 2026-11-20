package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

/**
 * Tests for Java code generation with option -nobuilder, which omits the
 * standard tree builders, in particular from standalone interfaces that are
 * shared between parsers.
 */
public class TestNoBuilder extends RExRunner
{
  private static boolean generates(String content, String className)
  {
    return content.contains("class " + className);
  }

  @ParameterizedTest
  @ValueSource(strings = {
    "-ll 1",
    "-lalr 1",
  })
  public void testInterfaceWithoutBuilders(String options)
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-java -tree -nobuilder -interface SharedInterface " + options), runner.summary());
      runner.compile("SharedInterface.java");
      String content = new NamedFile(runner.getPath("SharedInterface.java")).getContent();
      assertFalse(generates(content, "TopDownTreeBuilder"), runner.summary());
      assertFalse(generates(content, "ParseTreeBuilder"), runner.summary());
      assertFalse(generates(content, "Symbol"), runner.summary());
      assertFalse(generates(content, "XmlSerializer"), runner.summary());
      // the top-down event handler is needed by LL parsers, but by an LR parser only if
      // a generated class refers to it
      assertEquals(options.startsWith("-ll"), content.contains("interface EventHandler"), runner.summary());
      assertEquals(options.startsWith("-lalr"), content.contains("interface BottomUpEventHandler"), runner.summary());
      Pass.passNormally(runner);
    });
  }

  @ParameterizedTest
  @ValueSource(strings = {
    "-ll 1",
    "-lalr 1",
  })
  public void testInterfaceWithBuilders(String options)
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-java -tree -interface SharedInterface " + options), runner.summary());
      runner.compile("SharedInterface.java");
      String content = new NamedFile(runner.getPath("SharedInterface.java")).getContent();
      assertTrue(generates(content, options.startsWith("-ll") ? "TopDownTreeBuilder" : "ParseTreeBuilder"), runner.summary());
      assertFalse(generates(content, "XmlSerializer"), runner.summary());
      Pass.passNormally(runner);
    });
  }

  // BaseXFunction in the parser refers to ParseTreeBuilder in the interface
  @Test
  public void testBaseXInterfaceKeepsParseTreeBuilder()
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-java -lalr 1 -tree -nobuilder -basex -interface SharedInterface"), runner.summary());
      String content = new NamedFile(runner.getPath("SharedInterface.java")).getContent();
      assertTrue(generates(content, "ParseTreeBuilder"), runner.summary());
      assertFalse(generates(content, "TopDownTreeBuilder"), runner.summary());
      Pass.passNormally(runner);
    });
  }

  // a GLR interface rejects ambiguity, so ParseException refers to ParseTreeBuilder
  @Test
  public void testGlrInterfaceKeepsParseTreeBuilder()
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-java -tree -nobuilder -interface SharedInterface -glalr 1"), runner.summary());
      runner.compile("SharedInterface.java");
      String content = new NamedFile(runner.getPath("SharedInterface.java")).getContent();
      assertTrue(generates(content, "ParseTreeBuilder"), runner.summary());
      assertFalse(generates(content, "TopDownTreeBuilder"), runner.summary());
      Pass.passNormally(runner);
    });
  }

  private static NamedFile ambiguousGrammar()
  {
    return new NamedFile(
      "AmbiguousSum.ebnf",
      "input ::= expr EOF",
      "expr ::= expr '+' expr | integer",
      "<?TOKENS?>",
      "integer ::= [0-9]+",
      "EOF ::= $");
  }

  // a shared interface must know how the parser resolves ambiguity, because
  // the parser then reports it by BottomUpEventHandler.ambiguity()
  @ParameterizedTest
  @ValueSource(strings = {
    "-glr 1 -ambiguity minimal",
    "-glalr 1 -ambiguity minimal",
    "-glalr 1 -ambiguity shift",
    "-glalr 1 -ambiguity minimal -nobuilder",
    "-glalr 1 -ambiguity shift -nobuilder",
  })
  public void testInterfaceWithAmbiguityResolution(String options)
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-java -tree -interface SharedAmbiguity " + options), runner.summary());
      assertEquals(0, runner.run(REX, "-java -tree -interface SharedAmbiguity " + options + " AmbiguousSum.ebnf", ambiguousGrammar()), runner.summary());
      runner.compile("AmbiguousSum.java");
      Pass.passNormally(runner);
    });
  }
}
