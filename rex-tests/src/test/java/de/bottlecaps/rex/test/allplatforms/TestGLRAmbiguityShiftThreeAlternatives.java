package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

/**
 * Option -ambiguity shift, with three alternatives: "k()()" can be parsed with a shift of "(" as
 * the start of the argument of "k", or by reducing "k" to a name in two different ways. The conflict
 * is encoded with nested forks in the XQuery and XSLT parsers. The alternative that shifts must
 * still be selected, although it has the most nodes, and would not be chosen with -ambiguity
 * minimal.
 */
public class TestGLRAmbiguityShiftThreeAlternatives extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree -ambiguity shift",
      "{k()()}",
      new NamedFile(
        "S.ebnf",
        "S ::= E EOF",
        "E ::= U | F | G",
        "U ::= 'k' Paren '(' ')'",
        "Paren ::= Inner",
        "Inner ::= Core",
        "Core ::= '(' ')'",
        "F ::= Name1 '(' ')' ( '(' ')' )*",
        "G ::= Name2 '(' ')' ( '(' ')' )*",
        "Name1 ::= 'k'",
        "Name2 ::= 'k'",
        "<?TOKENS?>",
        "EOF ::= $"
      )
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><E><U><TOKEN>k</TOKEN>"
        + "<Paren><Inner><Core><TOKEN>(</TOKEN><TOKEN>)</TOKEN></Core></Inner></Paren>"
        + "<TOKEN>(</TOKEN><TOKEN>)</TOKEN></U></E><EOF/></S>";
  }
}
