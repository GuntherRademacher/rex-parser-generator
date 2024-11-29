package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestLALRSyntaxErrorMessage extends RExExecutionWithMessage
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-lalr 1",
      "{4+4)}",
      new NamedFile("expr.ebnf")
    );
    messages = Arrays.asList(
      "syntax error, found ')'",
      "while expecting [ws, EOF]",
      "at line 1, column 4:",
      "...)...");
  }
}
