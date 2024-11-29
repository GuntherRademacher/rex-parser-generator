package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import de.bottlecaps.rex.test.base.AbstractSinglePlatformTest;
import de.bottlecaps.rex.test.base.Pass;

public class TestRegression extends AbstractSinglePlatformTest
{
  private static final String EOL = isWindows ? "\r\n" : "\n";

  @Test
  public void testXmlOnConflicts() throws Exception
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "bug.ebnf",
        "S ::= 'x'+ A ( 'a' | 'c' )",
        "A ::= ( 'a' | 'b' )?"
      );
      String rexOptions =  "-lr 1 -xml";
      Runner runner = run(rexOptions, null, ebnf);

      assertEquals(1, runner.getExitCode(), runner.summary());
      Pass.passEarlyIfPossible(runner, "bug.xml");

      String xml = runner.getFileContent("bug.xml");
      try
      {
        DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        builder.parse(new InputSource(new ByteArrayInputStream(xml.getBytes(StandardCharsets.UTF_8))));
      }
      catch (SAXException e)
      {
        Assertions.fail("xml is not wellformed\n" + xml + "\n" + runner.summary());
      }
      catch (ParserConfigurationException | IOException e)
      {
        throw new RuntimeException(e.getMessage(), e);
      }

      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLlOrderedChoiceCompleteCover()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
          "S ::= ( 's' A ( 'a' | 'b' ) )+ EOF",
          "A ::= 'a'",
          "    / 'a' 'a'",
          "<?TOKENS?>",
          "EOF ::= $"
      );
      String rexOptions =  "-ll 1 -tree -main";
      Runner runner = run(rexOptions, "{saasab}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><TOKEN>s</TOKEN><A><TOKEN>a</TOKEN></A><TOKEN>a</TOKEN><TOKEN>s</TOKEN><A><TOKEN>a</TOKEN></A><TOKEN>b</TOKEN><EOF/></S>", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrOrderedChoiceCompleteCoverShift()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::= ( 's' A ( 'a' | 'b' ) )+ EOF",
          "A ::= 'a' 'a'",
          "    / 'a'",
          "<?TOKENS?>",
          "EOF ::= $"
      );
      String rexOptions =  "-lr 1 -tree -main";
      Runner runner = run(rexOptions, "{saaasaabsab}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><TOKEN>s</TOKEN><A><TOKEN>a</TOKEN><TOKEN>a</TOKEN></A><TOKEN>a</TOKEN><TOKEN>s</TOKEN><A><TOKEN>a</TOKEN><TOKEN>a</TOKEN></A><TOKEN>b</TOKEN><TOKEN>s</TOKEN><A><TOKEN>a</TOKEN></A><TOKEN>b</TOKEN><EOF/></S>", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrOrderedChoiceCompleteCoverReduce()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::= ( 's' A ( 'a' | 'b' ) )+ EOF",
          "A ::= 'a'",
          "    / 'a' 'a'",
          "<?TOKENS?>",
          "EOF ::= $"
      );
      String rexOptions =  "-lr 1 -tree -main";
      Runner runner = run(rexOptions, "{saasab}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><TOKEN>s</TOKEN><A><TOKEN>a</TOKEN></A><TOKEN>a</TOKEN><TOKEN>s</TOKEN><A><TOKEN>a</TOKEN></A><TOKEN>b</TOKEN><EOF/></S>", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrCodeAnnotationsReduce()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::= ( A 'c' | B 'd' )+ EOF",
          "A ::= 'a' <?rex process.stdout.write('Aa');?>",
          "    | 'b' <?rex process.stdout.write('Ab');?>",
          "B ::= 'a' <?rex process.stdout.write('Ba');?>",
          "    | 'b' <?rex process.stdout.write('Bb');?>",
          "<?TOKENS?>",
          "EOF ::= $"
      );
      String rexOptions =  "-lalr 1 -a rex -main";
      Runner runner = runNode(rexOptions, "{acbcadbd}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("AaAbBaBb", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrEmbeddedCodeAnnotations()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::= ( A                   <?rex process.stdout.write('1');?>",
          "          'c'               <?rex process.stdout.write('2');?>",
          "              | B           <?rex process.stdout.write('3');?>",
          "                  'd'       <?rex process.stdout.write('4');?>",
          "                      )+    <?rex process.stdout.write('5');?>",
          "                         EOF",
          "A ::= 'a' <?rex process.stdout.write('Aa');?>",
          "    | 'b' <?rex process.stdout.write('Ab');?>",
          "B ::= 'a' <?rex process.stdout.write('Ba');?>",
          "    | 'b' <?rex process.stdout.write('Bb');?>",
          "<?TOKENS?>",
          "EOF ::= $"
      );
      String rexOptions =  "-lr 2 -a rex -main";
      Runner runner = runNode(rexOptions, "{acbcadbd}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("Aa12Ab12Ba34Bb345", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrFullDoubledCodeAnnotations()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::=                        <?rex process.stdout.write('0');?> <?rex process.stdout.write('0');?>",
          "      ( A                    <?rex process.stdout.write('1');?> <?rex process.stdout.write('1');?>",
          "          'c'                <?rex process.stdout.write('2');?> <?rex process.stdout.write('2');?>",
          "              | B            <?rex process.stdout.write('3');?> <?rex process.stdout.write('3');?>",
          "                  'd'        <?rex process.stdout.write('4');?> <?rex process.stdout.write('4');?>",
          "                      )+     <?rex process.stdout.write('5');?> <?rex process.stdout.write('5');?>",
          "                         EOF <?rex process.stdout.write('6');?> <?rex process.stdout.write('6');?>",
          "A ::= <?rex process.stdout.write('A');?> <?rex process.stdout.write('A');?> 'a' <?rex process.stdout.write('a');?> <?rex process.stdout.write('a');?>",
          "    | <?rex process.stdout.write('A');?> <?rex process.stdout.write('A');?> 'b' <?rex process.stdout.write('b');?> <?rex process.stdout.write('b');?>",
          "B ::= <?rex process.stdout.write('B');?> <?rex process.stdout.write('B');?> 'a' <?rex process.stdout.write('a');?> <?rex process.stdout.write('a');?>",
          "    | <?rex process.stdout.write('B');?> <?rex process.stdout.write('B');?> 'b' <?rex process.stdout.write('b');?> <?rex process.stdout.write('b');?>",
          "<?TOKENS?>",
          "EOF ::= $"
      );
      String rexOptions =  "-lr 2 -a rex -main";
      Runner runner = runNode(rexOptions, "{acbcadbd}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("00AAaa1122AAbb1122BBaa3344BBbb33445566", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrActionFolding()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::= 'x' <?rex    process.stdout.write('0');?> 'y' 'z' <?rex process.stdout.write('1');   ?>",
          "    | 'x' <?rex process.stdout.write('0');   ?> 'y' 'z' <?rex    process.stdout.write('1');?>"
      );
      String rexOptions =  "-lalr 1 -a rex -main";
      Runner runner = runNode(rexOptions, "{xyz}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("01", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrActionFoldingII()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::= A 'w' | B 'u'",
          "A ::= 'x' <?rex    process.stdout.write('0');?> 'y' 'z' <?rex process.stdout.write('0');   ?>",
          "B ::= 'x' <?rex process.stdout.write('0');   ?> 'y' 'z' <?rex    process.stdout.write('0');?>"
      );
      String rexOptions =  "-lalr 3 -a rex -main";
      Runner runner = runNode(rexOptions, "{xyzw}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("00", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrLocalAmbiguity()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::= A EOF",
        "A ::= 'x'+",
        "    | 'x' 'x'",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String rexOptions =  "-lalr 1 -main -tree";
      Runner runner = run(rexOptions, "{xx}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><A><TOKEN>x</TOKEN><TOKEN>x</TOKEN></A><EOF/></S>", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrLocalAmbiguityWithCodeAnnotation()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::= A EOF",
        "A ::= 'x'+ <?rex process.stdout.write('x+');?>",
        "    | 'x' 'x' <?rex process.stdout.write('x+');?>",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String rexOptions =  "-lalr 1 -main -a rex";
      Runner runner = runNode(rexOptions, "{xx}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("x+", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrLocalAmbiguityWithDifferingCodeAnnotations()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::= A EOF",
        "A ::= 'x'+ <?rex process.stdout.write('x+');?>",
        "    | 'x' 'x' <?rex process.stdout.write('xx');?>",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String[] messages =
      {
        "LALR(1) conflict #1 (reduce-reduce):",
        "    A ::= ( 'x' )+ <?rex process.stdout.write('x+');?> .",
        "    A ::= 'x' 'x' <?rex process.stdout.write('xx');?> .",
        "  conflicting lookahead token:",
        "    EOF"
      };
      String rexOptions =  "-lalr 1 -main -a rex";
      Runner runner = runNode(rexOptions, "{xx}", ebnf);
      String summary = runner.summary();
      assertEquals(1, runner.getExitCode(), summary);
      String stdout = runner.getStdout();
      for (String message : messages)
      {
        assertTrue(stdout.contains(message), "missing message: " + message + "\n" + summary);
      }
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrOptionFollowedByAction()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::=  A EOF",
        "A ::= 'a'? <?x /* nothing */;?>",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String rexOptions =  "-lr 1 -a x -main -tree";
      Runner runner = runNode(rexOptions, "{a}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><A><TOKEN>a</TOKEN></A><EOF/></S>", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testNoThrowErrorMessage()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::= A+ EOF",
        "A ::= 'a' 'b'",
        "    | 'a' 'c'",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String rexOptions =  "-ll 1 -backtrack -nothrow";
      Runner runner = run(rexOptions, "{ad}", ebnf);
      String summary = runner.summary();
      assertNotEquals(0, runner.getExitCode(), summary);
      String stderr = runner.getStderr();
      assertTrue(stderr.contains("lexical analysis failed"), summary);
      assertTrue(stderr.contains("while expecting 'c'"), summary);
      assertTrue(stderr.contains("at line 1, column 2"), summary);
      assertTrue(stderr.contains("...d..."), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLlCodeAnnotationsWithTree()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::= A+ EOF",
        "A ::= 'a' <?js process.stderr.write('a');?> <?js process.stderr.write('a');?> 'b' <?js process.stderr.write('b');?> <?js process.stderr.write('b');?> 'c' <?js process.stderr.write('c');?> <?js process.stderr.write('c');?>",
        "    | 'a' <?js process.stderr.write('a');?> <?js process.stderr.write('a');?> 'b' <?js process.stderr.write('b');?> <?js process.stderr.write('b');?> 'd' <?js process.stderr.write('d');?> <?js process.stderr.write('d');?>",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String rexOptions =  "-ll 3 -a js -tree";
      Runner runner = runNode(rexOptions, "{abd}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><A><TOKEN>a</TOKEN><TOKEN>b</TOKEN><TOKEN>d</TOKEN></A><EOF/></S>", runner.getStdout(), summary);
      assertEquals("aabbdd", runner.getStderr(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrCodeAnnotationsWithTree()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::= A+ EOF",
        "A ::= 'a' <?js process.stderr.write('a');?> <?js process.stderr.write('a');?> 'b' <?js process.stderr.write('b');?> <?js process.stderr.write('b');?> 'c' <?js process.stderr.write('c');?> <?js process.stderr.write('c');?>",
        "    | 'a' <?js process.stderr.write('a');?> <?js process.stderr.write('a');?> 'b' <?js process.stderr.write('b');?> <?js process.stderr.write('b');?> 'd' <?js process.stderr.write('d');?> <?js process.stderr.write('d');?>",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String rexOptions =  "-lalr 1 -a js -tree";
      Runner runner = runNode(rexOptions, "{abd}", ebnf);
      String summary = runner.summary();
      assertEquals(1, runner.getExitCode(), summary);
      assertEquals("Code annotations only supported at end of production when combined with tree generation for LR" + EOL, runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testSubtractionOfLetters()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "Characters ::= ( A | NON_A )* EOF",
        "",
        "<?TOKENS?>",
        "",
        "A          ::= [A]",
        "NON_A      ::= . - A",
        "EOF        ::= $",
        "",
        "[A-Z]      == [a-z]",
        "//"
      );
      String tree = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Characters><TOKEN>A</TOKEN><NON_A>B</NON_A><NON_A>C</NON_A><NON_A>-</NON_A><TOKEN>a</TOKEN><NON_A>b</NON_A><NON_A>c</NON_A><EOF/></Characters>";
      String rexOptions =  "-tree";
      Runner runner = run(rexOptions, "{ABC-abc}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals(tree, runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLalr3()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile(Paths.get("../rex/src/parser", "EbnfParser.ebnf"));
      NamedFile input = new NamedFile
      (
          "Lines.ebnf",
          "File    ::= Line? (LF Line?)* EOF\n",
          "\n",
          "<?TOKENS?>\n",
          "\n",
          "Line    ::= .+ - ( .* [#xA#xD] .* )\n",
          "LF      ::= #xD* [#xA#xD]\n",
          "EOF     ::= $\n"
      );
      String rexOptions =  "-lalr 3 -tree -main -trace";
      Runner runner = run(rexOptions, "Lines.ebnf", ebnf, input);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testGLrNotNecessary()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::= 'x' EOF",
          "<?TOKENS?>",
          "EOF ::= $"
      );
      String trace =
          "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
          "<trace>\n" +
          "  <tokenize tokenset=\"1\">\n" +
          "    <next state=\"2\" offset=\"0\" char=\"x\" codepoint=\"120\" class=\"1\" result=\"'x'\"/>\n" +
          "    <done result=\"'x'\" begin=\"0\" end=\"1\"/>\n" +
          "  </tokenize>\n" +
          "  <parse state=\"0\" input=\"'x'\" action=\"shift\"/>\n" +
          "  <tokenize tokenset=\"0\">\n" +
          "    <next state=\"1\" offset=\"1\" codepoint=\"0\" class=\"2\" result=\"EOF\"/>\n" +
          "    <done result=\"EOF\" begin=\"1\" end=\"1\"/>\n" +
          "  </tokenize>\n" +
          "  <parse state=\"1\" input=\"EOF\" action=\"shift reduce\" nonterminal=\"S\" count=\"2\"/>\n" +
          "  <parse state=\"0\" input=\"S\" action=\"accept\"/>\n" +
          "</trace>\n";

      String rexOptions =  "-glalr 19 -main -trace -tree";
      Runner runner = run(rexOptions, "{x}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals(trace, runner.getStderr().replace("\r\n", "\n"), summary);
      assertEquals("<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><TOKEN>x</TOKEN><EOF/></S>", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLalr1Conflicts() throws Exception
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile("input/LR1_but_not_LALR1.ebnf");
      String rexOptions = "-lalr 1";
      String expectedResult =
            "LALR(1) conflict #1 (reduce-reduce):\n"
          + "    A ::= d .\n"
          + "    B ::= d .\n"
          + "  conflicting lookahead tokens:\n"
          + "    a\n"
          + "    c\n"
          + "\n"
          + "1 LALR(1)-conflict\n"
          + "grammar fails to be LALR(1)\n"
          + "";

      Runner runner = run(rexOptions, null, ebnf);
      assertEquals(1, runner.getExitCode(), runner.summary());
      assertEquals(expectedResult, runner.getStdout().replace("\r\n", "\n"));
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLr2Conflicts() throws Exception
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile("input/LL3_but_not_LR2.ebnf");
      String rexOptions = "-lr 2";
      String expectedResult =
            "LR(1) conflict #1 (shift-reduce):\n"
          + "    S ::= . a a\n"
          + "    S ::= . A a a a\n"
          + "    A ::= .\n"
          + "  conflicting lookahead token:\n"
          + "    a\n"
          + "\n"
          + "1 LR(1)-conflict\n"
          + "extending lookahead to 2 did not resolve any LR(1) conflicts\n"
          + "grammar fails to be LR(2)\n"
          + "";

      Runner runner = run(rexOptions, null, ebnf);
      assertEquals(1, runner.getExitCode(), runner.summary());
      assertEquals(expectedResult, runner.getStdout().replace("\r\n", "\n"));
      Pass.passNormally(runner);
    });
  }

  @Test
  public void TestLalr4Conflicts()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
          "S.ebnf",
          "S ::=   'x' 'y' 'z' 'v'",
          "    | A 'x' 'y' 'z' 'w'",
          "    | B 'x' 'y' 'z' 'u'",
          "A ::= ",
          "B ::= ",
          "<?TOKENS?>",
          "WS ::= [ #x9]+ /*ws:definition*/"
      );
      String rexOptions =  "-lalr 3";
      Runner runner = run(rexOptions, "", ebnf);
      String summary = runner.summary();
      assertEquals(1, runner.getExitCode(), summary);
      assertEquals(
          "LALR(1) conflict #1 (shift-reduce-reduce):\n" +
          "    S ::= . 'x' 'y' 'z' 'v'\n" +
          "    S ::= . A 'x' 'y' 'z' 'w'\n" +
          "    S ::= . B 'x' 'y' 'z' 'u'\n" +
          "    A ::= .\n" +
          "    B ::= .\n" +
          "  conflicting lookahead token:\n" +
          "    'x'\n" +
          "\n" +
          "1 LALR(1)-conflict\n" +
          "extending lookahead to 3 did not resolve any LALR(1) conflicts\n" +
          "grammar fails to be LALR(3)\n",
          runner.getStdout().replace("\r", ""),
          summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLR0()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile("strongLL27.ebnf");
      String rexOptions =  "-lr 0";
      Runner runner = run(rexOptions, "", ebnf);
      String summary = runner.summary();
      assertEquals(1, runner.getExitCode(), summary);
      assertEquals("lookahead size must be at least 1", runner.getStdout().trim(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testFirstKUpsizing()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile(
        "S.ebnf",
        "S ::= E '+' N EOF",
        "E ::= N ( ( '+' | '-' ) N )*",
        "",
        "<?TOKENS?>",
        "",
        "N ::= 'x'",
        "EOF ::= $"
      );
      String parseTree =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S><E><TOKEN>x</TOKEN><TOKEN>+</TOKEN><TOKEN>x</TOKEN></E><TOKEN>+</TOKEN><TOKEN>x</TOKEN><EOF/></S>";
      String rexOptions =  "-lalr 3 -tree";
      Runner runner = run(rexOptions, "{x+x+x}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals(parseTree, runner.getStdout().trim(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testTraceWithEmbeddedActions()
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile(
        "S.ebnf",
        "S ::= <?node ;?> A EOF",
        "A ::= 'x'",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String trace =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
        "<trace>\n" +
        "  <tokenize tokenset=\"1\">\n" +
        "    <next state=\"2\" offset=\"0\" char=\"x\" codepoint=\"120\" class=\"1\" result=\"'x'\"/>\n" +
        "    <done result=\"'x'\" begin=\"0\" end=\"1\"/>\n" +
        "  </tokenize>\n" +
        "  <parse state=\"0\" input=\"'x'\" action=\"reduce\" nonterminal=\"IMPLICIT-2\" count=\"0\"/>\n" +
        "  <parse state=\"0\" input=\"IMPLICIT-2 'x'\" action=\"shift\"/>\n" +
        "  <parse state=\"1\" input=\"'x'\" action=\"shift reduce\" nonterminal=\"A\" count=\"1\"/>\n" +
        "  <parse state=\"1\" input=\"A\" action=\"shift\"/>\n" +
        "  <tokenize tokenset=\"0\">\n" +
        "    <next state=\"1\" offset=\"1\" codepoint=\"0\" class=\"2\" result=\"EOF\"/>\n" +
        "    <done result=\"EOF\" begin=\"1\" end=\"1\"/>\n" +
        "  </tokenize>\n" +
        "  <parse state=\"2\" input=\"EOF\" action=\"shift reduce\" nonterminal=\"S\" count=\"3\"/>\n" +
        "  <parse state=\"0\" input=\"S\" action=\"accept\"/>\n" +
        "</trace>\n";
      String rexOptions =  "-lalr 1 -trace -a node";
      Runner runner = runNode(rexOptions, "{x}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals(trace, runner.getStderr(), summary);
      assertEquals("", runner.getStdout(), summary);
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testLrEmbeddedAction() throws Exception
  {
    Pass.expectPass(() ->
    {
      NamedFile ebnf = new NamedFile
      (
        "bug.ebnf",
        "alts::=      <?action //?>",
        "        't'?"
      );

      String rexOptions =  "-lalr 1 -a action -trace";
      Runner runner = run(rexOptions, "{}", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);
      assertEquals("", runner.getStdout().trim(), summary);
      Pass.passNormally(runner);
    });
  }

/*
 *          alts::=                        EMBEDDED_1
                 't'?
   EMBEDDED_1::=                        <?javax System.out.println("alts.peek().addAlt(new Alt());");?>
                                        <?xquery let $state := (trace((), "alts.peek().addAlt(new Alt());"), $state)?>

<?TOKENS?>

          eof::= $
 */
}
