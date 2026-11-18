package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestGLALR2Comments extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 2 -tree",
      "input.txt",
      new NamedFile
      (
        "simple.ebnf",
        "Start ::= A 'x' 'y' EOF | B 'x' 'z' EOF | C 'q' 'x' 'y' 'w' EOF | D 'q' 'x' 'y' 'v' EOF",
        "A ::= 'a'",
        "B ::= 'a'",
        "C ::= 'c'",
        "D ::= 'c'",
        "Whitespace ::= WS | Comment /* ws: definition */",
        "Comment ::= '(:' ( CommentContents | Comment )* ':)' /* ws: explicit */",
        "<?TOKENS?>",
        "WS ::= ' '+",
        "CommentContents ::= [0-9]+",
        "EOF ::= $"
      ),
      new NamedFile
      (
        "input.txt",
        "cq(:1:)xy(:2(:3:):)v"
      )
    );
    expectedStdout = TREE;
  }

  private static final String TREE = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Start><D><TOKEN>c</TOKEN></D><TOKEN>q</TOKEN>(:1:)<TOKEN>x</TOKEN><TOKEN>y</TOKEN>(:2(:3:):)<TOKEN>v</TOKEN><EOF/></Start>";
}
