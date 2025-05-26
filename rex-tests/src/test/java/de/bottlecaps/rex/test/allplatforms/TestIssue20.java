package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestIssue20 extends RExExecutionWithMessage
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "",
      "{-}",
      Arrays.asList
      (
        "lexical analysis failed",
        "while expecting ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']",
        "at line 1, column 1:",
        "...-..."
      ),
      new NamedFile
      (
        "issue20.ebnf",
          "S ::= 'A' | 'B' | 'C' | 'D' | 'E'\n"
        + "    | 'F' | 'G' | 'H' | 'I' | 'J'\n"
        + "    | 'K' | 'L' | 'M' | 'N' | 'O'\n"
        + "    | 'P' | 'Q' | 'R' | 'S' | 'T'\n"
        + "    | 'U' | 'V' | 'W' | 'X' | 'Y'\n"
        + "    | 'Z' | '0' | '1' | '2' | '3'\n"
        + "    | '4' | '5' | '6' | '7' | '8'\n"
        + "    | '9'"
      )
    );
  }
}
