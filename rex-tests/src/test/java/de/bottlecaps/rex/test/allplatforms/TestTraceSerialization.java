package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithTrace;

public class TestTraceSerialization extends RExExecutionWithTrace
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-trace",
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
    expectedStderr =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
      "<trace>\n" +
      "  <parse startnonterminal=\"test\"/>\n" +
      "  <tokenize tokenset=\"0\">\n" +
      "    <next state=\"1\" offset=\"0\" char=\"&lt;\" codepoint=\"60\" class=\"1\" result=\"string\"/>\n" +
      "    <next state=\"1\" offset=\"1\" char=\">\" codepoint=\"62\" class=\"1\" result=\"string\"/>\n" +
      "    <next state=\"1\" offset=\"2\" char=\"'\" codepoint=\"39\" class=\"1\" result=\"string\"/>\n" +
      "    <next state=\"1\" offset=\"3\" char=\"&quot;\" codepoint=\"34\" class=\"1\" result=\"string\"/>\n" +
      "    <next state=\"1\" offset=\"4\" char=\"&amp;\" codepoint=\"38\" class=\"1\" result=\"string\"/>\n" +
      "    <next state=\"1\" offset=\"5\" codepoint=\"0\" class=\"2\"/>\n" +
      "    <done result=\"string\" begin=\"0\" end=\"5\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"string\"/>\n" +
      "  <tokenize tokenset=\"1\">\n" +
      "    <next state=\"2\" offset=\"5\" codepoint=\"0\" class=\"2\" result=\"EOF\"/>\n" +
      "    <done result=\"EOF\" begin=\"5\" end=\"5\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"EOF\"/>\n" +
      "  <parse endnonterminal=\"test\"/>\n" +
      "</trace>\n";
  }
}
