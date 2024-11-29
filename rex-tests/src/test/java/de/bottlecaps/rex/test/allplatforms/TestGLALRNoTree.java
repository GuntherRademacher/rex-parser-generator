package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestGLALRNoTree extends RExExecutionWithResult
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-glalr 1",
      "{4+4}",
      new NamedFile("exprGLR.ebnf")
    );
    expectedStdout = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  }
}
