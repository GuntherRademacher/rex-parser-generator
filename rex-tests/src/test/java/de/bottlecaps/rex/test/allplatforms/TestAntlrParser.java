package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestAntlrParser extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-backtrack -ll 2 -tree",
      "antlr.g",
      new NamedFile("input/antlr.ebnf"),
      new NamedFile("antlr.g")
    );
    expectedStdout = new NamedFile("antlr.xml").getContent();
  }
}
