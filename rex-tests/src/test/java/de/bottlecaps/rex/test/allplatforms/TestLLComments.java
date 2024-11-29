package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestLLComments extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-tree",
      "input.txt",
      new NamedFile
      (
        "simple.ebnf",
        "S ::= A EOF",
        "A ::= 'x' 'y'",
        "Comment ::= '/*' ( CommentContent | Comment )* '*/' /*ws:definition*/",
        "<?TOKENS?>",
        "CommentContent ::= .+ - ( .* ( '/*' | '*/' ) .* )",
        "EOF ::= $"
      ),
      new NamedFile
      (
        "input.txt",
        "/*/**/*/x/*/**/*/y/*/**/*/"
      )
    );
    expectedStdout = TREE;
  }

  private static final String TREE = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S>/*/**/*/<A><TOKEN>x</TOKEN>/*/**/*/<TOKEN>y</TOKEN></A>/*/**/*/<EOF/></S>";
}
