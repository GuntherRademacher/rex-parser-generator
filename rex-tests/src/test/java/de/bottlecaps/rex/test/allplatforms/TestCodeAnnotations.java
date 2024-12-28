package de.bottlecaps.rex.test.allplatforms;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

public class TestCodeAnnotations extends RExRunner
{
  private final String XML_DECLARATION = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  private NamedFile doublyAnnotatedGrammar;
  private String doublyAnnotatedGrammarInput;
  private String doublyAnnotatedGrammarOutput;

  @BeforeEach
  public void before()
  {
    doublyAnnotatedGrammar = new NamedFile
    (
        "S.ebnf",
        "S ::=                        <?xslt <xsl:variable name=\"text\"><xsl:text>0</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>0</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'0'})?>",
        "                             <?xquery let $state := ($state, text{'0'})?>",
        "                             <?java System.out.print(\"0\");?>",
        "                             <?java System.out.print(\"0\");?>",
        "                             <?cpp printf(\"0\");?>",
        "                             <?cpp printf(\"0\");?>",
        "                             <?csharp Console.Out.Write(\"0\");?>",
        "                             <?csharp Console.Out.Write(\"0\");?>",
        "                             <?node process.stdout.write(\"0\");?>",
        "                             <?node process.stdout.write(\"0\");?>",
        "                             <?haxe Sys.print(\"0\");?>",
        "                             <?haxe Sys.print(\"0\");?>",
        "                             <?go fmt.Print(\"0\");?>",
        "                             <?go fmt.Print(\"0\");?>",
        "                             <?python print(\"0\", end=\"\");?>",
        "                             <?python print(\"0\", end=\"\");?>",
        "                             <?scala System.out.print(\"0\")?>",
        "                             <?scala System.out.print(\"0\")?>",
        "                             <?typescript process.stdout.write(\"0\");?>",
        "                             <?typescript process.stdout.write(\"0\");?>",
        "      ( A                    <?xslt <xsl:variable name=\"text\"><xsl:text>1</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>1</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'1'})?>",
        "                             <?xquery let $state := ($state, text{'1'})?>",
        "                             <?java System.out.print(\"1\");?>",
        "                             <?java System.out.print(\"1\");?>",
        "                             <?cpp printf(\"1\");?>",
        "                             <?cpp printf(\"1\");?>",
        "                             <?csharp Console.Out.Write(\"1\");?>",
        "                             <?csharp Console.Out.Write(\"1\");?>",
        "                             <?node process.stdout.write(\"1\");?>",
        "                             <?node process.stdout.write(\"1\");?>",
        "                             <?haxe Sys.print(\"1\");?>",
        "                             <?haxe Sys.print(\"1\");?>",
        "                             <?go fmt.Print(\"1\");?>",
        "                             <?go fmt.Print(\"1\");?>",
        "                             <?python print(\"1\", end=\"\");?>",
        "                             <?python print(\"1\", end=\"\");?>",
        "                             <?scala System.out.print(\"1\")?>",
        "                             <?scala System.out.print(\"1\")?>",
        "                             <?typescript process.stdout.write(\"1\");?>",
        "                             <?typescript process.stdout.write(\"1\");?>",
        "          'c'                <?xslt <xsl:variable name=\"text\"><xsl:text>2</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>2</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'2'})?>",
        "                             <?xquery let $state := ($state, text{'2'})?>",
        "                             <?java System.out.print(\"2\");?>",
        "                             <?java System.out.print(\"2\");?>",
        "                             <?cpp printf(\"2\");?>",
        "                             <?cpp printf(\"2\");?>",
        "                             <?csharp Console.Out.Write(\"2\");?>",
        "                             <?csharp Console.Out.Write(\"2\");?>",
        "                             <?node process.stdout.write(\"2\");?>",
        "                             <?node process.stdout.write(\"2\");?>",
        "                             <?haxe Sys.print(\"2\");?>",
        "                             <?haxe Sys.print(\"2\");?>",
        "                             <?go fmt.Print(\"2\");?>",
        "                             <?go fmt.Print(\"2\");?>",
        "                             <?python print(\"2\", end=\"\");?>",
        "                             <?python print(\"2\", end=\"\");?>",
        "                             <?scala System.out.print(\"2\")?>",
        "                             <?scala System.out.print(\"2\")?>",
        "                             <?typescript process.stdout.write(\"2\");?>",
        "                             <?typescript process.stdout.write(\"2\");?>",
        "              | B            <?xslt <xsl:variable name=\"text\"><xsl:text>3</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>3</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'3'})?>",
        "                             <?xquery let $state := ($state, text{'3'})?>",
        "                             <?java System.out.print(\"3\");?>",
        "                             <?java System.out.print(\"3\");?>",
        "                             <?cpp printf(\"3\");?>",
        "                             <?cpp printf(\"3\");?>",
        "                             <?csharp Console.Out.Write(\"3\");?>",
        "                             <?csharp Console.Out.Write(\"3\");?>",
        "                             <?node process.stdout.write(\"3\");?>",
        "                             <?node process.stdout.write(\"3\");?>",
        "                             <?haxe Sys.print(\"3\");?>",
        "                             <?haxe Sys.print(\"3\");?>",
        "                             <?go fmt.Print(\"3\");?>",
        "                             <?go fmt.Print(\"3\");?>",
        "                             <?python print(\"3\", end=\"\");?>",
        "                             <?python print(\"3\", end=\"\");?>",
        "                             <?scala System.out.print(\"3\")?>",
        "                             <?scala System.out.print(\"3\")?>",
        "                             <?typescript process.stdout.write(\"3\");?>",
        "                             <?typescript process.stdout.write(\"3\");?>",
        "                  'd'        <?xslt <xsl:variable name=\"text\"><xsl:text>4</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>4</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'4'})?>",
        "                             <?xquery let $state := ($state, text{'4'})?>",
        "                             <?java System.out.print(\"4\");?>",
        "                             <?java System.out.print(\"4\");?>",
        "                             <?cpp printf(\"4\");?>",
        "                             <?cpp printf(\"4\");?>",
        "                             <?csharp Console.Out.Write(\"4\");?>",
        "                             <?csharp Console.Out.Write(\"4\");?>",
        "                             <?node process.stdout.write(\"4\");?>",
        "                             <?node process.stdout.write(\"4\");?>",
        "                             <?haxe Sys.print(\"4\");?>",
        "                             <?haxe Sys.print(\"4\");?>",
        "                             <?go fmt.Print(\"4\");?>",
        "                             <?go fmt.Print(\"4\");?>",
        "                             <?python print(\"4\", end=\"\");?>",
        "                             <?python print(\"4\", end=\"\");?>",
        "                             <?scala System.out.print(\"4\")?>",
        "                             <?scala System.out.print(\"4\")?>",
        "                             <?typescript process.stdout.write(\"4\");?>",
        "                             <?typescript process.stdout.write(\"4\");?>",
        "                      )+     <?xslt <xsl:variable name=\"text\"><xsl:text>5</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>5</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'5'})?>",
        "                             <?xquery let $state := ($state, text{'5'})?>",
        "                             <?java System.out.print(\"5\");?>",
        "                             <?java System.out.print(\"5\");?>",
        "                             <?cpp printf(\"5\");?>",
        "                             <?cpp printf(\"5\");?>",
        "                             <?csharp Console.Out.Write(\"5\");?>",
        "                             <?csharp Console.Out.Write(\"5\");?>",
        "                             <?node process.stdout.write(\"5\");?>",
        "                             <?node process.stdout.write(\"5\");?>",
        "                             <?haxe Sys.print(\"5\");?>",
        "                             <?haxe Sys.print(\"5\");?>",
        "                             <?go fmt.Print(\"5\");?>",
        "                             <?go fmt.Print(\"5\");?>",
        "                             <?python print(\"5\", end=\"\");?>",
        "                             <?python print(\"5\", end=\"\");?>",
        "                             <?scala System.out.print(\"5\")?>",
        "                             <?scala System.out.print(\"5\")?>",
        "                             <?typescript process.stdout.write(\"5\");?>",
        "                             <?typescript process.stdout.write(\"5\");?>",
        "                         EOF <?xslt <xsl:variable name=\"text\"><xsl:text>6</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>6</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'6'})?>",
        "                             <?xquery let $state := ($state, text{'6'})?>",
        "                             <?java System.out.print(\"6\");?>",
        "                             <?java System.out.print(\"6\");?>",
        "                             <?cpp printf(\"6\");?>",
        "                             <?cpp printf(\"6\");?>",
        "                             <?csharp Console.Out.Write(\"6\");?>",
        "                             <?csharp Console.Out.Write(\"6\");?>",
        "                             <?node process.stdout.write(\"6\");?>",
        "                             <?node process.stdout.write(\"6\");?>",
        "                             <?haxe Sys.print(\"6\");?>",
        "                             <?haxe Sys.print(\"6\");?>",
        "                             <?go fmt.Print(\"6\");?>",
        "                             <?go fmt.Print(\"6\");?>",
        "                             <?python print(\"6\", end=\"\");?>",
        "                             <?python print(\"6\", end=\"\");?>",
        "                             <?scala System.out.print(\"6\")?>",
        "                             <?scala System.out.print(\"6\")?>",
        "                             <?typescript process.stdout.write(\"6\");?>",
        "                             <?typescript process.stdout.write(\"6\");?>",
        "A ::=                        <?xslt <xsl:variable name=\"text\"><xsl:text>A</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>A</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'A'})?>",
        "                             <?xquery let $state := ($state, text{'A'})?>",
        "                             <?java System.out.print(\"A\");?>",
        "                             <?java System.out.print(\"A\");?>",
        "                             <?cpp printf(\"A\");?>",
        "                             <?cpp printf(\"A\");?>",
        "                             <?csharp Console.Out.Write(\"A\");?>",
        "                             <?csharp Console.Out.Write(\"A\");?>",
        "                             <?node process.stdout.write(\"A\");?>",
        "                             <?node process.stdout.write(\"A\");?>",
        "                             <?haxe Sys.print(\"A\");?>",
        "                             <?haxe Sys.print(\"A\");?>",
        "                             <?go fmt.Print(\"A\");?>",
        "                             <?go fmt.Print(\"A\");?>",
        "                             <?python print(\"A\", end=\"\");?>",
        "                             <?python print(\"A\", end=\"\");?>",
        "                             <?scala System.out.print(\"A\")?>",
        "                             <?scala System.out.print(\"A\")?>",
        "                             <?typescript process.stdout.write(\"A\");?>",
        "                             <?typescript process.stdout.write(\"A\");?>",
        "      'a'                    <?xslt <xsl:variable name=\"text\"><xsl:text>a</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>a</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'a'})?>",
        "                             <?xquery let $state := ($state, text{'a'})?>",
        "                             <?java System.out.print(\"a\");?>",
        "                             <?java System.out.print(\"a\");?>",
        "                             <?cpp printf(\"a\");?>",
        "                             <?cpp printf(\"a\");?>",
        "                             <?csharp Console.Out.Write(\"a\");?>",
        "                             <?csharp Console.Out.Write(\"a\");?>",
        "                             <?node process.stdout.write(\"a\");?>",
        "                             <?node process.stdout.write(\"a\");?>",
        "                             <?haxe Sys.print(\"a\");?>",
        "                             <?haxe Sys.print(\"a\");?>",
        "                             <?go fmt.Print(\"a\");?>",
        "                             <?go fmt.Print(\"a\");?>",
        "                             <?python print(\"a\", end=\"\");?>",
        "                             <?python print(\"a\", end=\"\");?>",
        "                             <?scala System.out.print(\"a\")?>",
        "                             <?scala System.out.print(\"a\")?>",
        "                             <?typescript process.stdout.write(\"a\");?>",
        "                             <?typescript process.stdout.write(\"a\");?>",
        "    |                        <?xslt <xsl:variable name=\"text\"><xsl:text>A</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>A</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'A'})?>",
        "                             <?xquery let $state := ($state, text{'A'})?>",
        "                             <?java System.out.print(\"A\");?>",
        "                             <?java System.out.print(\"A\");?>",
        "                             <?cpp printf(\"A\");?>",
        "                             <?cpp printf(\"A\");?>",
        "                             <?csharp Console.Out.Write(\"A\");?>",
        "                             <?csharp Console.Out.Write(\"A\");?>",
        "                             <?node process.stdout.write(\"A\");?>",
        "                             <?node process.stdout.write(\"A\");?>",
        "                             <?haxe Sys.print(\"A\");?>",
        "                             <?haxe Sys.print(\"A\");?>",
        "                             <?go fmt.Print(\"A\");?>",
        "                             <?go fmt.Print(\"A\");?>",
        "                             <?python print(\"A\", end=\"\");?>",
        "                             <?python print(\"A\", end=\"\");?>",
        "                             <?scala System.out.print(\"A\")?>",
        "                             <?scala System.out.print(\"A\")?>",
        "                             <?typescript process.stdout.write(\"A\");?>",
        "                             <?typescript process.stdout.write(\"A\");?>",
        "      'b'                    <?xslt <xsl:variable name=\"text\"><xsl:text>b</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>b</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'b'})?>",
        "                             <?xquery let $state := ($state, text{'b'})?>",
        "                             <?java System.out.print(\"b\");?>",
        "                             <?java System.out.print(\"b\");?>",
        "                             <?cpp printf(\"b\");?>",
        "                             <?cpp printf(\"b\");?>",
        "                             <?csharp Console.Out.Write(\"b\");?>",
        "                             <?csharp Console.Out.Write(\"b\");?>",
        "                             <?node process.stdout.write(\"b\");?>",
        "                             <?node process.stdout.write(\"b\");?>",
        "                             <?haxe Sys.print(\"b\");?>",
        "                             <?haxe Sys.print(\"b\");?>",
        "                             <?go fmt.Print(\"b\");?>",
        "                             <?go fmt.Print(\"b\");?>",
        "                             <?python print(\"b\", end=\"\");?>",
        "                             <?python print(\"b\", end=\"\");?>",
        "                             <?scala System.out.print(\"b\")?>",
        "                             <?scala System.out.print(\"b\")?>",
        "                             <?typescript process.stdout.write(\"b\");?>",
        "                             <?typescript process.stdout.write(\"b\");?>",
        "B ::=                        <?xslt <xsl:variable name=\"text\"><xsl:text>B</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>B</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'B'})?>",
        "                             <?xquery let $state := ($state, text{'B'})?>",
        "                             <?java System.out.print(\"B\");?>",
        "                             <?java System.out.print(\"B\");?>",
        "                             <?cpp printf(\"B\");?>",
        "                             <?cpp printf(\"B\");?>",
        "                             <?csharp Console.Out.Write(\"B\");?>",
        "                             <?csharp Console.Out.Write(\"B\");?>",
        "                             <?node process.stdout.write(\"B\");?>",
        "                             <?node process.stdout.write(\"B\");?>",
        "                             <?haxe Sys.print(\"B\");?>",
        "                             <?haxe Sys.print(\"B\");?>",
        "                             <?go fmt.Print(\"B\");?>",
        "                             <?go fmt.Print(\"B\");?>",
        "                             <?python print(\"B\", end=\"\");?>",
        "                             <?python print(\"B\", end=\"\");?>",
        "                             <?scala System.out.print(\"B\")?>",
        "                             <?scala System.out.print(\"B\")?>",
        "                             <?typescript process.stdout.write(\"B\");?>",
        "                             <?typescript process.stdout.write(\"B\");?>",
        "      'a'                    <?xslt <xsl:variable name=\"text\"><xsl:text>a</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>a</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'a'})?>",
        "                             <?xquery let $state := ($state, text{'a'})?>",
        "                             <?java System.out.print(\"a\");?>",
        "                             <?java System.out.print(\"a\");?>",
        "                             <?cpp printf(\"a\");?>",
        "                             <?cpp printf(\"a\");?>",
        "                             <?csharp Console.Out.Write(\"a\");?>",
        "                             <?csharp Console.Out.Write(\"a\");?>",
        "                             <?node process.stdout.write(\"a\");?>",
        "                             <?node process.stdout.write(\"a\");?>",
        "                             <?haxe Sys.print(\"a\");?>",
        "                             <?haxe Sys.print(\"a\");?>",
        "                             <?go fmt.Print(\"a\");?>",
        "                             <?go fmt.Print(\"a\");?>",
        "                             <?python print(\"a\", end=\"\");?>",
        "                             <?python print(\"a\", end=\"\");?>",
        "                             <?scala System.out.print(\"a\")?>",
        "                             <?scala System.out.print(\"a\")?>",
        "                             <?typescript process.stdout.write(\"a\");?>",
        "                             <?typescript process.stdout.write(\"a\");?>",
        "    |                        <?xslt <xsl:variable name=\"text\"><xsl:text>B</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>B</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'B'})?>",
        "                             <?xquery let $state := ($state, text{'B'})?>",
        "                             <?java System.out.print(\"B\");?>",
        "                             <?java System.out.print(\"B\");?>",
        "                             <?cpp printf(\"B\");?>",
        "                             <?cpp printf(\"B\");?>",
        "                             <?csharp Console.Out.Write(\"B\");?>",
        "                             <?csharp Console.Out.Write(\"B\");?>",
        "                             <?node process.stdout.write(\"B\");?>",
        "                             <?node process.stdout.write(\"B\");?>",
        "                             <?haxe Sys.print(\"B\");?>",
        "                             <?haxe Sys.print(\"B\");?>",
        "                             <?go fmt.Print(\"B\");?>",
        "                             <?go fmt.Print(\"B\");?>",
        "                             <?python print(\"B\", end=\"\");?>",
        "                             <?python print(\"B\", end=\"\");?>",
        "                             <?scala System.out.print(\"B\")?>",
        "                             <?scala System.out.print(\"B\")?>",
        "                             <?typescript process.stdout.write(\"B\");?>",
        "                             <?typescript process.stdout.write(\"B\");?>",
        "      'b'                    <?xslt <xsl:variable name=\"text\"><xsl:text>b</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xslt <xsl:variable name=\"text\"><xsl:text>b</xsl:text></xsl:variable><xsl:variable name=\"state\" select=\"$state, $text\"/>?>",
        "                             <?xquery let $state := ($state, text{'b'})?>",
        "                             <?xquery let $state := ($state, text{'b'})?>",
        "                             <?java System.out.print(\"b\");?>",
        "                             <?java System.out.print(\"b\");?>",
        "                             <?cpp printf(\"b\");?>",
        "                             <?cpp printf(\"b\");?>",
        "                             <?csharp Console.Out.Write(\"b\");?>",
        "                             <?csharp Console.Out.Write(\"b\");?>",
        "                             <?node process.stdout.write(\"b\");?>",
        "                             <?node process.stdout.write(\"b\");?>",
        "                             <?haxe Sys.print(\"b\");?>",
        "                             <?haxe Sys.print(\"b\");?>",
        "                             <?go fmt.Print(\"b\");?>",
        "                             <?go fmt.Print(\"b\");?>",
        "                             <?python print(\"b\", end=\"\");?>",
        "                             <?python print(\"b\", end=\"\");?>",
        "                             <?scala System.out.print(\"b\")?>",
        "                             <?scala System.out.print(\"b\")?>",
        "                             <?typescript process.stdout.write(\"b\");?>",
        "                             <?typescript process.stdout.write(\"b\");?>",
        "<?TOKENS?>",
        "EOF ::= $"
    );
    doublyAnnotatedGrammarInput = "{acbcadbd}";
    doublyAnnotatedGrammarOutput = "00AAaa1122AAbb1122BBaa3344BBbb33445566";
  }

  @Test
  public void testSimpleXQueryCodeAnnotations()
  {
    Pass.expectPass(() -> {
      NamedFile ebnf = new NamedFile
      (
        "S.ebnf",
        "S ::= A+ EOF",
        "A ::= 'a' <?xquery let $state := ($state, text{'a'})?>",
        "        <?xquery let $state := ($state, text{'a'})?> 'b' <?xquery let $state := ($state, text{'b'})?>",
        "        <?xquery let $state := ($state, text{'b'})?> 'c' <?xquery let $state := ($state, text{'c'})?>",
        "        <?xquery let $state := ($state, text{'c'})?>",
        "    | 'a' <?xquery let $state := ($state, text{'a'})?>",
        "        <?xquery let $state := ($state, text{'a'})?> 'b' <?xquery let $state := ($state, text{'b'})?>",
        "        <?xquery let $state := ($state, text{'b'})?> 'd' <?xquery let $state := ($state, text{'d'})?>",
        "        <?xquery let $state := ($state, text{'d'})?>",
        "<?TOKENS?>",
        "EOF ::= $"
      );
      String rexOptions =  "-a xquery -lalr 1";
      Runner runner = runXQuerySaxon(rexOptions, "{abcabd}", ebnf);
      test(runner, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>aabbccaabbdd");
    });
  }

  private void test(Runner runner, String expectedOutput)
  {
    String summary = runner.summary();
    assertEquals(0, runner.getExitCode(), summary);
    assertEquals(expectedOutput, runner.getStdout().replace("\r\n", "\n"), summary);
    Pass.passNormally(runner);
  }

  @Test
  public void testDoubleXQuerySaxonCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xquery -ll 2";
      Runner runner = runXQuerySaxon(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, XML_DECLARATION + doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleXQueryBaseXCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xquery -ll 2";
      Runner runner = runXQueryBaseX(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, String.join("\n", doublyAnnotatedGrammarOutput.split("")));
    });
  }

  @Test
  public void testDoubleXQuerySaxonCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xquery -lalr 2";
      Runner runner = runXQuerySaxon(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, XML_DECLARATION + doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleXQueryBaseXCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xquery -lalr 2";
      Runner runner = runXQueryBaseX(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, String.join("\n", doublyAnnotatedGrammarOutput.split("")));
    });
  }

  @Test
  public void testDoubleXQuerySaxonCodeAnnotationsGLR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xquery -glr 1";
      Runner runner = runXQuerySaxon(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, XML_DECLARATION + doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleXQueryBaseXCodeAnnotationsGLR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xquery -glr 1";
      Runner runner = runXQueryBaseX(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, String.join("\n", doublyAnnotatedGrammarOutput.split("")));
    });
  }

  @Test
  public void testDoubleXsltCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xslt -ll 2";
      Runner runner = runXsltSaxon(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, XML_DECLARATION + doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleXsltCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xslt -lalr 2";
      Runner runner = runXsltSaxon(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, XML_DECLARATION + doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleXsltCodeAnnotationsGLR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a xslt -glr 1";
      Runner runner = runXsltSaxon(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, XML_DECLARATION + doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleJavaCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a java -ll 2";
      Runner runner = runJava(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleJavaCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a java -lalr 2";
      Runner runner = runJava(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleJavaCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a java -glalr 1";
      Runner runner = runJava(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleCppCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a cpp -ll 2";
      Runner runner = runCppWchar_t(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleCppCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a cpp -lalr 2";
      Runner runner = runCppWchar_t(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleCppCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a cpp -glalr 1";
      Runner runner = runCppWchar_t(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleCSharpCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a csharp -ll 2";
      Runner runner = runMcs(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleCSharpCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a csharp -lalr 2";
      Runner runner = runMcs(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleCSharpCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a csharp -glalr 1";
      Runner runner = runMcs(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleNodeCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a node -ll 2";
      Runner runner = runNode(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleNodeCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a node -lalr 2";
      Runner runner = runNode(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleNodeCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a node -glalr 1";
      Runner runner = runNode(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleScalaCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a scala -ll 2";
      Runner runner = runScala(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleScalaCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a scala -lalr 2";
      Runner runner = runScala(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleScalaCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a scala -glalr 1";
      Runner runner = runScala(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleHaxeCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a haxe -lalr 2";
      Runner runner = runHaxe(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleHaxeCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a haxe -lalr 2";
      Runner runner = runHaxe(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleHaxeCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a haxe -glalr 1";
      Runner runner = runHaxe(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleGoCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a go -ll 2";
      Runner runner = runGo(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleGoCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a go -lalr 2";
      Runner runner = runGo(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleGoCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a go -glalr 1";
      Runner runner = runGo(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoublePythonCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a python -ll 2";
      Runner runner = runPython(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoublePythonCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a python -lalr 2";
      Runner runner = runPython(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoublePythonCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a python -glalr 1";
      Runner runner = runPython(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleTypescriptCodeAnnotationsLL()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a typescript -ll 2";
      Runner runner = runTypescript(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleTypescriptCodeAnnotationsLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a typescript -lalr 2";
      Runner runner = runTypescript(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }

  @Test
  public void testDoubleTypescriptCodeAnnotationsGLALR()
  {
    Pass.expectPass(() -> {
      String rexOptions =  "-a typescript -glalr 1";
      Runner runner = runTypescript(rexOptions, doublyAnnotatedGrammarInput, doublyAnnotatedGrammar);
      test(runner, doublyAnnotatedGrammarOutput);
    });
  }
}
