package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.AbstractSinglePlatformTest;
import de.bottlecaps.rex.test.base.Pass;

/**
 * Event sequence of a Java parser generated with -ambiguity minimal, as seen by a recording
 * BottomUpEventHandler. The ranges passed to ambiguity() are an over-approximation: they may start
 * before the ambiguous part, and they include the lookahead token read when the alternatives were
 * merged. The notification follows the events of the selected alternative.
 */
public class TestGLRAmbiguityNotification extends AbstractSinglePlatformTest
{
  private static final String[] AMBIGUOUS_X =
  {
    "X ::= B | C",
    "B ::= 'x'",
    "C ::= D",
    "D ::= 'x'",
    "<?TOKENS?>",
    "EOF ::= $"
  };

  private static final NamedFile RECORDER = new NamedFile
  (
    "Recorder.java",
    "public class Recorder",
    "{",
    "  public static void main(String[] args)",
    "  {",
    "    S.BottomUpEventHandler handler = new S.BottomUpEventHandler()",
    "    {",
    "      public void reset(CharSequence input) {}",
    "      public void terminal(String name, int begin, int end)",
    "      {",
    "        System.out.println(\"terminal \" + name + \" \" + begin + \" \" + end);",
    "      }",
    "      public void nonterminal(String name, int begin, int end, int count)",
    "      {",
    "        System.out.println(\"nonterminal \" + name + \" \" + begin + \" \" + end + \" \" + count);",
    "      }",
    "      public void ambiguity(int begin, int end)",
    "      {",
    "        System.out.println(\"ambiguity \" + begin + \" \" + end);",
    "      }",
    "    };",
    "    new S(args[0], handler).parse_S();",
    "  }",
    "}"
  );

  /** The alternatives are merged only after the lookahead 'b' has been read. */
  @Test
  public void testAmbiguityAfterLookahead()
  {
    check("S ::= 'a' X 'b' 'c' EOF", "axbc",
        "terminal 'a' 0 1",
        "terminal 'x' 1 2",
        "nonterminal B 1 2 1",
        "nonterminal X 1 2 1",
        "terminal 'b' 2 3",
        "ambiguity 1 3",
        "terminal 'c' 3 4",
        "terminal EOF 4 4",
        "nonterminal S 0 4 5");
  }

  /** The alternatives are only merged when the input is accepted: the range is not narrowed down. */
  @Test
  public void testAmbiguityAtEndOfInput()
  {
    check("S ::= 'a' X EOF", "ax",
        "terminal 'a' 0 1",
        "terminal 'x' 1 2",
        "nonterminal B 1 2 1",
        "nonterminal X 1 2 1",
        "terminal EOF 2 2",
        "nonterminal S 0 2 3",
        "ambiguity 0 2");
  }

  @Test
  public void testTwoAmbiguities()
  {
    check("S ::= 'a' X 'b' X 'c' 'd' EOF", "axbxcd",
        "terminal 'a' 0 1",
        "terminal 'x' 1 2",
        "nonterminal B 1 2 1",
        "nonterminal X 1 2 1",
        "terminal 'b' 2 3",
        "ambiguity 1 3",
        "terminal 'x' 3 4",
        "nonterminal B 3 4 1",
        "nonterminal X 3 4 1",
        "terminal 'c' 4 5",
        "ambiguity 3 5",
        "terminal 'd' 5 6",
        "terminal EOF 6 6",
        "nonterminal S 0 6 7");
  }

  /** The input does not use the ambiguous alternatives: no notification. */
  @Test
  public void testNoAmbiguity()
  {
    check("S ::= 'a' ( X | 'z' ) 'b' 'c' EOF", "azbc",
        "terminal 'a' 0 1",
        "terminal 'z' 1 2",
        "terminal 'b' 2 3",
        "terminal 'c' 3 4",
        "terminal EOF 4 4",
        "nonterminal S 0 4 5");
  }

  private void check(String startRule, String input, String... expectedEvents)
  {
    Pass.expectPass(() ->
    {
      String[] lines = new String[AMBIGUOUS_X.length + 1];
      lines[0] = startRule;
      System.arraycopy(AMBIGUOUS_X, 0, lines, 1, AMBIGUOUS_X.length);
      NamedFile grammar = new NamedFile("S.ebnf", lines);

      String commandLine = commandLine("-java", "-glalr 1 -tree -ambiguity minimal", grammar);
      Runner runner = new Runner();
      if (0 != runner.run(REX, commandLine, grammar, RECORDER))
        throw new RuntimeException(runner.summary("rex generation failed"));
      assertTrue(runner.getStdout().contains("LALR(1)-conflict handled by GLALR processing"), runner.summary());

      String className = className(runner.getArgs(), JAVAC);
      runner.compile(className + ".java");
      runner.expectSuccess("Java compilation", JAVAC, "-encoding UTF-8 Recorder.java");

      assertEquals(0, runner.run(JAVA, "Recorder " + input), runner.summary());
      assertEquals(String.join("\n", expectedEvents),
          runner.getStdout().replace("\r\n", "\n").trim(), runner.summary());
      Pass.passNormally(runner);
    });
  }
}
