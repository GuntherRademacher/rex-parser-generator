package de.bottlecaps.rex.test.base;

import static org.junit.jupiter.api.Assertions.fail;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

import org.opentest4j.TestAbortedException;

import de.bottlecaps.rex.test.base.RExRunner.NamedFile;
import de.bottlecaps.rex.test.base.RExRunner.Runner;

public class Pass extends RuntimeException
{
  private static final long serialVersionUID = -7287661853551526015L;
  private static final String cacheRoot = cacheRoot();

  public Pass()
  {
    super("test passed");
  }

  public Pass(Runner runner)
  {
    super("test passed");
    if (cachePath != null)
    {
      if (! cachePath.equals(cachePath(runner))
       || fileName == null
       || content == null)
      {
        throw new IllegalStateException();
      }
      File cacheFile = new File(cachePath + fileName);
      if (! cacheFile.getParentFile().exists())
      {
        cacheFile.getParentFile().mkdirs();
      }
      try
      {
        Path tempPath = new File(cachePath + fileName + ".tmp").toPath();
        Files.write(tempPath, content.getBytes(StandardCharsets.UTF_8), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
        TabFree.main(new String[] {tempPath.toAbsolutePath().toString()});
        Files.move(tempPath, cacheFile.toPath());
      }
      catch (Exception e)
      {
        throw new RuntimeException(runner.summary("caught exception " + e.getMessage()), e);
      }
      cachePath = null;
      fileName = null;
      content = null;
    }
  }

  private Pass(String cachePath)
  {
    super("test passed early, because output file matched cache file in " + cachePath);
  }

  private static String cachePath = null;
  private static String fileName = null;
  private static String content = null;

  public static void passNormally(Runner runner)
  {
    try
    {
      throw new Pass(runner);
    }
    catch (Pass p)
    {
      runner.cleanup();
      throw p;
    }
  }

  public static void passEarlyIfPossible(Runner runner, String fileName)
  {
    Pass.cachePath = null;
    Pass.fileName = null;
    Pass.content = null;

    String content = runner.getFileContent(fileName);
    if (content.isEmpty())
      throw new IllegalStateException();

    String cachePath = cachePath(runner);
    try
    {
      File cacheFile = new File(cachePath + fileName);
      if (cacheFile.exists())
      {
        String cacheContent = new NamedFile(Paths.get(cacheFile.getCanonicalPath())).getContent();    	    
        if (isSameCode(content, cacheContent))
        {
          runner.cleanup();
          throw new Pass(cachePath);
        }
        cacheFile.delete();
      }
    }
    catch (IOException e)
    {
      throw new RuntimeException(e.getMessage(), e);
    }
    Pass.cachePath = cachePath;
    Pass.fileName = fileName;
    Pass.content = content;
  }

  public static boolean isSameCode(String code1, String code2)
  {
    return code2.replaceFirst("This file was generated[^\n]+\n", "").equals(
           code1.replaceFirst("This file was generated[^\n]+\n", ""));
  }

  public static void expectPass(ThrowingRunnable runnable)
  {
    try
    {
      runnable.run();
      fail("expected Pass");
    }
    catch (Pass p)
    {
    }
    catch (TestAbortedException e)
    {
      throw e;
    }
    catch (Exception e)
    {
      throw new RuntimeException(e.getMessage(), e);
    }
  }

  private static String cacheRoot() {
    final String classRoot = RExRunner.class.getProtectionDomain().getCodeSource().getLocation().getPath();
    final String buildRoot = classRoot.endsWith("/bin/test/")
        ? classRoot.substring(0, classRoot.length() - "test/".length())
        : classRoot.endsWith("/build/classes/java/test/")
            ? classRoot.substring(0, classRoot.length() - "classes/java/test/".length())
            : classRoot;
    return buildRoot + "cache/";
  }

  private static String cachePath(Runner runner)
  {
    return cacheRoot +
        runner.outer().testInfo.getTestClass().get().getName().replace('.', '/') + "/" +
        runner.outer().testInfo.getTestMethod().get().getName() + "/";
  }
}