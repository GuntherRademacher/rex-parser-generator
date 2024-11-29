package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.File;
import java.net.URISyntaxException;

import org.junit.jupiter.api.Test;

import de.bottlecaps.rex.test.base.Pass;
import de.bottlecaps.rex.test.base.RExRunner;

public class TestParseXQuery extends RExRunner
{
  @Test
  public void testParseXQuery() throws Exception
  {
    Pass.expectPass(() ->
    {
      String grammar = "REC-xquery-31-20170321.ebnf";
      NamedFile ebnf = new NamedFile(grammar);
      String rexOptions =  "-lalr 2 -performance -name xquery_31";
      Runner runner = runJava(rexOptions, "", ebnf);
      String summary = runner.summary();
      assertEquals(0, runner.getExitCode(), summary);

      String rootFolder;
      try
      {
        rootFolder = new File(getClass().getResource("/" + grammar).toURI()).getParentFile().getAbsolutePath();
      }
      catch (URISyntaxException e)
      {
        throw new RuntimeException(e.getMessage(), e);
      }

      String folder = runner.getFolder();
      runner.setFolder(rootFolder);
      int status = runner.run(JAVA, "-cp " + folder + " xquery_31 -q .xquery.ref");
      runner.setFolder(folder);

      String stderr = runner.getStderr();
      assertEquals(0, status, "Unexpected status, stderr: \n" + stderr);
      String stdout = runner.getStdout();
      assertTrue(stdout.matches("(?s).*loaded \\d+ files.*"), "Unexpected stdout: \n" + stdout);
      assertTrue(stdout.matches("(?s).*parsed \\d+ bytes.*"), "Unexpected stdout: \n" + stdout);
      assertTrue(stdout.matches("(?s).*0 errors.*"), "Unexpected stdout: \n" + stdout);
      Pass.passNormally(runner);
    });
  }
}
