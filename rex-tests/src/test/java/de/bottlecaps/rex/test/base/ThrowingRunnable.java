package de.bottlecaps.rex.test.base;

@FunctionalInterface
public interface ThrowingRunnable {
  void run() throws Exception;
}