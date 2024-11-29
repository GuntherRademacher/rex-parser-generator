package de.bottlecaps.rex.test.allplatforms;

import java.nio.file.Paths;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestGLRTree extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
      "simple.ebnf",
      new NamedFile(Paths.get("../rex/src/parser", "EbnfParser.ebnf")),
      new NamedFile
      (
        "simple.ebnf",
        "S ::= A",
        "A ::= 'x' <?a /*A*/?>"
      )
    );
    expectedStdout = TREE;
  }

  private static final String TREE = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Grammar><Prolog/><SyntaxDefinition><SyntaxProduction><Name>S</Name> <TOKEN>::=</TOKEN> <SyntaxChoice><SyntaxSequence><SyntaxItem><SyntaxPrimary><NameOrString><Name>A</Name></NameOrString></SyntaxPrimary></SyntaxItem></SyntaxSequence></SyntaxChoice></SyntaxProduction>\n<SyntaxProduction><Name>A</Name> <TOKEN>::=</TOKEN> <SyntaxChoice><SyntaxSequence><SyntaxItem><SyntaxPrimary><NameOrString><StringLiteral>'x'</StringLiteral></NameOrString></SyntaxPrimary></SyntaxItem> <SyntaxItem><SyntaxPrimary><ProcessingInstruction><TOKEN>&lt;?</TOKEN><Name>a</Name><Space> </Space><DirPIContents>/*A*/</DirPIContents><TOKEN>?&gt;</TOKEN></ProcessingInstruction></SyntaxPrimary></SyntaxItem></SyntaxSequence></SyntaxChoice></SyntaxProduction></SyntaxDefinition><EOF/></Grammar>";
}
