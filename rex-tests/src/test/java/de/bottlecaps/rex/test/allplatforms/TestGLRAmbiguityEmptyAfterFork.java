package de.bottlecaps.rex.test.allplatforms;

import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

/**
 * Ambiguity with an empty production reduced after the fork. Although it is located at the fork
 * position in the input, it is not shared, and must be reported as "E", not as unambiguous.
 */
public class TestGLRAmbiguityEmptyAfterFork extends RExExecutionWithMessage
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
      "{abcf}",
      new NamedFile(
        "S.ebnf",
        "S ::= 'a' X 'f'",
        "X ::= P E 'c' | Q E 'c'",
        "P ::= 'b'",
        "Q ::= 'b'",
        "E ::="
      )
    );
    messages = Arrays.asList
    (
        "ambiguous input",
        "at line 1, column 2:",
        "...bcf..."
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><AMBIGUOUS><ALTERNATIVE><X><Q><UNAMBIGUOUS>b</UNAMBIGUOUS></Q><E/><TOKEN>c</TOKEN></X></ALTERNATIVE><ALTERNATIVE><X><P><UNAMBIGUOUS>b</UNAMBIGUOUS></P><E/><TOKEN>c</TOKEN></X></ALTERNATIVE></AMBIGUOUS>\n";
  }
}
