package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

/**
 * Option -ambiguity minimal, for a grammar with active code annotations. The selection must be
 * the same as without code annotations, see {@link TestGLRAmbiguityMinimal}: all nonterminal
 * reductions must be counted, whether or not they are mapped to custom code.
 * <p>
 * The annotations are no-ops, and they are only active for the target language that is selected
 * by option -a. The Saxon-HE, Saxon-EE and BaseX extension function tests use no annotation language.
 */
public class TestGLRAmbiguityMinimalCodeAnnotations extends RExExecutionWithResult
{
  private String baseOptions;

  @BeforeEach
  public void before()
  {
    baseOptions = "-glalr 1 -tree -ambiguity minimal";
    init
    (
      baseOptions,
      "{xx}",
      new NamedFile(
        "S.ebnf",
        "S ::= X X                    <?java ;?>",
        "                             <?cpp ;?>",
        "                             <?csharp ;?>",
        "                             <?node ;?>",
        "                             <?typescript ;?>",
        "                             <?haxe {}?>",
        "                             <?go _ = 0?>",
        "                             <?python pass?>",
        "                             <?scala ()?>",
        "                             <?xquery let $state := ($state, ())?>",
        "                             <?xslt <xsl:variable name=\"state\" select=\"$state\"/>?>",
        "X ::= B | C",
        "B ::= 'x'",
        "C ::= D",
        "D ::= 'x'"
      )
    );
    expectedStdout =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><X><B><TOKEN>x</TOKEN></B></X><X><B><TOKEN>x</TOKEN></B></X></S>";
  }

  private void withAnnotations(String language, Runnable test)
  {
    rexOptions = baseOptions + " -a " + language;
    test.run();
  }

  @Test
  @Override
  public void testJava()
  {
    withAnnotations("java", super::testJava);
  }

  @Test
  @Override
  public void testNode()
  {
    withAnnotations("node", super::testNode);
  }

  @Test
  @Override
  public void testScala()
  {
    withAnnotations("scala", super::testScala);
  }

  @Test
  @Override
  public void testCsc()
  {
    withAnnotations("csharp", super::testCsc);
  }

  @Test
  @Override
  public void testMcs()
  {
    withAnnotations("csharp", super::testMcs);
  }

  @Test
  @Override
  public void testCppWchar_t()
  {
    withAnnotations("cpp", super::testCppWchar_t);
  }

  @Test
  @Override
  public void testCppChar()
  {
    withAnnotations("cpp", super::testCppChar);
  }

  @Test
  @Override
  public void testTypescript()
  {
    withAnnotations("typescript", super::testTypescript);
  }

  @Test
  @Override
  public void testHaxe()
  {
    withAnnotations("haxe", super::testHaxe);
  }

  @Test
  @Override
  public void testGo()
  {
    withAnnotations("go", super::testGo);
  }

  @Test
  @Override
  public void testPython()
  {
    withAnnotations("python", super::testPython);
  }

  @Test
  @Override
  public void testXQuerySaxon()
  {
    withAnnotations("xquery", super::testXQuerySaxon);
  }

  @Test
  @Override
  public void testXQueryBaseX()
  {
    withAnnotations("xquery", super::testXQueryBaseX);
  }

  @Test
  @Override
  public void testXsltSaxon()
  {
    withAnnotations("xslt", super::testXsltSaxon);
  }

  @Test
  @Override
  public void testSaxonHE()
  {
    withAnnotations("java", super::testSaxonHE);
  }

  @Test
  @Override
  public void testBaseX()
  {
    withAnnotations("java", super::testBaseX);
  }
}
