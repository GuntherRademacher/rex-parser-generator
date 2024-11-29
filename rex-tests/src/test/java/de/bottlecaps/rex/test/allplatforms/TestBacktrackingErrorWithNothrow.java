package de.bottlecaps.rex.test.allplatforms;

import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestBacktrackingErrorWithNothrow extends RExExecutionWithMessage
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-ll 1 -backtrack -asi -nothrow",
      "\"{const x = 42;}\"",
      Arrays.asList
      (
        "lexical analysis failed",
        "while expecting Identifier",
        "after successfully scanning 5 characters beginning at line 1, column 1:",
        "...const x = 42;..."
      ),
      new NamedFile("EcmaScript.ebnf")
    );
  }

  @Test
  @Override
  public void testXQuerySaxon()
  {
  }

  @Test
  @Override
  public void testXQueryBaseX()
  {
  }

  @Test
  @Override
  public void testXsltSaxon()
  {
  }
}
