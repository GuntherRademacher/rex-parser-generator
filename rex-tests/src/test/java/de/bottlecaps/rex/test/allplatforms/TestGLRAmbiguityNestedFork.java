package de.bottlecaps.rex.test.allplatforms;

import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

/**
 * Ambiguity between threads that were forked at different input positions: the thread parsing
 * "Q c R" forks again, for R, after the fork for P/Q, while the thread parsing "P c d" does not.
 * The shared part is determined by the earlier fork, so the tokens "c" and "d" must not be
 * reported as unambiguous.
 */
public class TestGLRAmbiguityNestedFork extends RExExecutionWithMessage
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
      "{abcdf}",
      new NamedFile(
        "S.ebnf",
        "S ::= 'a' X 'f'",
        "X ::= P 'c' 'd' | Q 'c' R",
        "P ::= 'b'",
        "Q ::= 'b'",
        "R ::= U | V",
        "U ::= 'd'",
        "V ::= 'd'"
      )
    );
    messages = Arrays.asList
    (
        "ambiguous input",
        "at line 1, column 2:",
        "...bcdf..."
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><AMBIGUOUS><ALTERNATIVE><X><Q><UNAMBIGUOUS>b</UNAMBIGUOUS></Q><TOKEN>c</TOKEN><R><V><TOKEN>d</TOKEN></V></R></X></ALTERNATIVE><ALTERNATIVE><X><P><UNAMBIGUOUS>b</UNAMBIGUOUS></P><TOKEN>c</TOKEN><TOKEN>d</TOKEN></X></ALTERNATIVE></AMBIGUOUS>\n";
  }
}
