package de.bottlecaps.rex.test.base;

public abstract class AbstractSinglePlatformTest extends RExRunner
{
  public Runner run(String rexOptions, String runtimeOptions, NamedFile... files)
  {
    return runNode(rexOptions, runtimeOptions, files);
  }
}