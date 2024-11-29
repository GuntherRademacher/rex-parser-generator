package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestGLRInitialFailure extends RExExecutionWithMessage
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-glr 1",
      "{42}",
      Arrays.asList
      (
        "lexical analysis failed",
        "while expecting [Whitespace, Name, '<?']",
        "at line 1, column 1:",
        "...42..."
      ),
      new NamedFile(Paths.get("../rex/src/parser", "EbnfParser.ebnf"))
    );
  }
}
