package de.bottlecaps.rex.test.allplatforms;

import java.util.regex.Pattern;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestLRPerformance extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-lr 1 -tree -performance",
      "-q -r 3 simple.expr",
      new NamedFile("expr.ebnf"),
      new NamedFile
      (
        "simple.expr",
        "2+4*(3*2+2*2)"
      )
    );
    expectedStdout =
      "loaded 1 file in 6 msec\n" +
      "parsed 39 bytes in 1 msec (1 MB/sec)\n" +
      "0 errors\n";
    stdoutPattern = Pattern.compile("\\d+(?= msec)| \\(\\d+([.,]\\d+)? [KM]B/sec\\)");
  }

  @Override
  public void testSaxonEE()
  {
    // -performance not supported in this context
  }

  @Override
  public void testSaxonHE()
  {
    // -performance not supported in this context
  }

  @Override
  public void testBaseX()
  {
    // -performance not supported in this context
  }

  @Override
  public void testXQuerySaxon()
  {
    // -performance not supported in this context
  }

  @Override
  public void testXQueryBaseX()
  {
    // -performance not supported in this context
  }

  @Override
  public void testXsltSaxon()
  {
    // -performance not supported in this context
  }
}
