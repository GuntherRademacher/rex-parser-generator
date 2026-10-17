package de.bottlecaps.rex.test.allplatforms;

import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

/**
 * Ambiguity handling without option -ambiguity: the default is to reject the input.
 * The grammar is shared with {@link TestGLRAmbiguityMinimal} and
 * {@link TestGLRAmbiguityMinimalCodeAnnotations}.
 */
public class TestGLRAmbiguityDefault extends RExExecutionWithMessage
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
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
    messages = Arrays.asList
    (
        "ambiguous input",
        "at line 1, column 2:",
        "...x..."
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><AMBIGUOUS><ALTERNATIVE><X><C><D><UNAMBIGUOUS>x</UNAMBIGUOUS></D></C></X><TOKEN>x</TOKEN></ALTERNATIVE><ALTERNATIVE><X><B><UNAMBIGUOUS>x</UNAMBIGUOUS></B></X><TOKEN>x</TOKEN></ALTERNATIVE></AMBIGUOUS>\n";
  }
}
