package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestLALRNoTree extends RExExecutionWithResult
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-lalr 1",
      "{4+4}",
      new NamedFile("expr.ebnf")
    );
    expectedStdout = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  }
}
