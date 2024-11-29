package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.net.URISyntaxException;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithTrace;

public class TestBacktrackingTrace extends RExExecutionWithTrace
{
  @BeforeEach
  public void before() throws IOException, URISyntaxException
  {
    init
    (
      "-trace -ll 1 -backtrack -nothrow",
      "\"{5 * (5 + 3)}\"",
      new NamedFile
      (
        "exprPEG.ebnf",
        "input   ::= ws? expr ws? EOF\n",
        "expr    ::= term ( ws? ('+' | '-') ws? term )*\n",
        "term    ::= factor ( ws? ('*' | '/') ws? factor)*\n",
        "factor  ::= integer | '(' ws? expr ws? ')'\n",
        "integer ::= ( '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' )+\n",
        "<?TOKENS?>\n",
        "ws      ::= ' '\n",
        "EOF     ::= $"
      )
    );

    expectedStdout = XML_DECLARATION;
    expectedStderr = TRACE;
  }

  private static String TRACE =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
      "<trace>\n" +
      "  <parse startnonterminal=\"input\"/>\n" +
      "  <tokenize tokenset=\"6\">\n" +
      "    <next state=\"7\" offset=\"0\" char=\"5\" codepoint=\"53\" class=\"13\" result=\"'5'\"/>\n" +
      "    <done result=\"'5'\" begin=\"0\" end=\"1\"/>\n" +
      "  </tokenize>\n" +
      "  <parse startnonterminal=\"expr\" input=\"'5'\"/>\n" +
      "  <parse startnonterminal=\"term\" input=\"'5'\"/>\n" +
      "  <parse startnonterminal=\"factor\" input=\"'5'\"/>\n" +
      "  <parse startnonterminal=\"integer\" input=\"'5'\"/>\n" +
      "  <parse terminal=\"'5'\"/>\n" +
      "  <tokenize tokenset=\"7\">\n" +
      "    <next state=\"8\" offset=\"1\" char=\" \" codepoint=\"32\" class=\"1\" result=\"ws\"/>\n" +
      "    <done result=\"ws\" begin=\"1\" end=\"2\"/>\n" +
      "  </tokenize>\n" +
      "  <parse endnonterminal=\"integer\" input=\"ws\"/>\n" +
      "  <parse endnonterminal=\"factor\" input=\"ws\"/>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <tokenize tokenset=\"2\">\n" +
      "    <next state=\"3\" offset=\"2\" char=\"*\" codepoint=\"42\" class=\"4\" result=\"'*'\"/>\n" +
      "    <done result=\"'*'\" begin=\"2\" end=\"3\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"'*'\"/>\n" +
      "  <tokenize tokenset=\"6\">\n" +
      "    <next state=\"7\" offset=\"3\" char=\" \" codepoint=\"32\" class=\"1\" result=\"ws\"/>\n" +
      "    <done result=\"ws\" begin=\"3\" end=\"4\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <try startnonterminal=\"factor\"/>\n" +
      "  <tokenize tokenset=\"5\">\n" +
      "    <next state=\"6\" offset=\"4\" char=\"(\" codepoint=\"40\" class=\"2\" result=\"'('\"/>\n" +
      "    <done result=\"'('\" begin=\"4\" end=\"5\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"'('\"/>\n" +
      "  <tokenize tokenset=\"6\">\n" +
      "    <next state=\"7\" offset=\"5\" char=\"5\" codepoint=\"53\" class=\"13\" result=\"'5'\"/>\n" +
      "    <done result=\"'5'\" begin=\"5\" end=\"6\"/>\n" +
      "  </tokenize>\n" +
      "  <try startnonterminal=\"expr\" input=\"'5'\"/>\n" +
      "  <try startnonterminal=\"term\" input=\"'5'\"/>\n" +
      "  <try startnonterminal=\"factor\" input=\"'5'\"/>\n" +
      "  <try startnonterminal=\"integer\" input=\"'5'\"/>\n" +
      "  <parse terminal=\"'5'\"/>\n" +
      "  <tokenize tokenset=\"7\">\n" +
      "    <next state=\"8\" offset=\"6\" char=\" \" codepoint=\"32\" class=\"1\" result=\"ws\"/>\n" +
      "    <done result=\"ws\" begin=\"6\" end=\"7\"/>\n" +
      "  </tokenize>\n" +
      "  <try endnonterminal=\"integer\" input=\"ws\"/>\n" +
      "  <try endnonterminal=\"factor\" input=\"ws\"/>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <tokenize tokenset=\"2\">\n" +
      "    <next state=\"3\" offset=\"7\" char=\"+\" codepoint=\"43\" class=\"5\"/>\n" +
      "    <fail begin=\"7\" end=\"7\" state=\"3\"/>\n" +
      "  </tokenize>\n" +
      "  <try endnonterminal=\"term\" input=\"ws\"/>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <tokenize tokenset=\"3\">\n" +
      "    <next state=\"4\" offset=\"7\" char=\"+\" codepoint=\"43\" class=\"5\" result=\"'+'\"/>\n" +
      "    <done result=\"'+'\" begin=\"7\" end=\"8\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"'+'\"/>\n" +
      "  <tokenize tokenset=\"6\">\n" +
      "    <next state=\"7\" offset=\"8\" char=\" \" codepoint=\"32\" class=\"1\" result=\"ws\"/>\n" +
      "    <done result=\"ws\" begin=\"8\" end=\"9\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <try startnonterminal=\"term\"/>\n" +
      "  <try startnonterminal=\"factor\"/>\n" +
      "  <tokenize tokenset=\"5\">\n" +
      "    <next state=\"6\" offset=\"9\" char=\"3\" codepoint=\"51\" class=\"11\" result=\"'3'\"/>\n" +
      "    <done result=\"'3'\" begin=\"9\" end=\"10\"/>\n" +
      "  </tokenize>\n" +
      "  <try startnonterminal=\"integer\" input=\"'3'\"/>\n" +
      "  <parse terminal=\"'3'\"/>\n" +
      "  <tokenize tokenset=\"7\">\n" +
      "    <next state=\"8\" offset=\"10\" char=\")\" codepoint=\"41\" class=\"3\" result=\"')'\"/>\n" +
      "    <done result=\"')'\" begin=\"10\" end=\"11\"/>\n" +
      "  </tokenize>\n" +
      "  <try endnonterminal=\"integer\" input=\"')'\"/>\n" +
      "  <try endnonterminal=\"factor\" input=\"')'\"/>\n" +
      "  <try endnonterminal=\"term\" input=\"')'\"/>\n" +
      "  <try endnonterminal=\"expr\" input=\"')'\"/>\n" +
      "  <parse terminal=\"')'\"/>\n" +
      "  <try endnonterminal=\"factor\"/>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <tokenize tokenset=\"2\">\n" +
      "    <next state=\"3\" offset=\"2\" char=\"*\" codepoint=\"42\" class=\"4\" result=\"'*'\"/>\n" +
      "    <done result=\"'*'\" begin=\"2\" end=\"3\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"'*'\"/>\n" +
      "  <tokenize tokenset=\"6\">\n" +
      "    <next state=\"7\" offset=\"3\" char=\" \" codepoint=\"32\" class=\"1\" result=\"ws\"/>\n" +
      "    <done result=\"ws\" begin=\"3\" end=\"4\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <parse startnonterminal=\"factor\"/>\n" +
      "  <tokenize tokenset=\"5\">\n" +
      "    <next state=\"6\" offset=\"4\" char=\"(\" codepoint=\"40\" class=\"2\" result=\"'('\"/>\n" +
      "    <done result=\"'('\" begin=\"4\" end=\"5\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"'('\"/>\n" +
      "  <tokenize tokenset=\"6\">\n" +
      "    <next state=\"7\" offset=\"5\" char=\"5\" codepoint=\"53\" class=\"13\" result=\"'5'\"/>\n" +
      "    <done result=\"'5'\" begin=\"5\" end=\"6\"/>\n" +
      "  </tokenize>\n" +
      "  <parse startnonterminal=\"expr\" input=\"'5'\"/>\n" +
      "  <parse startnonterminal=\"term\" input=\"'5'\"/>\n" +
      "  <parse startnonterminal=\"factor\" input=\"'5'\"/>\n" +
      "  <parse startnonterminal=\"integer\" input=\"'5'\"/>\n" +
      "  <parse terminal=\"'5'\"/>\n" +
      "  <tokenize tokenset=\"7\">\n" +
      "    <next state=\"8\" offset=\"6\" char=\" \" codepoint=\"32\" class=\"1\" result=\"ws\"/>\n" +
      "    <done result=\"ws\" begin=\"6\" end=\"7\"/>\n" +
      "  </tokenize>\n" +
      "  <parse endnonterminal=\"integer\" input=\"ws\"/>\n" +
      "  <parse endnonterminal=\"factor\" input=\"ws\"/>\n" +
      "  <parse endnonterminal=\"term\" input=\"ws\"/>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <tokenize tokenset=\"3\">\n" +
      "    <next state=\"4\" offset=\"7\" char=\"+\" codepoint=\"43\" class=\"5\" result=\"'+'\"/>\n" +
      "    <done result=\"'+'\" begin=\"7\" end=\"8\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"'+'\"/>\n" +
      "  <tokenize tokenset=\"6\">\n" +
      "    <next state=\"7\" offset=\"8\" char=\" \" codepoint=\"32\" class=\"1\" result=\"ws\"/>\n" +
      "    <done result=\"ws\" begin=\"8\" end=\"9\"/>\n" +
      "  </tokenize>\n" +
      "  <parse terminal=\"ws\"/>\n" +
      "  <parse startnonterminal=\"term\"/>\n" +
      "  <parse startnonterminal=\"factor\"/>\n" +
      "  <tokenize tokenset=\"5\">\n" +
      "    <next state=\"6\" offset=\"9\" char=\"3\" codepoint=\"51\" class=\"11\" result=\"'3'\"/>\n" +
      "    <done result=\"'3'\" begin=\"9\" end=\"10\"/>\n" +
      "  </tokenize>\n" +
      "  <parse startnonterminal=\"integer\" input=\"'3'\"/>\n" +
      "  <parse terminal=\"'3'\"/>\n" +
      "  <tokenize tokenset=\"7\">\n" +
      "    <next state=\"8\" offset=\"10\" char=\")\" codepoint=\"41\" class=\"3\" result=\"')'\"/>\n" +
      "    <done result=\"')'\" begin=\"10\" end=\"11\"/>\n" +
      "  </tokenize>\n" +
      "  <parse endnonterminal=\"integer\" input=\"')'\"/>\n" +
      "  <parse endnonterminal=\"factor\" input=\"')'\"/>\n" +
      "  <parse endnonterminal=\"term\" input=\"')'\"/>\n" +
      "  <parse endnonterminal=\"expr\" input=\"')'\"/>\n" +
      "  <parse terminal=\"')'\"/>\n" +
      "  <parse endnonterminal=\"factor\"/>\n" +
      "  <tokenize tokenset=\"4\">\n" +
      "    <next state=\"5\" offset=\"11\" codepoint=\"0\" class=\"18\" result=\"EOF\"/>\n" +
      "    <done result=\"EOF\" begin=\"11\" end=\"11\"/>\n" +
      "  </tokenize>\n" +
      "  <parse endnonterminal=\"term\" input=\"EOF\"/>\n" +
      "  <parse endnonterminal=\"expr\" input=\"EOF\"/>\n" +
      "  <parse terminal=\"EOF\"/>\n" +
      "  <parse endnonterminal=\"input\"/>\n" +
      "</trace>\n";
}