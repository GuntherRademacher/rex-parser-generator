package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestGLRLongestAccept extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
      "{xxxx}",
      new NamedFile(
        "S.ebnf",
        "S ::= A 'x'",
        "    | B 'x'",
        "    | C 'x' 'x' 'x'",
        "A ::= 'x'",
        "B ::= 'x'",
        "C ::= 'x'"
      )
    );
    expectedStdout = TREE;
  }

  private static final String TREE = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><C><TOKEN>x</TOKEN></C><TOKEN>x</TOKEN><TOKEN>x</TOKEN><TOKEN>x</TOKEN></S>";
}
