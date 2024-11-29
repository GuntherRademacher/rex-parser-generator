package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestXmlSerialization extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-tree",
      "test.data",
      new NamedFile(
        "test.ebnf",
        "test ::= string EOF",
        "<?TOKENS?>",
        "string ::= .*",
        "EOF ::= $"),
      new NamedFile(
        "test.data",
        "<>'\"&")
    );
    expectedStdout = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><test><string>&lt;&gt;'\"&amp;</string><EOF/></test>";
  }
}
