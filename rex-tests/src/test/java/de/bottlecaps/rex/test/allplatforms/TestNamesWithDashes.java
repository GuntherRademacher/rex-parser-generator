package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestNamesWithDashes extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-ll 1 -tree",
      "{x-x}",
      new NamedFile("X-X.ebnf", "X-X ::= 'x-x'")
    );
    expectedStdout = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><X-X><TOKEN>x-x</TOKEN></X-X>";
  }
}
