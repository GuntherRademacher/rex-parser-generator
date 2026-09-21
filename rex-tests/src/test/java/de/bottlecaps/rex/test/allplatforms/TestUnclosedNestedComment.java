package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.util.Arrays;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithMessage;

public class TestUnclosedNestedComment extends RExExecutionWithMessage
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "",
      "{abc(:}",
      Arrays.asList
      (
        "lexical analysis failed",
        "while expecting [CommentContents, '(:', ':)']",
        "at line 1, column 6:",
        "......"
      ),
      new NamedFile(
        "S.ebnf",
        "S        ::= Letter+ EOF",
        "Comment  ::= '(:' ( CommentContents | Comment )* ':)'",
        "          /* ws: definition */",
        "",
        "<?TOKENS?>",
        "",
        "Letter   ::= [a-z]",
        "Char     ::= #x9",
        "           | #xA",
        "           | #xD",
        "           | [#x20-#xD7FF]",
        "           | [#xE000-#xFFFD]",
        "           | [#x10000-#x10FFFF]",
        "CommentContents",
        "         ::= ( ( Char+ - ( Char* ( '(:' | ':)' ) Char* ) ) - ( Char* '(' ) ) &':'",
        "           | ( Char+ - ( Char* ( '(:' | ':)' ) Char* ) ) &'('",
        "EOF      ::= $")
    );
  }
}
