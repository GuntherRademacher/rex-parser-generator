package de.bottlecaps.rex.test.allplatforms;

import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestGLRAmbiguity extends RExExecutionWithMessage
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
        "X ::= B1 'c'",
        "    | B2 'c' 'd' 'e'",
        "    | B3 'c' 'd' 'e'",
        "B1 ::= 'b'",
        "B2 ::= 'b'",
        "B3 ::= 'b'"
      )
    );
    messages = Arrays.asList
    (
        "ambiguous input",
        "at line 1, column 2:",
        "...bcdef..."
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><AMBIGUOUS><ALTERNATIVE><X><B3><UNAMBIGUOUS>b</UNAMBIGUOUS></B3><TOKEN>c</TOKEN><TOKEN>d</TOKEN><TOKEN>e</TOKEN></X></ALTERNATIVE><ALTERNATIVE><X><B2><UNAMBIGUOUS>b</UNAMBIGUOUS></B2><TOKEN>c</TOKEN><TOKEN>d</TOKEN><TOKEN>e</TOKEN></X></ALTERNATIVE></AMBIGUOUS>\n";
  }

  @Test
  @Override
  public void testBaseX()
  {
    expectedStdout = null;
    super.testBaseX();
  }

  @Test
  @Override
  public void testSaxonHE()
  {
    expectedStdout = null;
    super.testSaxonHE();
  }

//@Test - requires license
  @Override
  public void testSaxonEE()
  {
    expectedStdout = null;
    super.testSaxonEE();
  }
}
