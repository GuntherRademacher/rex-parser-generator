package de.bottlecaps.rex.test.base;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public abstract class RExExecutionWithMessage extends AbstractAllPlatformsTest
{
  protected String expectedStdout = null;
  protected List<String> messages;

  protected void init(String rexOptions, String runtimeOptions, List<String> messages, NamedFile... files)
  {
     super.init(rexOptions, runtimeOptions, files);
     this.messages = messages;
  }

  @Override
  protected void verifyResult(Runner runner)
  {
    assertNotEquals(0, runner.getExitCode(), runner.summary());
    List<String> stderr = Arrays.asList(runner.getStderr().split("(^|\r?\n)\\s*")).stream()
        .map(line -> line.split(", __nativeStack => \\{")[0]) // substring-before, for ignoring Haxe 4.2.1 suffixes on openSUSE Tumbleweed
        .collect(Collectors.toList());
    for (String message : messages)
    {
      assertTrue(stderr.contains(message), "missing message: " + message + "\n" + runner.summary());
    }

    if (expectedStdout != null)
    {
      String actualStdout = normalize(runner.getStdout(), stdoutPattern).trim();
      String netExpectedStdout = normalize(expectedStdout, stdoutPattern).trim();
      assertEquals(netExpectedStdout, actualStdout, runner.summary());
    }

    Pass.passNormally(runner);
  }
}