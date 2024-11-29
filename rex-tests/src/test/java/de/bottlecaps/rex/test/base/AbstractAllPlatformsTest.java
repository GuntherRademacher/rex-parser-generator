package de.bottlecaps.rex.test.base;

import static org.junit.jupiter.api.Assertions.fail;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.regex.Pattern;

import org.junit.jupiter.api.Test;

public abstract class AbstractAllPlatformsTest extends RExRunner
{
  protected static final String XML_DECLARATION = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  protected static Pattern crlfNormalizer = Pattern.compile("\r*\n");

  protected Pattern stdoutPattern = Pattern.compile("(?s)^\\Q" + XML_DECLARATION + "\\E");

  private static Map<String, Long> runtime = new HashMap<>();

  protected NamedFile[] files;
  protected String rexOptions;
  protected String runtimeOptions;

  protected abstract void verifyResult(Runner runner);

  protected void init(String rexOptions, String runtimeOptions, NamedFile... files)
  {
    this.rexOptions = rexOptions;
    this.runtimeOptions = runtimeOptions;
    this.files = files;
  }

  static
  {
    Runtime.getRuntime().addShutdownHook(new Thread()
    {
      @Override
      public void run()
      {
        List<Entry<String, Long>> runtimes = new ArrayList<>(runtime.entrySet());
        Collections.sort(runtimes, new Comparator<Entry<String, Long>>(){
          @Override
          public int compare(Entry<String, Long> o1, Entry<String, Long> o2)
          {
            return o1.getValue().compareTo(o2.getValue());
          }});
        for (Entry<String, Long> r : runtimes)
        {
          System.out.println(String.format("%8.3f sec %s", r.getValue() / 1000.0, r.getKey()));
        }
      }
    });
  }

  protected String normalize(String string, Pattern pattern)
  {
    string = crlfNormalizer.matcher(string).replaceAll("\n");
    if (pattern != null)
      string = pattern.matcher(string).replaceAll("");
    return string;
  }

  @Test
  public void testJava()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runJava(rexOptions, runtimeOptions, files));
      stop("Java", start);
    });
  }

  @Test
  public void testNode()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runNode(rexOptions, runtimeOptions, files));
      stop("Node", start);
    });
  }

  @Test
  public void testScala()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runScala(rexOptions, runtimeOptions, files));
      stop("Scala", start);
    });
  }

  @Test
  public void testCsc()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runCsc(rexOptions, runtimeOptions, files));
      stop("C# (csc)", start);
    });
  }

  @Test
  public void testMcs()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runMcs(rexOptions, runtimeOptions, files));
      stop("C# (mcs)", start);
    });
  }

  @Test
  public void testCppWchar_t()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runCppWchar_t(rexOptions, runtimeOptions, files));
      stop("C++ (wchar_t)", start);
    });
  }

  @Test
  public void testCppChar()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runCppChar(rexOptions, runtimeOptions, files));
      stop("C++ (char)", start);
    });
  }

  @Test
  public void testTypescript()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runTypescript(rexOptions, runtimeOptions, files));
      stop("TypeScript", start);
    });
  }

  @Test
  public void testHaxe()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runHaxe(rexOptions, runtimeOptions, files));
      stop("Haxe", start);
    });
  }

  @Test
  public void testGo()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runGo(rexOptions, runtimeOptions, files));
      stop("Go", start);
    });
  }

  @Test
  public void testPython()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runPython(rexOptions, runtimeOptions, files));
      stop("Python", start);
    });
  }

  @Test
  public void testXQuerySaxon()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runXQuerySaxon(rexOptions.replace("-nothrow", ""), runtimeOptions, files));
      stop("XQuery", start);
    });
  }

  @Test
  public void testXQueryBaseX()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runXQueryBaseX(rexOptions.replace("-nothrow", ""), runtimeOptions, files));
      stop("XQuery", start);
    });
  }

  @Test
  public void testXsltSaxon()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runXsltSaxon(rexOptions.replace("-nothrow", ""), runtimeOptions, files));
      stop("XSLT", start);
    });
  }

  @Test
  public void testSaxonHE()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runSaxonHE(rexOptions, runtimeOptions, files));
      stop("Saxon-HE", start);
    });
  }

//@Test - requires license
  public void testSaxonEE()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runSaxonEE(rexOptions, runtimeOptions, files));
      stop("Saxon-EE", start);
      fail("expected Pass");
    });
  }

  @Test
  public void testBaseX()
  {
    Pass.expectPass(() ->
    {
      long start = System.currentTimeMillis();
      verifyResult(runBaseX(rexOptions, runtimeOptions, files));
      stop("BaseX", start);
    });
  }

  private static void stop(String target, long start)
  {
    long duration = System.currentTimeMillis() - start;
    Long sum = runtime.get(target);
    runtime.put(target, (sum == null ? 0 : sum) + duration);
  }
}