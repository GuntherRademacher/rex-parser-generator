package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

/**
 * Option -ambiguity shift: "updating()()" is either an updating function call, or the call of a
 * function "updating" with a postfix argument list. At the point where the two alternatives
 * diverge, the first one shifts a terminal, and the second one reduces. It is selected, although
 * it has more nodes, and would not be chosen with -ambiguity minimal.
 */
public class TestGLRAmbiguityShiftAllPlatforms extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree -ambiguity shift",
      "{updating()()}",
      new NamedFile(
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
      )
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><E><U><TOKEN>updating</TOKEN>"
        + "<Paren><Inner><Core><TOKEN>(</TOKEN><TOKEN>)</TOKEN></Core></Inner></Paren>"
        + "<TOKEN>(</TOKEN><TOKEN>)</TOKEN></U></E><EOF/></S>";
  }
}
