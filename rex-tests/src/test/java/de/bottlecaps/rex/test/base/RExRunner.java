package de.bottlecaps.rex.test.base;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.StandardOpenOption;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map.Entry;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

import javax.xml.transform.stream.StreamSource;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.TestInfo;
import org.opentest4j.TestAbortedException;

import net.sf.saxon.Configuration;
import net.sf.saxon.s9api.Processor;
import net.sf.saxon.s9api.SaxonApiException;
import net.sf.saxon.s9api.XsltCompiler;

public class RExRunner
{
  protected static final boolean isWindows = System.getProperty("os.name").startsWith("Windows");
  protected static final String WHICH = isWindows ? "where" : "which";
  protected static final int[] UNKNOWN_VERSION = {-1, -1, -1};
  protected static final String XQUERY = "net.sf.saxon.Query";
  protected static final String XSLT = "net.sf.saxon.Transform";

  protected static final boolean USE_VALGRIND;
  protected static final String VALGRIND = "valgrind";
  protected static final String VALGRIND_COMMAND_LINE = "-q --leak-check=full --error-exitcode=42 ";

  protected static final String REX;
  protected static final String JAVAC;
  protected static final String JAVA;
  protected static final String NODE;
  protected static final String NPM;
  protected static final String TSC;
  protected static final String SCALAC;
  protected static final String SCALA;
  protected static final String CSC;
  protected static final String MCS;
  protected static final String MONO;
  protected static final String GPP;
  protected static final String GO;
  protected static final String PYTHON;
  protected static final String HAXE;
  protected static final String NEKO;
  protected static final String SAXON_EE;

  protected static final String JAVA_HOME;
  protected static final String JAVAC_VERSION_STRING;
  protected static final int[] JAVAC_VERSION;
  protected static final int[] PYTHON_VERSION;
  protected static final int[] SCALAC_VERSION;

  protected boolean allowScalaWarmup = true;

  static
  {
    String propertyValue = System.getProperty("USE_VALGRIND");
    USE_VALGRIND = propertyValue == null
                ? false
                : propertyValue.isEmpty() ? true
                                          : Boolean.parseBoolean(propertyValue);
    
    Runner runner = new RExRunner().new Runner(false);

    JAVA = executableName(runner, "java");
    assertNotNull(JAVA, "Java not found");

    JAVAC = executableName(runner, "javac");
    assertNotNull(JAVAC, "Java compiler not found");

    JAVA_HOME = new File(JAVAC).getParentFile().getParentFile().getAbsolutePath();
    JAVAC_VERSION = version(runner, JAVAC, "-version", "");
    JAVAC_VERSION_STRING = runner.getOutput();

    REX = executableName(runner, "rex");
    NODE = executableName(runner, "node");
    TSC = executableName(runner, "tsc");
    HAXE = executableName(runner, "haxe");
    NEKO = executableName(runner, "neko");
    GO = executableName(runner, "go");
    GPP = executableName(runner, "g++");
    CSC = executableName(runner, "csc");
    MCS = executableName(runner, "mcs");
    MONO = executableName(runner, "mono");
    NPM = executableName(runner, "npm");
    PYTHON = executableName(runner, "python3");
    SCALA = executableName(runner, "scala");
    SCALAC = executableName(runner, "scalac");

    SCALAC_VERSION = SCALA == null || SCALAC == null
        ? UNKNOWN_VERSION
        : version(runner, SCALAC, "-version", "version");

    PYTHON_VERSION = PYTHON == null
        ? UNKNOWN_VERSION
        : version(runner, PYTHON, "--version", "");

    SAXON_EE = System.getenv("SAXON_EE");

    // swallow BaseX first-time messages like "writing new configuration file."

    runner.expectSuccess("BaseX initialization", JAVA, "org.basex.BaseX 42");
  }

  @BeforeAll
  public static void beforeAll()
  {
    assertNotNull(REX, "REx executable not found. It must be available on the PATH.");
    assertTrue(JAVAC_VERSION[0] >= 17,
        "At least Java 17 is needed. \"" + JAVAC + " -version\" returned: " + JAVAC_VERSION_STRING);
  }

  private static String executableName(Runner runner, String name) {
    if (0 != runner.run(WHICH, name))
      return null;
    return Arrays.stream(runner.getOutput().split("\r?\n"))
      .map(File::new)
      .filter(f -> ! isWindows || f.getName().contains("."))
      .map(File::getAbsolutePath)
      .findFirst()
      .orElse(null);
  }

  private static int[] version(Runner runner, String command, String options, String versionLineSubstring)
  {
    if (0 != runner.run(command, options))
      return UNKNOWN_VERSION;
    final String versionPattern = "\\d+(?:\\.\\d+)*";
    final String xx = "(?s)^[^\\d]*(" + versionPattern + ").*$";
    final int[] result = Arrays.copyOf(UNKNOWN_VERSION, UNKNOWN_VERSION.length);
    for (String line : runner.getOutput().split("\r?\n"))
      if (line.contains(versionLineSubstring) && line.matches(xx)) {
        int[] version = Arrays.stream(line.replaceFirst(xx, "$1").split("\\."))
            .mapToInt(Integer::parseInt)
            .toArray();
        System.arraycopy(version, 0, result, 0, Math.min(result.length, version.length));
        break;
      }
    return result;
  }

  private void ensureScalacAvailable(Runner runner)
  {
    Pass.assume(SCALAC != null, runner, "\"scalac\" not found. It must be available on the PATH.");
  }

  private void ensureCscAvailable(Runner runner)
  {
    Pass.assume(CSC != null, runner, "\"csc\" not found. It must be available on the PATH.");
  }

  private void ensureMcsAvailable(Runner runner)
  {
    Pass.assume(MCS != null, runner, "\"mcs\" not found. It must be available on the PATH.");
  }

  private void ensureMonoAvailable(Runner runner)
  {
    Pass.assume(MONO != null, runner, "\"mono\" not found. It must be available on the PATH.");
  }

  private void ensureGppAvailable(Runner runner)
  {
    Pass.assume(GPP != null, runner, "\"g++\" not found. It must be available on the PATH.");
  }

  private void ensureTscAvailable(Runner runner)
  {
    Pass.assume(TSC != null, runner, "\"tsc\" not found. It must be available on the PATH.");
  }

  private void ensureHaxeAvailable(Runner runner)
  {
    Pass.assume(HAXE != null, runner, "\"haxe\" not found. It must be available on the PATH.");
  }

  private void ensureNekoAvailable(Runner runner)
  {
    Pass.assume(NEKO != null, runner, "\"neko\" not found. It must be available on the PATH.");
  }

  private void ensureNodeAvailable(Runner runner)
  {
    Pass.assume(NODE != null, runner, "\"node\" not found. It must be available on the PATH.");
  }

  private void ensureSaxonEEAvailable(Runner runner)
  {
    Pass.assume(SAXON_EE != null, runner, "\"SAXON-EE\" not found. Its CLASSPATH entry must be in environment variable SAXON_EE.");
  }

  private void ensureGoAvailable(Runner runner) throws TestAbortedException {
    Pass.assume(GO != null, runner, "\"go\" not found. It must be available on the PATH.");
  }

  private void ensurePythonAvailable(Runner runner) throws TestAbortedException {
    Pass.assume(PYTHON_VERSION[0] >= 3, runner, "\"python3 --version\" failed. It must be available on the PATH.");
  }

  protected static String className(String[] args, String compiler)
  {
    String name = null;
    for (int i = 0; i < args.length; ++i)
    {
      switch (args[i])
      {
      case "-name":
        if (i + 1 < args.length)
          name = args[++i];
        break;
      case "-ll":
      case "-lr":
      case "-lalr":
        ++i;
        break;
      }
    }
    if (name == null)
    {
      name = inputBaseName(args);
      if (name != null)
      {
        int pos = name.lastIndexOf(".");
        if (pos > 0)
        {
          name = name.substring(0, pos);
        }
      }
    }
    if (name != null)
    {
      if(compiler.equals(HAXE))
        name = name.substring(0, 1).toUpperCase() + name.substring(1);
      if(compiler.equals(HAXE)  || compiler.equals(JAVAC) || compiler.equals(SCALAC))
        name = name.replace("-", "_");
    }
    return name;
  }

  private static String inputBaseName(String[] args)
  {
    String name = null;
    for (int i = 0; i < args.length; ++i)
    {
      switch (args[i])
      {
      case "-name":
      case "-ll":
      case "-lr":
        ++i;
        break;
      default:
        if (! args[i].startsWith("-"))
          name = args[i];
      }
    }
    if (name != null)
    {
      int pos = name.lastIndexOf(".");
      if (pos > 0) name = name.substring(0, pos);
    }
    return name;
  }

  protected String commandLine(String defaultRExOptions, String testSpecificRExOptions, NamedFile... files)
  {
    for (NamedFile file : files)
    {
      if ("ebnf".equals(file.getExtension()))
      {
        testSpecificRExOptions += " " + file.getName();
        break;
      }
    }
    if (testSpecificRExOptions.contains("-performance"))
      defaultRExOptions = defaultRExOptions.replaceAll("-main", "");
    String commandLine = defaultRExOptions + " " + testSpecificRExOptions;
    return commandLine.replaceAll(" +", " ");
  }

  private boolean isLiteral(String runtimeOptions)
  {
    return runtimeOptions.contains("{") || runtimeOptions.contains("}");
  }

  public TestInfo testInfo = null;

  @BeforeEach
  public void before(TestInfo testInfo)
  {
    this.testInfo = testInfo;
  }

  public Runner runJava(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-java -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;
    String className = className(runner.getArgs(), JAVAC);
    Pass.passEarlyIfPossible(runner, className + ".java");
    runner.expectSuccess("Java compilation", JAVAC, "-encoding UTF-8 " + className + ".java");
    runner.run(JAVA, "-Dfile.encoding=UTF-8 " + className + " " + runtimeOptions);
    return runner;
  }

  public Runner runScala(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-scala -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensureScalacAvailable(runner);

    String className = className(runner.getArgs(), SCALAC);
    Pass.passEarlyIfPossible(runner, className + ".scala");
    if (SCALAC_VERSION[0] > 3 || SCALAC_VERSION[0] == 3 && SCALAC_VERSION[1] >= 5)
    {
      Pass.assume(JAVAC_VERSION[0] >= 17, runner, "Running on Java "+ JAVAC_VERSION[0] + ", but Scala 3.5+ requires Java 17 or higher");
      runner.expectSuccess("Scala compilation", SCALA, "compile " + className + ".scala");
      runner.run(SCALA, "run " + className + ".scala -- " + runtimeOptions);
    }
    else
    {
      runner.expectSuccess("Scala compilation", SCALAC, className + ".scala");
      runner.run(SCALA, className + " " + runtimeOptions);
    }
    return runner;
  }

  public Runner runCsc(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-csharp -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensureCscAvailable(runner);

    String className = className(runner.getArgs(), CSC);
    Pass.passEarlyIfPossible(runner, className + ".cs");
    runner.expectSuccess("C# compilation", CSC, className + ".cs");
    final String exeFile = runner.getFolder() + File.separator + className + ".exe";
    if (isWindows) {
      runner.run(exeFile, runtimeOptions);
    }
    else if (MONO != null) {
      runner.run(MONO, exeFile + " " + runtimeOptions);
    }
    else {
      runner.expectSuccess("Setting execute permission", "chmod", "+x " + exeFile);
      runner.run(exeFile, runtimeOptions);
    }
    return runner;
  }

  public Runner runMcs(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-csharp -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensureMcsAvailable(runner);

    String className = className(runner.getArgs(), MCS);
    Pass.passEarlyIfPossible(runner, className + ".cs");
    if (0 == runner.run(MCS, className + ".cs"))
    {
      ensureMonoAvailable(runner);
      runner.run(MONO, runner.getFolder() + File.separator + className + ".exe " + runtimeOptions);
    }
    return runner;
  }

  public Runner runNode(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-javascript -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensureNodeAvailable(runner);

    String className = className(runner.getArgs(), NODE);
    Pass.passEarlyIfPossible(runner, className + ".js");
    runner.run(NODE, className + ".js " + runtimeOptions);
    return runner;
  }

  public Runner runTypescript(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-typescript -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensureTscAvailable(runner);

    String baseName = className(runner.getArgs(), TSC);
    Pass.passEarlyIfPossible(runner, baseName + ".ts");
    if (0 != runner.run(NPM, "init -y")) throw new RuntimeException(runner.summary());
    if (0 != runner.run(NPM, "install --save-dev @types/node")) throw new RuntimeException(runner.summary());
    if (0 == runner.run(TSC, baseName + ".ts "))
    {
      runner.run(NODE, baseName + ".js " + runtimeOptions);
    }
    return runner;
  }

  private Runner runCpp(
      String charOption,
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    Runner runner = new Runner();
    runner.expectSuccess("REx processing", REX, commandLine("-cpp" + charOption + " -main", rexOptions, files), files);

    ensureGppAvailable(runner);

    String baseName = className(runner.getArgs(), GPP);
    Pass.passEarlyIfPossible(runner, baseName + ".cpp");
    final String exeFile = baseName + ".exe";
    runner.expectSuccess("C++ compilation", GPP, "-o " + exeFile + " " + baseName + ".cpp");
    if (USE_VALGRIND)
    {
      runner.run(VALGRIND, VALGRIND_COMMAND_LINE +
                 runner.getFolder() + File.separator + exeFile + " " + runtimeOptions);
    }
    else
    {
      runner.run(runner.getFolder() + File.separator + exeFile, runtimeOptions);
    }
    return runner;
  }

  public Runner runCppWchar_t(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    return runCpp("", rexOptions, runtimeOptions, files);
  }

  public Runner runCppChar(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    return runCpp(" -char", rexOptions, runtimeOptions, files);
  }

  public Runner runHaxe(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-haxe -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensureHaxeAvailable(runner);

    String baseName = className(runner.getArgs(), HAXE);
    Pass.passEarlyIfPossible(runner, baseName + ".hx");
    if (0 == runner.run(HAXE, "-main " + baseName + " -neko " + baseName + ".n"))
    {
      ensureNekoAvailable(runner);
      runner.run(NEKO, baseName + ".n " + runtimeOptions);
    }
    return runner;
  }

  public Runner runGo(
    String rexOptions,
    String runtimeOptions,
    NamedFile... files)
  {
    String commandLine = commandLine("-go -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensureGoAvailable(runner);

    String baseName = className(runner.getArgs(), GO);
    Pass.passEarlyIfPossible(runner, baseName + ".go");
    if (0 != runner.run(GO, "mod init " + baseName)) throw new RuntimeException(runner.summary());
    if (0 == runner.run(GO, "build"))
    {
      String folder = runner.getFolder();
      runner.run(folder + File.separator + baseName, runtimeOptions);
    }
    return runner;
  }

  public Runner runPython(
          String rexOptions,
          String runtimeOptions,
          NamedFile... files)
  {
    String commandLine = commandLine("-python -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) return runner;

    ensurePythonAvailable(runner);

    String baseName = className(runner.getArgs(), PYTHON);
    Pass.passEarlyIfPossible(runner, baseName + ".py");
    runner.run(PYTHON, baseName + ".py " + runtimeOptions);
    return runner;
  }

  public Runner runXQuerySaxon(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-xquery -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) throw new RuntimeException(runner.summary());
    String baseName = className(runner.getArgs(), XQUERY);
    Pass.passEarlyIfPossible(runner, baseName + ".xquery");
    runner.run(JAVA, "net.sf.saxon.Query " + baseName + ".xquery input=" + runtimeOptions);
    return runner;
  }

  public Runner runXQueryBaseX(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-xquery -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) throw new RuntimeException(runner.summary());
    String baseName = className(runner.getArgs(), XQUERY);
    Pass.passEarlyIfPossible(runner, baseName + ".xquery");
    runner.run(JAVA, "org.basex.BaseX -binput=" + runtimeOptions + " " + baseName + ".xquery");
    return runner;
  }

  public Runner runXsltSaxon(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-xslt -main", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) throw new RuntimeException(runner.summary());
    String baseName = className(runner.getArgs(), XSLT);
    Pass.passEarlyIfPossible(runner, baseName + ".xslt");
    runner.run(JAVA, "net.sf.saxon.Transform -versionmsg:off -xsl:" + baseName + ".xslt -it:main input=" + runtimeOptions);
    return runner;
  }

  public Runner runSaxonHE(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-java -saxon", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) throw new RuntimeException(runner.summary());
    String className = className(runner.getArgs(), JAVAC);
    Pass.passEarlyIfPossible(runner, className + ".java");
    if (0 != runner.run(JAVAC, className + ".java")) throw new RuntimeException(runner.summary());
    String java = new NamedFile(Paths.get(runner.getFolder(), className + ".java")).getContent();
    Pattern pattern = Pattern.compile(".*\"parse-([^\"]+)\".*", Pattern.DOTALL);
    Matcher matcher = pattern.matcher(java);
    String startSymbol = matcher.find() ? matcher.group(1) : "NOTFOUND";
    runner.run(JAVA, "net.sf.saxon.Query -init:" + className + "$SaxonInitializer -qs:\"" +
      "declare namespace p='" + className + "'; " +
      "declare variable $input external; " +
      "let $tree := p:parse-" + startSymbol + "(" +
      (isLiteral(runtimeOptions) ? "substring($input, 2, string-length($input) - 2)" : "unparsed-text($input)") +
      ") return if ($tree/self::ERROR) then error(xs:QName('" + this.getClass().getSimpleName() + "'), concat('&#xA;', $tree)) else $tree " +
      "\" input=" + runtimeOptions);
    return runner;
  }

  public Runner runSaxonEE(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-java -saxon", rexOptions, files);
    Runner runner = new Runner();
    if (0 != runner.run(REX, commandLine, files)) throw new RuntimeException(runner.summary());

    ensureSaxonEEAvailable(runner);

    String className = className(runner.getArgs(), JAVAC);
    Pass.passEarlyIfPossible(runner, className + ".java");
    if (0 != runner.run(JAVAC, "-cp \"." + System.getProperty("path.separator") + SAXON_EE + "\" " + className + ".java")) throw new RuntimeException(runner.summary());
    String java = new NamedFile(Paths.get(runner.getFolder(), className + ".java")).getContent();
    Pattern pattern = Pattern.compile(".*public static Sequence(?:<\\?>)? parse([^(]+)\\(XPathContext context, String input\\).*", Pattern.DOTALL);
    Matcher matcher = pattern.matcher(java);
    String startSymbol = matcher.find() ? matcher.group(1) : "NOTFOUND";
    runner.run(JAVA, "-cp \"." + System.getProperty("path.separator") + SAXON_EE + "\" net.sf.saxon.Query -qs:\"" +
      "declare namespace p='java:" + className + "'; " +
      "declare variable $input external; " +
      "let $tree := p:parse-" + startSymbol + "(" +
      (isLiteral(runtimeOptions) ? "substring($input, 2, string-length($input) - 2)" : "unparsed-text($input)") +
      ") return if ($tree/self::ERROR) then error(xs:QName('" + this.getClass().getSimpleName() + "'), concat('&#xA;', $tree)) else $tree " +
      "\" input=" + runtimeOptions);
    return runner;
  }

  public Runner runBaseX(
      String rexOptions,
      String runtimeOptions,
      NamedFile... files)
  {
    String commandLine = commandLine("-java -basex", rexOptions, files);
    Runner runner = new Runner();
    String className = className(runner.args(REX, commandLine, files), JAVAC);
    if (commandLine.contains("-name "))
      commandLine = commandLine.replace("-name ", "-name pkg.");
    else
      commandLine = "-name pkg." + className + " " + commandLine;
    if (0 != runner.run(REX, commandLine, files)) return runner;
    Pass.passEarlyIfPossible(runner, className + ".java");
    runner.expectSuccess("Java compilation", JAVAC, "-d . " + className + ".java");
    String java = new NamedFile(Paths.get(runner.getFolder(), className + ".java")).getContent();
    Pattern pattern = Pattern.compile(".*public static ANode parse([^(]+)\\(Str str\\).*", Pattern.DOTALL);
    Matcher matcher = pattern.matcher(java);
    String startSymbol = matcher.find() ? matcher.group(1) : "NOTFOUND";
    runner.run(JAVA, "org.basex.BaseX -sindent=no -binput=" + runtimeOptions + " \"" +
      "declare namespace p='java:pkg." + className + "'; " +
      "declare variable $input external; " +
      "let $tree := p:parse-" + startSymbol + "(" +
      (isLiteral(runtimeOptions) ? "substring($input, 2, string-length($input) - 2)" : "unparsed-text($input)") +
      ") return if ($tree/self::ERROR) then error(xs:QName('" + this.getClass().getSimpleName() + "'), concat('&#xA;', $tree)) else $tree" +
      "\"");
    return runner;
  }

  public static class NamedFile
  {
    private String name;
    private String content;
    private String path;

    public NamedFile(String name, String... content)
    {
      this.name = name;
      this.content = String.join("\n", content);
      this.path = null;
    }

    public NamedFile(String resourceName)
    {
      try
      {
        URL resource = this.getClass().getResource("/" + resourceName);
        path = new File(resource.toURI()).getAbsolutePath();
        assertNotNull(resource, "missing resource: " + resourceName);
        Path path = Paths.get(resource.toURI());
        name = path.toFile().getName();
        content = read(path);
      }
      catch (IOException | URISyntaxException e)
      {
        throw new RuntimeException(e.getMessage(), e);
      }
    }

    private static String read(Path path) throws IOException {
      String content = new String(Files.readAllBytes(path), StandardCharsets.UTF_8);
      if (content.startsWith("\uFEFF"))
        return content.substring(1);
      else
        return content;
    }

    public NamedFile(Path path)
    {
      try
      {
        name = path.toFile().getName();
        this.path = path.toFile().getAbsolutePath();
        content = read(path);
      }
      catch (IOException e)
      {
        throw new RuntimeException(e.getMessage(), e);
      }
    }

    public String getBaseName()
    {
      int pos = name.lastIndexOf(".");
      if (pos > 0)
      {
          return name.substring(0, pos);
      }
      return name;
    }

    public String getName()
    {
      return name;
    }

    public String getPath() {
      return path;
    }

    public String getExtension() {
      int i = name.lastIndexOf('.');
      return i < 0 ? null : name.substring(i + 1);
    }

    public String getContent()
    {
      return content;
    }

    public void write(String folder)
    {
      try
      {
        Path path = Paths.get(folder, name);
        Files.write(path, content.getBytes(StandardCharsets.UTF_8));
      }
      catch (IOException e)
      {
        throw new RuntimeException(e.getMessage(), e);
      }
    }
  }

  public class Runner
  {
    private int exitCode;
    private String stdout;
    private String stderr;
    private Path folder;
    private String[] args;

    public Runner()
    {
      this(true);
    }

    public Runner(boolean createFolder)
    {
      if (createFolder) {
        try
        {
          String prefix = RExRunner.class.getSimpleName() + "-" +
            testInfo.getTestClass().get().getSimpleName() + "-" +
            testInfo.getTestMethod().get().getName() + "-";
          folder = Files.createTempDirectory(prefix);
        }
        catch (IOException e)
        {
          throw new RuntimeException(e.getMessage(), e);
        }
      }
    }

    public RExRunner outer()
    {
      return RExRunner.this;
    }

    public void cleanup()
    {
      try
      {
        Files.walkFileTree(folder, new SimpleFileVisitor<Path>()
        {
          @Override
          public FileVisitResult visitFile(Path file, BasicFileAttributes attrs)
          {
            return delete(file);
          }

          @Override
          public FileVisitResult postVisitDirectory(Path dir, IOException exc)
          {
            return delete(dir);
          }

          private FileVisitResult delete(Path file)
          {
            try
            {
              Files.delete(file);
            }
            catch (IOException e)
            {
            }
            return FileVisitResult.CONTINUE;
          }
       });
      }
      catch (IOException e)
      {
        throw new RuntimeException(e.getMessage(), e);
      }
      folder = null;
    }

    public String[] getArgs() {
      return args;
    }

    public String getFolder()
    {
      return folder.toString();
    }

    public void setFolder(String folder)
    {
      this.folder = Paths.get(folder);
    }

    public Path getPath(String runnerFileName)
    {
      return Paths.get(folder.toString(), runnerFileName);
    }

    public String getFileContent(String runnerFileName)
    {
      return new NamedFile(getPath(runnerFileName)).getContent();
    }

    public String summary()
    {
      return summary(this.getClass().getSimpleName() + " failed");
    }

    public String summary(String msg)
    {
      StringBuilder sb = new StringBuilder();
      sb.append(msg);
      sb.append("\nworking dir: " + folder);
      sb.append("\ncommand: ");
      sb.append(Arrays.stream(args)
          .map(arg -> arg.contains(" ") ? '"' + arg + '"': arg)
          .collect(Collectors.joining(" ")));
      sb.append("\nexit code: ");
      sb.append(getExitCode());
      sb.append("\n");
      sb.append(("stdout:\n" + getStdout()).trim().replaceAll("\n", "\n    "));
      sb.append("\n");
      sb.append(("stderr:\n" + getStderr()).trim().replaceAll("\n", "\n    "));
      sb.append("\n");
      return sb.toString();
    }

    public int getExitCode() {return exitCode;}
    public String getStderr() {return stderr;}
    public String getStdout() {return stdout;}

    public String getOutput()
    {
      return stdout == null || stdout.isEmpty()
          ? stderr
          : stderr == null || stderr.isEmpty()
              ? stdout
              : stdout + "\n" + stderr;
    }

    public void expectSuccess(String step, String command, String coomandLine, NamedFile... input)
    {
      if (0 != run(command, coomandLine, input))
        throw new RuntimeException(summary(step + " failed"));
    }

    public int run(String command, String commandLine, NamedFile... input)
    {
      if (USE_VALGRIND && command.equals(REX))
      {
        command = VALGRIND;
        commandLine = VALGRIND_COMMAND_LINE + REX + " " + commandLine;
      }
      try
      {
        List<String> environment = new ArrayList<>();
        environment.add("FLAGS=R");
        for (Entry<String, String> e : System.getenv().entrySet())
        {
          String key = e.getKey();
          String value = e.getValue();
          switch (key) {
          case "CLASSPATH":
          case "JAVA_HOME":
            break;
          case "PATH":
            environment.add(key + "=" + trimPath(value));
            break;
          default:
            environment.add(key + "=" + e.getValue());
          }
        }

        environment.add("JAVA_HOME=" + JAVA_HOME);
        environment.add("CLASSPATH=." + System.getProperty("path.separator") + trimPath(System.getProperty("java.class.path")));

        args = args(command, commandLine, input);
        Process proc = Runtime.getRuntime().exec(
            args,
            environment.toArray(new String[environment.size()]),
            folder == null ? null : folder.toFile());
        StreamCollector stderrCollector = new StreamCollector(proc.getErrorStream());
        StreamCollector stdoutCollector = new StreamCollector(proc.getInputStream());

        exitCode = proc.waitFor();
        if (allowScalaWarmup && command == SCALA && commandLine.startsWith("compile "))
        {
          // Scala 3.5 spawns a compilation server upon first compilation, causing the output
          // streams not to see EOF. Ignore them upon success, otherwise rerun compilation.
          allowScalaWarmup = false;
          if (exitCode == 0)
          {
            stderr = "";
            stdout = "";
            return exitCode;
          }
          proc = Runtime.getRuntime().exec(
              args,
              environment.toArray(new String[environment.size()]),
              folder == null ? null : folder.toFile());
          stderrCollector = new StreamCollector(proc.getErrorStream());
          stdoutCollector = new StreamCollector(proc.getInputStream());
        }
        stderr = stderrCollector.toString();
        stdout = stdoutCollector.toString();
        return exitCode;
      }
      catch (Exception e)
      {
        throw new RuntimeException(e.getMessage(), e);
      }
    }

    public String[] args(String command, String commandLine, NamedFile... input) {
      List<String> argList = new ArrayList<>();
      argList.add(isWindows ? command : command.replace(".bat", "").replace(".cmd", ""));
      Args.list(commandLine).stream().forEach(arg -> argList.add(arg));

      for (NamedFile file : input)
      {
        file.write(folder.toString());
      }

      return argList.toArray(new String[argList.size()]);
    }

    public void swapStdoutWithStdErr()
    {
      String temp = stderr;
      stderr = stdout;
      stdout = temp;
    }

    public void compile(String path)
    {
      String fileName = new File(path).getName();
      if (fileName.endsWith(".java"))
      {
        Pass.passEarlyIfPossible(this, path);
        expectSuccess("Java compilation", JAVAC, "-encoding UTF-8 " + fileName);
      }
      else if (fileName.endsWith(".scala"))
      {
        ensureScalacAvailable(this);
        Pass.passEarlyIfPossible(this, path);
        if (SCALAC_VERSION[0] > 3 || SCALAC_VERSION[0] ==3 && SCALAC_VERSION[1] >= 5)
          expectSuccess("Scala compilation", SCALA, "compile " + fileName);
        else
          expectSuccess("Scala compilation", SCALAC, fileName);
      }
      else if (fileName.endsWith(".cs"))
      {
        ensureCscAvailable(this);
        Pass.passEarlyIfPossible(this, path);
        expectSuccess("C# compilation", CSC, fileName);
      }
      else if (fileName.endsWith(".xquery"))
      {
        Pass.passEarlyIfPossible(this, path);
        if (0 != run(JAVA, "net.sf.saxon.Query -repeat:0 " + fileName))
        {
          if (! stderr.contains("Module declaration must not be used in a main module"))
            throw new RuntimeException(summary("XQuery compilation failed"));
          String content = new NamedFile(Paths.get(folder.toString(), path)).getContent();
          String namespace = content.replaceFirst("(?s)^.*\nmodule namespace p=\"([^\"]*)\";\n.*$", "$1");
          expectSuccess("XQuery compilation", JAVA, "net.sf.saxon.Query -repeat:0 -qs:\"import module namespace m='" + namespace + "' at '"+ fileName + "'; ()\"");
        }
      }
      else if (fileName.endsWith(".xslt"))
      {
        Pass.passEarlyIfPossible(this, path);
        XsltCompiler compiler = new Processor(new Configuration()).newXsltCompiler();
        try
        {
          compiler.compile(new StreamSource(Paths.get(folder.toString(), path).toFile()));
        }
        catch (SaxonApiException e)
        {
          throw new RuntimeException(summary(e.getMessage()), e);
        }
      }
      else if (fileName.endsWith(".xml"))
      {
        Pass.passEarlyIfPossible(this, path);
        expectSuccess("XML parsing", JAVA, "net.sf.saxon.Query \"-qs:count(*/*)\" -s:" + fileName);
      }
      else if (fileName.endsWith(".cpp"))
      {
        ensureGppAvailable(this);
        Pass.passEarlyIfPossible(this, path);
        expectSuccess("C++ compilation", GPP, "-Wall -c " + fileName);
      }
      else if (fileName.endsWith(".hpp"))
      {
        ensureGppAvailable(this);
        Pass.passEarlyIfPossible(this, path);
        if (! fileName.startsWith("HelloWorld_REx_")
         && ! fileName.equals("XqcTtdaG.hpp")
         && ! fileName.equals("XmlParser.hpp"))
        {
          String cppFile = fileName.replace(".hpp", ".cpp");
          String cppPath = getFolder() + File.separator + cppFile;
          try
          {
            Files.write(Paths.get(cppPath), ("#include \"" + fileName + "\"").getBytes(StandardCharsets.UTF_8), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
          }
          catch (IOException e)
          {
            throw new RuntimeException(e.getMessage(), e);
          }
          expectSuccess("", GPP, "-Wall -c " + cppFile);
        }
      }
      else if (fileName.endsWith(".ts"))
      {
        ensureTscAvailable(this);
        Pass.passEarlyIfPossible(this, path);
        expectSuccess("npm init", NPM, "init -y");
        expectSuccess("npm node types installation", NPM, "install --save-dev @types/node");
        expectSuccess("TypeScript compilation", TSC, "--noImplicitAny " + fileName);
      }
      else if (fileName.endsWith(".rex"))
      {
        Pass.passEarlyIfPossible(this, path);
        expectSuccess("REx processing", REX, fileName);
      }
      else if (fileName.endsWith(".hx"))
      {
        ensureHaxeAvailable(this);
        Pass.passEarlyIfPossible(this, path);
        expectSuccess("Haxe compilation", HAXE, fileName);
      }
      else if (fileName.endsWith(".js"))
      {
        ensureNodeAvailable(this);
        Pass.passEarlyIfPossible(this, path);
        File ecmaScriptParserFile;
        try
        {
          ecmaScriptParserFile = new File(RExRunner.class.getResource("/output/EcmaScript.js.ref").toURI());
        }
        catch (URISyntaxException e)
        {
          throw new RuntimeException(e.getMessage(), e);
        }
        expectSuccess("Haxe compilation", NODE, ecmaScriptParserFile.getAbsolutePath() + " " + fileName);
      }
      else
      {
        fail("don't know how to compile (or otherwise verify) " + path);
      }
    }
  }

  private static String trimPath(String path) {
    return Arrays.stream(path.split(File.pathSeparator))
      .map(String::trim)
      .filter(e -> ! e.isEmpty())
      .collect(Collectors.joining(File.pathSeparator));
  }
}

