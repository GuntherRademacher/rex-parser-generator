package de.bottlecaps.rex.test.singleplatform;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;

import de.bottlecaps.rex.test.base.AbstractSinglePlatformTest;
import de.bottlecaps.rex.test.base.Args;
import de.bottlecaps.rex.test.base.Pass;

public class TestRemake extends AbstractSinglePlatformTest
{
  private static boolean runningInEclipse = isEclipseRunnerInStackTrace();

  public static Collection<String> testRemake() throws IOException {
    String suffix = ".ref";
    List<String> filenames = new ArrayList<>();
    try (InputStream in = TestRemake.class.getResourceAsStream("/output");
         BufferedReader br = new BufferedReader(new InputStreamReader(in)))
    {
      for (String resource; (resource = br.readLine()) != null; )
      {
        Assertions.assertTrue(resource.endsWith(suffix));
        filenames.add(resource.substring(0, resource.length() - suffix.length()));
      }
    }
    return filenames;
  }

  @ParameterizedTest
  @MethodSource
  public void testRemake(String fileName)
  {
    Pass.expectPass(() ->
    {
      NamedFile expectedResult = new NamedFile("output/" + fileName + ".ref");
      String expectedContent = expectedResult.getContent();
      String commandLine = rexCommandLine(expectedContent);

      String input = null;
      List<String> args = Args.list(commandLine);

      for (int i = 0; i < args.size(); ++i)
      {
        String arg = args.get(i);
        switch (arg)
        {
        case "-a":
        case "-name":
        case "-ll":
        case "-lr":
        case "-lalr":
        case "-glr":
        case "-glalr":
          i++;
          break;
        default:
          if (! arg.startsWith("-"))
          {
            assertNull(input);
            input = arg;
          }
        }
      }

      assertNotNull(input);

      String inputResourceName = "input/" + input;

      Runner runner = new Runner();
      runner.run(REX, commandLine, new NamedFile(inputResourceName));
      assertEquals(0, runner.getExitCode(), runner.summary());

      runner.compile(fileName);

      String actualContent = new NamedFile(runner.getPath(fileName)).getContent();
      if (! Pass.isSameCode(expectedContent, actualContent)) {
        String summary = runner.summary(
                "actual result does not match expected result, see\n"
              + "    diff " + runner.getPath(fileName) + " " + expectedResult.getPath());
        if (runningInEclipse)
        {
          // when running in Eclipse test runner, show the complete diff
          Assertions.assertEquals(expectedContent, actualContent, summary);
        }
        else
        {
          // otherwise, show just the diff command
          Assertions.fail(summary);
        }
      }

      Pass.passNormally(runner);
    });
  }

  private String rexCommandLine(String content) {
    String commandLineIntroducer = " REx command line: ";
    int begin = content.indexOf(commandLineIntroducer);
    if (begin >= 0)
    {
      begin += commandLineIntroducer.length();
      int end = content.indexOf('\n', begin);
      for (String terminator : Arrays.asList(":)", "*/", "-->"))
      {
        if (terminator.equals(content.substring(end - terminator.length(), end)))
          return content.substring(begin, end - terminator.length());
      }
      return content.substring(begin, end);
    }
    return "";
  }

  private static boolean isEclipseRunnerInStackTrace()
  {
    for (StackTraceElement element : Thread.currentThread().getStackTrace())
    {
      if (element.getClassName().startsWith("org.eclipse.jdt.internal.junit.runner"))
        return true;
    }
    return false;
  }
}
