package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

/**
 * Tests that the standard tree builders of generated Java parsers make the
 * resulting parse tree accessible: getRoot() is null before parsing, and the
 * root nonterminal afterwards.
 */
public class TestTreeBuilderRoot extends RExRunner
{
  @ParameterizedTest
  @CsvSource({
    "-ll 1,TopDownTreeBuilder",
    "-lalr 1,ParseTreeBuilder",
    "-glalr 1,ParseTreeBuilder",
  })
  public void testGetRoot(String options, String builder)
  {
    Pass.expectPass(() ->
    {
      NamedFile grammar = new NamedFile(
        "Root.ebnf",
        "Expr ::= Term ( '+' Term )* EOF",
        "Term ::= 'x' | 'y'",
        "<?TOKENS?>",
        "EOF ::= $",
        "ws ::= ' ' /* ws:definition */");
      NamedFile driver = new NamedFile(
        "RootCheck.java",
        "public class RootCheck",
        "{",
        "  public static void main(String[] args)",
        "  {",
        "    Root." + builder + " b = new Root." + builder + "();",
        "    if (b.getRoot() != null) throw new RuntimeException(\"root before parsing\");",
        "    new Root(\"x + y\", b).parse_Expr();",
        "    Root.Symbol r = b.getRoot();",
        "    System.out.println(r.getName() + \" \" + r.begin + \" \" + r.end + \" \" + ((Root.Nonterminal) r).children.length);",
        "  }",
        "}");

      Runner runner = new Runner();
      assertEquals(0, runner.run(REX, "-java -tree " + options + " Root.ebnf", grammar, driver), runner.summary());
      runner.compile("Root.java");
      runner.expectSuccess("Java compilation", JAVAC, "-encoding UTF-8 RootCheck.java");
      assertEquals(0, runner.run(JAVA, "RootCheck"), runner.summary());
      assertEquals("Expr 0 5 4", runner.getStdout().replace("\r\n", "\n").trim(), runner.summary());
      Pass.passNormally(runner);
    });
  }
}
