package de.bottlecaps.rex.test.allplatforms;

import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestGLREmptyStackAmbiguity extends RExExecutionWithMessage
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
      "{xxxx}",
      new NamedFile(
        "S.ebnf",
        "S ::= A 'x'",
        "    | B 'x' 'x' 'x'",
        "    | C 'x' 'x' 'x'",
        "A ::= 'x'",
        "B ::= 'x'",
        "C ::= 'x'"
      )
    );
    messages = Arrays.asList
    (
        "ambiguous input",
        "at line 1, column 1:",
        "...xxxx..."
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><AMBIGUOUS><ALTERNATIVE><S><C><UNAMBIGUOUS>x</UNAMBIGUOUS></C><TOKEN>x</TOKEN><TOKEN>x</TOKEN><TOKEN>x</TOKEN></S></ALTERNATIVE><ALTERNATIVE><S><B><UNAMBIGUOUS>x</UNAMBIGUOUS></B><TOKEN>x</TOKEN><TOKEN>x</TOKEN><TOKEN>x</TOKEN></S></ALTERNATIVE></AMBIGUOUS>\n";
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
