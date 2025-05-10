package de.bottlecaps.rex.test.base;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.ByteArrayOutputStream;
import java.io.StringReader;
import java.nio.charset.StandardCharsets;
import java.util.regex.Pattern;

import javax.xml.transform.stream.StreamSource;

import net.sf.saxon.Configuration;
import net.sf.saxon.lib.FeatureKeys;
import net.sf.saxon.s9api.DocumentBuilder;
import net.sf.saxon.s9api.Processor;
import net.sf.saxon.s9api.SaxonApiException;
import net.sf.saxon.s9api.XQueryEvaluator;
import net.sf.saxon.s9api.XQueryExecutable;

public abstract class RExExecutionWithTrace extends RExExecutionWithResult
{
  protected static final Pattern stderrPattern = Pattern.compile(
      "\\w+\\.hx:\\d+: " + "|" +
      "^\\Q" + XML_DECLARATION + "\\E\n?" + "|" +
      "trace \\[1\\]: xs:string: ?" + "|" +
      "(trace\")?<trace>\"?\n" + "|" +
      "(trace\")?</trace>\"?\n$");

  private static Configuration configuration = new Configuration();
  static
  {
    configuration.setConfigurationProperty(FeatureKeys.XQUERY_VERSION, "3.1");
  }
  private static Processor processor = new Processor(configuration);
  private static DocumentBuilder documentBuilder = processor.newDocumentBuilder();

  private static XQueryExecutable normalizeTrace;
  static
  {
    try
    {
      normalizeTrace = processor.newXQueryCompiler().compile(
        "declare namespace map = 'http://www.w3.org/2005/xpath-functions/map';\n" +
        "declare function local:rewrite($nodes, $offsets)\n" +
        "{\n" +
        " for $node in $nodes\n" +
        " return\n" +
        "   typeswitch ($node)\n" +
        "   case document-node() return\n" +
        "     document {local:rewrite($node/node(), $offsets)}\n" +
        "   case element(trace) return\n" +
        "     <trace>{" +
        "       for $event at $i in local:rewrite($node/*, $offsets)\n" +
        "       order by local-name($event), $event/@thread, $event/@offset, $i\n" +
        "       return ('&#xA;  ', $event),\n" +
        "       '&#xA;'\n" +
        "     }</trace>\n" +
        "   case element() return\n" +
        "     element {node-name($node)} {local:rewrite($node/(@*, node()), $offsets)}\n" +
        "   case attribute(offset) | attribute(begin) | attribute(end) return\n" +
        "     attribute {node-name($node)} {$offsets($node)}\n" +
        "   default return\n" +
        "     $node\n" +
        "};\n" +
        "\n" +
        "let $offsets := \n" +
        "  map:merge\n" +
        "  (\n" +
        "    for $offset at $i in\n" +
        "    (\n" +
        "      for $offset in distinct-values(.//@offset)\n" +
        "      order by xs:integer($offset)\n" +
        "      return $offset\n" +
        "    )\n" +
        "    return map {$offset: $i - 1}\n" +
        "  )\n" +
        "return local:rewrite(., $offsets)"
      );
    }
    catch (SaxonApiException e)
    {
      throw new RuntimeException(e);
    }
  }

  private static String normalizeTrace(String trace)
  {
    if ("".equals(trace))
    {
      return trace;
    }
    try
    {
      if (trace.startsWith("trace: \""))
      {
        trace = trace
          .replaceAll("^trace: \"", "")
          .replaceAll("\"$", "")
          .replaceAll("\"\ntrace: \"", "\n")
          .replaceAll("\"\"", "\"")
          .replaceAll("&amp;", "&");
      }
      XQueryEvaluator evaluator = normalizeTrace.load();
      evaluator.setContextItem(documentBuilder.build(new StreamSource(new StringReader("<trace>\n" + trace + "</trace>"))));
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      evaluator.run(processor.newSerializer(baos));
      return new String(baos.toByteArray(), StandardCharsets.UTF_8);
    }
    catch (SaxonApiException e)
    {
      throw new RuntimeException(e);
    }
  }

  @Override
  protected String normalize(String string, Pattern pattern)
  {
    string = super.normalize(string, pattern);
    return normalizeTrace(string);
  }

  @Override
  public Runner runHaxe(String rexOptions, String runtimeOptions, NamedFile... ebnf)
  {
    Runner result = super.runHaxe(rexOptions, runtimeOptions, ebnf);
    result.swapStdoutWithStdErr();
    return result;
  }

  @Override
  protected void verifyResult(Runner runner)
  {
    assertEquals(0, runner.getExitCode(), runner.summary());

    String actualStdout = normalize(runner.getStdout(), stdoutPattern);
    String netExpectedStdout = normalize(expectedStdout, stdoutPattern);
    assertEquals(netExpectedStdout, actualStdout, runner.summary());

    String actualStderr = normalize(runner.getStderr(), stderrPattern);
    String netExpectedStderr = normalize(expectedStderr, stderrPattern);
    assertEquals(netExpectedStderr, actualStderr, runner.summary());

    Pass.passNormally(runner);
  }
}