package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithTrace;

public class TestLRParsingTrace extends RExExecutionWithTrace
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-lalr 2 -trace",
      "simple.json",
      new NamedFile("rfc7159.ebnf"),
      new NamedFile("simple.json", "{\"&<\\\">'\":42}")
    );
    expectedStdout = XML_DECLARATION;
    expectedStderr = TRACE;
  }

  private static final String TRACE =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
      "<trace>\n" +
      "  <tokenize tokenset=\"0\">\n" +
      "    <next state=\"1\" offset=\"0\" char=\"{\" codepoint=\"123\" class=\"27\"/>\n" +
      "    <done result=\"ws\" begin=\"0\" end=\"0\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"9\" input=\"ws\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"13\">\n" +
      "    <next state=\"14\" offset=\"0\" char=\"{\" codepoint=\"123\" class=\"27\"/>\n" +
      "    <done result=\"ws\" begin=\"0\" end=\"0\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"0\" input=\"ws\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"10\">\n" +
      "    <next state=\"11\" offset=\"0\" char=\"{\" codepoint=\"123\" class=\"27\" result=\"'{'\"/>\n" +
      "    <done result=\"'{'\" begin=\"0\" end=\"1\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"11\" input=\"'{'\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"0\">\n" +
      "    <next state=\"1\" offset=\"1\" char=\"&quot;\" codepoint=\"34\" class=\"4\"/>\n" +
      "    <done result=\"ws\" begin=\"1\" end=\"1\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"18\" input=\"ws\" action=\"shift reduce\" nonterminal=\"begin-object\" count=\"3\"/>\n" +
      "  <parse state=\"0\" input=\"begin-object\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"7\">\n" +
      "    <next state=\"8\" offset=\"1\" char=\"&quot;\" codepoint=\"34\" class=\"4\"/>\n" +
      "    <next state=\"16\" offset=\"2\" char=\"&amp;\" codepoint=\"38\" class=\"3\"/>\n" +
      "    <next state=\"16\" offset=\"3\" char=\"&lt;\" codepoint=\"60\" class=\"3\"/>\n" +
      "    <next state=\"16\" offset=\"4\" char=\"\\\" codepoint=\"92\" class=\"16\"/>\n" +
      "    <next state=\"22\" offset=\"5\" char=\"&quot;\" codepoint=\"34\" class=\"4\"/>\n" +
      "    <next state=\"16\" offset=\"6\" char=\">\" codepoint=\"62\" class=\"3\"/>\n" +
      "    <next state=\"16\" offset=\"7\" char=\"'\" codepoint=\"39\" class=\"3\"/>\n" +
      "    <next state=\"16\" offset=\"8\" char=\"&quot;\" codepoint=\"34\" class=\"4\" result=\"string\"/>\n" +
      "    <done result=\"string\" begin=\"1\" end=\"9\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"2\" input=\"string\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"0\">\n" +
      "    <next state=\"1\" offset=\"9\" char=\":\" codepoint=\"58\" class=\"12\"/>\n" +
      "    <done result=\"ws\" begin=\"9\" end=\"9\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"5\" input=\"ws\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"4\">\n" +
      "    <next state=\"5\" offset=\"9\" char=\":\" codepoint=\"58\" class=\"12\" result=\"':'\"/>\n" +
      "    <done result=\"':'\" begin=\"9\" end=\"10\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"24\" input=\"':'\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"0\">\n" +
      "    <next state=\"1\" offset=\"10\" char=\"4\" codepoint=\"52\" class=\"11\"/>\n" +
      "    <done result=\"ws\" begin=\"10\" end=\"10\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"26\" input=\"ws\" action=\"shift reduce\" nonterminal=\"name-separator\" count=\"3\"/>\n" +
      "  <parse state=\"5\" input=\"name-separator\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"13\">\n" +
      "    <next state=\"14\" offset=\"10\" char=\"4\" codepoint=\"52\" class=\"11\" result=\"int\"/>\n" +
      "    <next state=\"15\" offset=\"11\" char=\"2\" codepoint=\"50\" class=\"11\" result=\"int\"/>\n" +
      "    <next state=\"15\" offset=\"12\" char=\"}\" codepoint=\"125\" class=\"28\"/>\n" +
      "    <done result=\"int\" begin=\"10\" end=\"12\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"8\" input=\"int\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"11\">\n" +
      "    <next state=\"12\" offset=\"12\" char=\"}\" codepoint=\"125\" class=\"28\"/>\n" +
      "    <done result=\"ws\" begin=\"12\" end=\"12\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"12\" input=\"ws\" action=\"reduce\" nonterminal=\"number\" count=\"1\"/>\n" +
      "  <parse state=\"8\" input=\"number ws\" action=\"shift reduce\" nonterminal=\"value\" count=\"1\"/>\n" +
      "  <parse state=\"8\" input=\"value ws\" action=\"shift reduce\" nonterminal=\"member\" count=\"3\"/>\n" +
      "  <parse state=\"2\" input=\"member ws\" action=\"shift\"/>\n" +
      "  <parse state=\"4\" input=\"ws\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"9\">\n" +
      "    <next state=\"10\" offset=\"12\" char=\"}\" codepoint=\"125\" class=\"28\" result=\"'}'\"/>\n" +
      "    <done result=\"'}'\" begin=\"12\" end=\"13\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"22\" input=\"'}'\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"0\">\n" +
      "    <next state=\"1\" offset=\"13\" codepoint=\"0\" class=\"29\"/>\n" +
      "    <done result=\"ws\" begin=\"13\" end=\"13\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"23\" input=\"ws\" action=\"shift reduce\" nonterminal=\"end-object\" count=\"3\"/>\n" +
      "  <parse state=\"4\" input=\"end-object\" action=\"shift reduce\" nonterminal=\"object\" count=\"3\"/>\n" +
      "  <parse state=\"0\" input=\"object\" action=\"shift reduce\" nonterminal=\"value\" count=\"1\"/>\n" +
      "  <parse state=\"0\" input=\"value\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"0\">\n" +
      "    <next state=\"1\" offset=\"13\" codepoint=\"0\" class=\"29\"/>\n" +
      "    <done result=\"ws\" begin=\"13\" end=\"13\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"10\" input=\"ws\" action=\"shift\"/>\n" +
      "  <tokenize tokenset=\"3\">\n" +
      "    <next state=\"4\" offset=\"13\" codepoint=\"0\" class=\"29\" result=\"EOF\"/>\n" +
      "    <done result=\"EOF\" begin=\"13\" end=\"13\"/>\n" +
      "  </tokenize>\n" +
      "  <parse state=\"16\" input=\"EOF\" action=\"shift reduce\" nonterminal=\"JSON-text\" count=\"4\"/>\n" +
      "  <parse state=\"9\" input=\"JSON-text\" action=\"accept\"/>\n" +
      "</trace>\n";
}
