package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

/**
 * Option -ambiguity minimal: both X nodes are ambiguous between B and C, and the alternative
 * with fewer events, which is B, must be selected for each of them.
 */
public class TestGLRAmbiguityMinimal extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree -ambiguity minimal",
      "{xx}",
      new NamedFile(
        "S.ebnf",
        "S ::= X X",
        "X ::= B | C",
        "B ::= 'x'",
        "C ::= D",
        "D ::= 'x'"
      )
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><X><B><TOKEN>x</TOKEN></B></X><X><B><TOKEN>x</TOKEN></B></X></S>";
  }
}
