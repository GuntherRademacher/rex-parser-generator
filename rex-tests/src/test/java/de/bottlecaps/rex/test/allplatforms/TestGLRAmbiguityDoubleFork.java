package de.bottlecaps.rex.test.allplatforms;

import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

/**
 * Ambiguity between threads that both forked again after their common fork. The shared part is
 * determined by the first fork, so the tokens "c" and "d" must not be reported as unambiguous.
 */
public class TestGLRAmbiguityDoubleFork extends RExExecutionWithMessage
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
      "{abcdef}",
      new NamedFile(
        "S.ebnf",
        "S ::= 'a' X 'f'",
        "X ::= P 'c' R | Q 'c' T",
        "P ::= 'b'",
        "Q ::= 'b'",
        "R ::= U 'e' | V 'e' 'h'",
        "T ::= W 'e' | Z 'e' 'i'",
        "U ::= 'd'",
        "V ::= 'd'",
        "W ::= 'd'",
        "Z ::= 'd'"
      )
    );
    messages = Arrays.asList
    (
        "ambiguous input",
        "at line 1, column 2:",
        "...bcdef..."
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><AMBIGUOUS><ALTERNATIVE><X><Q><UNAMBIGUOUS>b</UNAMBIGUOUS></Q><TOKEN>c</TOKEN><T><W><TOKEN>d</TOKEN></W><TOKEN>e</TOKEN></T></X></ALTERNATIVE><ALTERNATIVE><X><P><UNAMBIGUOUS>b</UNAMBIGUOUS></P><TOKEN>c</TOKEN><R><U><TOKEN>d</TOKEN></U><TOKEN>e</TOKEN></R></X></ALTERNATIVE></AMBIGUOUS>\n";
  }
}
