package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.function.Function;

import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.AbstractSinglePlatformTest;
import de.bottlecaps.rex.test.base.Pass;

/**
 * Option -ambiguity shift: at the first point where the alternatives of an ambiguity diverge, the
 * one that shifts a terminal is preferred over the one that reduces. In both grammars this is the
 * pattern of a keyword that can be a name, as in XQuery's "element update {()}", which is a
 * constructor named "update", or an expression "element" updated by "{()}". Input that is
 * only valid with the reduction must still be accepted. In both grammars, the preferred
 * alternative has more nodes, so it would not be selected with -ambiguity minimal.
 */
public class TestGLRAmbiguityShift extends AbstractSinglePlatformTest
{
  private static final String OPTIONS = "-glalr 1 -tree -ambiguity shift";

  private static final String XML = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

  /** 'element' is a name, or starts a constructor. */
  private static final NamedFile CONSTRUCTOR = new NamedFile
  (
    "S.ebnf",
    "S ::= E EOF",
    "E ::= P ( 'update' '{' E? '}' )*",
    "P ::= C | Name",
    "C ::= 'element' Name '{' E? '}'",
    "Name ::= 'element' | 'update' | 'x'",
    "Whitespace ::= Blank",
    "          /* ws: definition */",
    "<?TOKENS?>",
    "EOF ::= $",
    "Blank ::= ' '+"
  );

  /** 'updating' is a function name, or starts an updating function call. */
  private static final NamedFile CALL = new NamedFile
  (
    "S.ebnf",
    "S ::= E EOF",
    "E ::= U | F",
    "U ::= 'updating' Paren '(' ')'",
    "Paren ::= Inner",
    "Inner ::= Core",
    "Core ::= '(' ')'",
    "F ::= Call ( '(' ')' )*",
    "Call ::= Name '(' ')'",
    "Name ::= 'updating' | 'x'",
    "<?TOKENS?>",
    "EOF ::= $"
  );

  private static final String CONSTRUCTOR_RESULT = XML
      + "<S><E><P><C><TOKEN>element</TOKEN> <Name><TOKEN>update</TOKEN></Name> <TOKEN>{</TOKEN><TOKEN>}</TOKEN></C></P></E><EOF/></S>";

  private static final String UPDATING_CALL_RESULT = XML
      + "<S><E><U><TOKEN>updating</TOKEN><Paren><Inner><Core><TOKEN>(</TOKEN><TOKEN>)</TOKEN></Core></Inner></Paren>"
      + "<TOKEN>(</TOKEN><TOKEN>)</TOKEN></U></E><EOF/></S>";

  private static final String PLAIN_CALL_RESULT = XML
      + "<S><E><F><Call><Name><TOKEN>updating</TOKEN></Name><TOKEN>(</TOKEN><TOKEN>)</TOKEN></Call></F></E><EOF/></S>";

  @Test public void testJavaConstructor() {check(this::java, CONSTRUCTOR, "\"{element update {}}\"", CONSTRUCTOR_RESULT);}
  @Test public void testNodeConstructor() {check(this::node, CONSTRUCTOR, "\"{element update {}}\"", CONSTRUCTOR_RESULT);}
  @Test public void testJavaUpdatingCall() {check(this::java, CALL, "{updating()()}", UPDATING_CALL_RESULT);}
  @Test public void testNodeUpdatingCall() {check(this::node, CALL, "{updating()()}", UPDATING_CALL_RESULT);}

  /** Only valid when 'updating' is reduced to a name: the language must not shrink. */
  @Test public void testJavaPlainCall() {check(this::java, CALL, "{updating()}", PLAIN_CALL_RESULT);}
  @Test public void testNodePlainCall() {check(this::node, CALL, "{updating()}", PLAIN_CALL_RESULT);}

  /**
   * The resolution must not depend on whether an event handler is passed to the parser: with
   * action annotations, the selected alternative is the one whose action is executed.
   */
  private static final NamedFile CALL_WITH_ACTIONS = new NamedFile
  (
    "S.ebnf",
    "S ::= E EOF",
    "E ::= U | F",
    "U ::= 'updating' Paren '(' ')' <?java System.out.println(\"U\");?> <?js console.log('U');?>",
    "Paren ::= Inner",
    "Inner ::= Core",
    "Core ::= '(' ')'",
    "F ::= Call ( '(' ')' )* <?java System.out.println(\"F\");?> <?js console.log('F');?>",
    "Call ::= Name '(' ')'",
    "Name ::= 'updating' | 'x'",
    "<?TOKENS?>",
    "EOF ::= $"
  );

  private static final NamedFile JAVA_WITHOUT_HANDLER = new NamedFile
  (
    "NoHandler.java",
    "public class NoHandler",
    "{",
    "  public static void main(String[] args)",
    "  {",
    "    new S(args[0], null).parse_S();",
    "  }",
    "}"
  );

  private static final NamedFile NODE_WITHOUT_HANDLER = new NamedFile
  (
    "nohandler.js",
    "const fs = require('fs');",
    "const S = new Function(fs.readFileSync('S.js', 'utf8') + '; return S;')();",
    "new S(process.argv[2], null).parse_S();"
  );

  @Test
  public void testJavaWithoutHandler()
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      String commandLine = commandLine("-java", OPTIONS + " -a java", CALL_WITH_ACTIONS);
      if (0 != runner.run(REX, commandLine, CALL_WITH_ACTIONS, JAVA_WITHOUT_HANDLER))
        throw new RuntimeException(runner.summary("rex generation failed"));
      runner.compile("S.java");
      runner.expectSuccess("Java compilation", JAVAC, "-encoding UTF-8 NoHandler.java");
      assertEquals(0, runner.run(JAVA, "NoHandler updating()()"), runner.summary());
      assertEquals("U", runner.getStdout().trim(), runner.summary());
      assertEquals(0, runner.run(JAVA, "NoHandler updating()"), runner.summary());
      assertEquals("F", runner.getStdout().trim(), runner.summary());
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testNodeWithoutHandler()
  {
    Pass.expectPass(() ->
    {
      Runner runner = new Runner();
      String commandLine = commandLine("-javascript", OPTIONS + " -a js", CALL_WITH_ACTIONS);
      if (0 != runner.run(REX, commandLine, CALL_WITH_ACTIONS, NODE_WITHOUT_HANDLER))
        throw new RuntimeException(runner.summary("rex generation failed"));
      Pass.passEarlyIfPossible(runner, "S.js");
      assertEquals(0, runner.run(NODE, "nohandler.js updating()()"), runner.summary());
      assertEquals("U", runner.getStdout().trim(), runner.summary());
      assertEquals(0, runner.run(NODE, "nohandler.js updating()"), runner.summary());
      assertEquals("F", runner.getStdout().trim(), runner.summary());
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testRequiresTree()
  {
    expectRexError("-glalr 1 -ambiguity shift -java", "missing option: -ambiguity shift also requires -tree");
  }

  private Runner java(String runtimeOptions)
  {
    return runJava(OPTIONS, runtimeOptions, grammar);
  }

  private Runner node(String runtimeOptions)
  {
    return runNode(OPTIONS, runtimeOptions, grammar);
  }

  private NamedFile grammar;

  private void check(Function<String, Runner> runner, NamedFile grammar, String input, String expected)
  {
    this.grammar = grammar;
    Pass.expectPass(() ->
    {
      Runner r = runner.apply(input);
      assertEquals(0, r.getExitCode(), r.summary());
      assertEquals(expected, r.getStdout().replace("\r\n", "\n").trim(), r.summary());
      Pass.passNormally(r);
    });
  }

  private void expectRexError(String options, String message)
  {
    Runner runner = new Runner();
    String commandLine = commandLine("", options, CALL);
    assertNotEquals(0, runner.run(REX, commandLine, CALL), runner.summary());
    assertTrue(runner.getStdout().contains(message), runner.summary());
    runner.cleanup();
  }
}
