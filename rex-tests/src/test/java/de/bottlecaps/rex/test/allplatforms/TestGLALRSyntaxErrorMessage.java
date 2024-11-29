package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestGLALRSyntaxErrorMessage extends RExExecutionWithMessage
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-glalr 1",
      "{4+4)}",
      new NamedFile("exprGLR.ebnf")
    );
    messages = Arrays.asList(
      "syntax error, found ')'",
      "while expecting [ws, '$']",
      "at line 1, column 4:",
      "...)...");
  }
}
