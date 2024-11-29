package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestGLRLexicalErrorMessage extends RExExecutionWithMessage
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-glr 1",
      "{4++4}",
      Arrays.asList
      (
        "lexical analysis failed",
        "while expecting [ws, integer, '(']",
        "at line 1, column 3:",
        "...+4..."
      ),
      new NamedFile("exprGLR.ebnf")
    );
  }
}
