package de.bottlecaps.rex.test.allplatforms;

import java.nio.file.Paths;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestIndentedTree extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree",
      "-i simple.ebnf",
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

  @Test
  @Override
  public void testSaxonEE()
  {
  }

  @Test
  @Override
  public void testSaxonHE()
  {
  }

  @Test
  @Override
  public void testBaseX()
  {
  }

  //  private static final String TREE = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Grammar><Prolog/><SyntaxDefinition><SyntaxProduction><Name>S</Name> <TOKEN>::=</TOKEN> <SyntaxChoice><SyntaxSequence><SyntaxItem><SyntaxPrimary><NameOrString><Name>A</Name></NameOrString></SyntaxPrimary></SyntaxItem></SyntaxSequence></SyntaxChoice></SyntaxProduction>\n<SyntaxProduction><Name>A</Name> <TOKEN>::=</TOKEN> <SyntaxChoice><SyntaxSequence><SyntaxItem><SyntaxPrimary><NameOrString><StringLiteral>'x'</StringLiteral></NameOrString></SyntaxPrimary></SyntaxItem> <SyntaxItem><SyntaxPrimary><ProcessingInstruction><TOKEN>&lt;?</TOKEN><Name>a</Name><Space> </Space><DirPIContents>/*A*/</DirPIContents><TOKEN>?&gt;</TOKEN></ProcessingInstruction></SyntaxPrimary></SyntaxItem></SyntaxSequence></SyntaxChoice></SyntaxProduction></SyntaxDefinition><EOF/></Grammar>";
  private static final String TREE =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
    "<Grammar>\n" +
    "  <Prolog/>\n" +
    "  <SyntaxDefinition>\n" +
    "    <SyntaxProduction>\n" +
    "      <Name>S</Name> \n" +
    "      <TOKEN>::=</TOKEN> \n" +
    "      <SyntaxChoice>\n" +
    "        <SyntaxSequence>\n" +
    "          <SyntaxItem>\n" +
    "            <SyntaxPrimary>\n" +
    "              <NameOrString>\n" +
    "                <Name>A</Name>\n" +
    "              </NameOrString>\n" +
    "            </SyntaxPrimary>\n" +
    "          </SyntaxItem>\n" +
    "        </SyntaxSequence>\n" +
    "      </SyntaxChoice>\n" +
    "    </SyntaxProduction>\n" +
    "\n" +
    "    <SyntaxProduction>\n" +
    "      <Name>A</Name> \n" +
    "      <TOKEN>::=</TOKEN> \n" +
    "      <SyntaxChoice>\n" +
    "        <SyntaxSequence>\n" +
    "          <SyntaxItem>\n" +
    "            <SyntaxPrimary>\n" +
    "              <NameOrString>\n" +
    "                <StringLiteral>'x'</StringLiteral>\n" +
    "              </NameOrString>\n" +
    "            </SyntaxPrimary>\n" +
    "          </SyntaxItem> \n" +
    "          <SyntaxItem>\n" +
    "            <SyntaxPrimary>\n" +
    "              <ProcessingInstruction>\n" +
    "                <TOKEN>&lt;?</TOKEN>\n" +
    "                <Name>a</Name>\n" +
    "                <Space> </Space>\n" +
    "                <DirPIContents>/*A*/</DirPIContents>\n" +
    "                <TOKEN>?&gt;</TOKEN>\n" +
    "              </ProcessingInstruction>\n" +
    "            </SyntaxPrimary>\n" +
    "          </SyntaxItem>\n" +
    "        </SyntaxSequence>\n" +
    "      </SyntaxChoice>\n" +
    "    </SyntaxProduction>\n" +
    "  </SyntaxDefinition>\n" +
    "  <EOF/>\n" +
    "</Grammar>";
}
