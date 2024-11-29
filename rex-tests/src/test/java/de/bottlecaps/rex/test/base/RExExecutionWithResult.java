package de.bottlecaps.rex.test.base;

import static org.junit.jupiter.api.Assertions.assertEquals;

public abstract class RExExecutionWithResult extends AbstractAllPlatformsTest
{
  protected String expectedStdout = "";
  protected String expectedStderr = "";

  @Override
  protected void verifyResult(Runner runner)
  {
    assertEquals(0, runner.getExitCode(), runner.summary());

    String actualStdout = normalize(runner.getStdout(), stdoutPattern);
    String netExpectedStdout = normalize(expectedStdout, stdoutPattern);
    assertEquals(netExpectedStdout, actualStdout, runner.summary());

    String actualStderr = normalize(runner.getStderr(), null);
    String netExpectedStderr = normalize(expectedStderr, null);
    assertEquals(netExpectedStderr, actualStderr, runner.summary());

    Pass.passNormally(runner);
  }
}