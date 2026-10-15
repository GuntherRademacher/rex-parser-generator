package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

/**
 * Tests for Java code generation with option -codepoints, where the generated
 * parser takes its input as an int[] array of Unicode codepoints. Offsets are
 * codepoint offsets then, so they differ from UTF-16 offsets as soon as the
 * input contains characters outside of the Basic Multilingual Plane.
 */
public class TestJavaCodepoints extends RExRunner
{
  private static final String EMOJI = new String(Character.toChars(0x1F600));
  private static final String FULLWIDTH_EXCLAMATION = "！";

  private static NamedFile grammar()
  {
    return new NamedFile(
      "nonbmp.ebnf",
      "S ::= Item* EOF",
      "Item ::= Run | Ctx | Fix | Word | Plain",
      "<?TOKENS?>",
      "Run ::= [#x10000-#x10FFFF] [#x10000-#x10FFFF]*",
      "Ctx ::= 'b' & '" + EMOJI + "'",
      "Fix ::= '" + EMOJI + FULLWIDTH_EXCLAMATION + "' & [a-z]+",
      "Word ::= [a-z]+",
      "Plain ::= [#xE000-#xFFFF]",
      "EOF ::= $");
  }

  private static final String TREE_INPUT =
      EMOJI + EMOJI + "b" + EMOJI + "ab" + EMOJI + FULLWIDTH_EXCLAMATION + "xyz" + EMOJI + EMOJI + EMOJI + "c";

  private static final String EXPECTED_TREE =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?><S>"
    + "<Item><Run>" + EMOJI + EMOJI + "</Run></Item>"
    + "<Item><TOKEN>b</TOKEN></Item>"
    + "<Item><Run>" + EMOJI + "</Run></Item>"
    + "<Item><Word>ab</Word></Item>"
    + "<Item><Fix>" + EMOJI + FULLWIDTH_EXCLAMATION + "</Fix></Item>"
    + "<Item><Word>xyz</Word></Item>"
    + "<Item><Run>" + EMOJI + EMOJI + EMOJI + "</Run></Item>"
    + "<Item><Word>c</Word></Item>"
    + "<EOF/></S>";

  @Test
  public void testTreeWithNonBmpCharacters()
  {
    Pass.expectPass(() ->
    {
      Runner runner = runJavaCodepoints("-tree", "test.data", grammar(), new NamedFile("test.data", TREE_INPUT));
      assertEquals(0, runner.getExitCode(), runner.summary());
      assertEquals(EXPECTED_TREE, runner.getStdout().trim(), runner.summary());
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testTreeWithNonBmpCharactersUtf16()
  {
    // same as above, but with UTF-16 input: verifies the fixed-length token end computation
    // for characters in range U+DC00..U+FFFF following a surrogate pair
    Pass.expectPass(() ->
    {
      Runner runner = runJava("-tree", "test.data", grammar(), new NamedFile("test.data", TREE_INPUT));
      assertEquals(0, runner.getExitCode(), runner.summary());
      assertEquals(EXPECTED_TREE, runner.getStdout().trim(), runner.summary());
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testTraceOffsetsAreCodepointOffsets()
  {
    Pass.expectPass(() ->
    {
      Runner runner = runJavaCodepoints("-trace", "test.data", grammar(), new NamedFile("test.data", EMOJI + "b" + EMOJI));
      assertEquals(0, runner.getExitCode(), runner.summary());
      String trace = runner.getStderr();
      assertTrue(trace.contains("<done result=\"Run\" begin=\"0\" end=\"1\"/>"), runner.summary());
      assertTrue(trace.contains("<done result=\"'b'\" begin=\"1\" end=\"2\"/>"), runner.summary());
      assertTrue(trace.contains("<done result=\"Run\" begin=\"2\" end=\"3\"/>"), runner.summary());
      assertTrue(trace.contains("<done result=\"EOF\" begin=\"3\" end=\"3\"/>"), runner.summary());
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testErrorColumnCountsCodepoints()
  {
    Pass.expectPass(() ->
    {
      Runner runner = runJavaCodepoints("-tree", "test.data", grammar(), new NamedFile("test.data", EMOJI + EMOJI + "ab#"));
      assertEquals(1, runner.getExitCode(), runner.summary());
      assertTrue(runner.getStderr().contains("lexical analysis failed"), runner.summary());
      assertTrue(runner.getStderr().contains("at line 1, column 5:"), runner.summary());
      Pass.passNormally(runner);
    });
  }

  @Test
  public void testCodepointsRequiresJava()
  {
    Runner runner = new Runner();
    runner.run(REX, "-csharp -codepoints nonbmp.ebnf", grammar());
    assertEquals(1, runner.getExitCode(), runner.summary());
    assertTrue(runner.getStdout().contains("missing option: -codepoints also requires -java"), runner.summary());
    runner.cleanup();
  }

  @Test
  public void testCodepointsExcludesNoLexer()
  {
    Runner runner = new Runner();
    runner.run(REX, "-java -codepoints -nolexer nonbmp.ebnf", grammar());
    assertEquals(1, runner.getExitCode(), runner.summary());
    assertTrue(runner.getStdout().contains("option -codepoints cannot be combined with -nolexer"), runner.summary());
    runner.cleanup();
  }
}
