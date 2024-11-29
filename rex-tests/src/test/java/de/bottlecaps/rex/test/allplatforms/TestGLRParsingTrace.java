package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;
import java.nio.file.Paths;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithTrace;

public class TestGLRParsingTrace extends RExExecutionWithTrace
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-glalr 1 -trace",
      "simple.ebnf",
      new NamedFile(Paths.get("../rex/src/parser", "EbnfParser.ebnf")),
      new NamedFile
      (
        "simple.ebnf",
        "S ::= A",
        "A ::= 'x' <?a /*A*/?>"
      )
    );
    expectedStdout = XML_DECLARATION;
    expectedStderr = TRACE;
  }

  private static final String TRACE =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
    "<trace>\n" +
    "  <tokenize thread=\"0\" tokenset=\"13\">\n" +
    "    <next state=\"14\" offset=\"0\" char=\"S\" codepoint=\"83\" class=\"31\" result=\"Name\"/>\n" +
    "    <next state=\"50\" offset=\"1\" char=\" \" codepoint=\"32\" class=\"3\"/>\n" +
    "    <done result=\"Name\" begin=\"0\" end=\"1\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"0\" offset=\"0\" state=\"0\" input=\"Name\" action=\"reduce\" nonterminal=\"Prolog\" count=\"0\"/>\n" +
    "  <parse thread=\"0\" offset=\"0\" state=\"0\" input=\"Prolog Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"0\" offset=\"0\" state=\"1\" input=\"Name\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"0\" tokenset=\"7\">\n" +
    "    <next state=\"8\" offset=\"1\" char=\" \" codepoint=\"32\" class=\"3\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"2\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"1\" end=\"2\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"0\" tokenset=\"7\">\n" +
    "    <next state=\"8\" offset=\"2\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"54\" offset=\"3\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"83\" offset=\"4\" char=\"=\" codepoint=\"61\" class=\"20\" result=\"'::='\"/>\n" +
    "    <done result=\"'::='\" begin=\"2\" end=\"5\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"0\" offset=\"1\" state=\"35\" input=\"'::='\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"0\" tokenset=\"40\">\n" +
    "    <next state=\"41\" offset=\"5\" char=\" \" codepoint=\"32\" class=\"3\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"6\" char=\"A\" codepoint=\"65\" class=\"23\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"5\" end=\"6\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"0\" tokenset=\"40\">\n" +
    "    <next state=\"41\" offset=\"6\" char=\"A\" codepoint=\"65\" class=\"23\" result=\"Name\"/>\n" +
    "    <next state=\"50\" offset=\"7\" codepoint=\"10\" class=\"2\"/>\n" +
    "    <done result=\"Name\" begin=\"6\" end=\"7\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"0\" offset=\"5\" state=\"8\" input=\"Name\" action=\"fork\"/>\n" +
    "  <parse thread=\"0\" offset=\"5\" state=\"8\" input=\"Name\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"0\" tokenset=\"46\">\n" +
    "    <next state=\"47\" offset=\"7\" codepoint=\"10\" class=\"2\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"8\" char=\"A\" codepoint=\"65\" class=\"23\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"7\" end=\"8\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"0\" tokenset=\"46\">\n" +
    "    <next state=\"47\" offset=\"8\" char=\"A\" codepoint=\"65\" class=\"23\" result=\"Name\"/>\n" +
    "    <next state=\"50\" offset=\"9\" char=\" \" codepoint=\"32\" class=\"3\"/>\n" +
    "    <done result=\"Name\" begin=\"8\" end=\"9\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"1\" offset=\"5\" state=\"8\" input=\"Name\" action=\"reduce\" nonterminal=\"SyntaxSequence\" count=\"0\"/>\n" +
    "  <parse thread=\"1\" offset=\"5\" state=\"8\" input=\"SyntaxSequence Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"1\" offset=\"5\" state=\"41\" input=\"Name\" action=\"reduce\" nonterminal=\"SyntaxChoice\" count=\"1\"/>\n" +
    "  <parse thread=\"1\" offset=\"5\" state=\"8\" input=\"SyntaxChoice Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"1\" offset=\"5\" state=\"12\" input=\"Name\" action=\"reduce\" nonterminal=\"SyntaxProduction\" count=\"3\"/>\n" +
    "  <parse thread=\"1\" offset=\"5\" state=\"1\" input=\"SyntaxProduction Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"1\" offset=\"5\" state=\"4\" input=\"Name\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"1\" tokenset=\"7\">\n" +
    "    <next state=\"8\" offset=\"7\" codepoint=\"10\" class=\"2\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"8\" char=\"A\" codepoint=\"65\" class=\"23\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"7\" end=\"8\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"1\" tokenset=\"7\">\n" +
    "    <next state=\"8\" offset=\"8\" char=\"A\" codepoint=\"65\" class=\"23\"/>\n" +
    "    <fail begin=\"8\" end=\"8\" state=\"8\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"0\" offset=\"7\" state=\"14\" input=\"Name\" action=\"reduce\" nonterminal=\"NameOrString\" count=\"1\"/>\n" +
    "  <parse thread=\"0\" offset=\"7\" state=\"8\" input=\"NameOrString Name\" action=\"shift reduce\" nonterminal=\"SyntaxPrimary\" count=\"1\"/>\n" +
    "  <parse thread=\"0\" offset=\"7\" state=\"8\" input=\"SyntaxPrimary Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"0\" offset=\"7\" state=\"42\" input=\"Name\" action=\"reduce\" nonterminal=\"SyntaxItem\" count=\"1\"/>\n" +
    "  <parse thread=\"0\" offset=\"7\" state=\"8\" input=\"SyntaxItem Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"0\" offset=\"7\" state=\"13\" input=\"Name\" action=\"fork\"/>\n" +
    "  <parse thread=\"0\" offset=\"7\" state=\"13\" input=\"Name\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"0\" tokenset=\"46\">\n" +
    "    <next state=\"47\" offset=\"9\" char=\" \" codepoint=\"32\" class=\"3\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"10\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"9\" end=\"10\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"0\" tokenset=\"46\">\n" +
    "    <next state=\"47\" offset=\"10\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <fail begin=\"10\" end=\"10\" state=\"47\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"1\" offset=\"7\" state=\"35\" input=\"\" action=\"fail\"/>\n" +
    "  <parse thread=\"2\" offset=\"7\" state=\"13\" input=\"Name\" action=\"reduce\" nonterminal=\"SyntaxSequence\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"7\" state=\"8\" input=\"SyntaxSequence Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"7\" state=\"41\" input=\"Name\" action=\"reduce\" nonterminal=\"SyntaxChoice\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"7\" state=\"8\" input=\"SyntaxChoice Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"7\" state=\"12\" input=\"Name\" action=\"reduce\" nonterminal=\"SyntaxProduction\" count=\"3\"/>\n" +
    "  <parse thread=\"2\" offset=\"7\" state=\"1\" input=\"SyntaxProduction Name\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"7\" state=\"4\" input=\"Name\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"7\">\n" +
    "    <next state=\"8\" offset=\"9\" char=\" \" codepoint=\"32\" class=\"3\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"10\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"9\" end=\"10\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"2\" tokenset=\"7\">\n" +
    "    <next state=\"8\" offset=\"10\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"54\" offset=\"11\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"83\" offset=\"12\" char=\"=\" codepoint=\"61\" class=\"20\" result=\"'::='\"/>\n" +
    "    <done result=\"'::='\" begin=\"10\" end=\"13\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"0\" offset=\"9\" state=\"14\" input=\"\" action=\"fail\"/>\n" +
    "  <parse thread=\"2\" offset=\"9\" state=\"35\" input=\"'::='\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"40\">\n" +
    "    <next state=\"41\" offset=\"13\" char=\" \" codepoint=\"32\" class=\"3\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"14\" char=\"'\" codepoint=\"39\" class=\"9\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"13\" end=\"14\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"2\" tokenset=\"40\">\n" +
    "    <next state=\"41\" offset=\"14\" char=\"'\" codepoint=\"39\" class=\"9\"/>\n" +
    "    <next state=\"60\" offset=\"15\" char=\"x\" codepoint=\"120\" class=\"49\"/>\n" +
    "    <next state=\"60\" offset=\"16\" char=\"'\" codepoint=\"39\" class=\"9\" result=\"StringLiteral\"/>\n" +
    "    <done result=\"StringLiteral\" begin=\"14\" end=\"17\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"2\" offset=\"13\" state=\"8\" input=\"StringLiteral\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"47\">\n" +
    "    <next state=\"48\" offset=\"17\" char=\" \" codepoint=\"32\" class=\"3\" result=\"Whitespace\"/>\n" +
    "    <next state=\"52\" offset=\"18\" char=\"&lt;\" codepoint=\"60\" class=\"19\"/>\n" +
    "    <done result=\"Whitespace\" begin=\"17\" end=\"18\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize thread=\"2\" tokenset=\"47\">\n" +
    "    <next state=\"48\" offset=\"18\" char=\"&lt;\" codepoint=\"60\" class=\"19\"/>\n" +
    "    <next state=\"80\" offset=\"19\" char=\"?\" codepoint=\"63\" class=\"22\" result=\"'&lt;?'\"/>\n" +
    "    <next state=\"89\" offset=\"20\" char=\"a\" codepoint=\"97\" class=\"23\"/>\n" +
    "    <done result=\"'&lt;?'\" begin=\"18\" end=\"20\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"2\" offset=\"17\" state=\"10\" input=\"'&lt;?'\" action=\"reduce\" nonterminal=\"NameOrString\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"17\" state=\"8\" input=\"NameOrString '&lt;?'\" action=\"shift reduce\" nonterminal=\"SyntaxPrimary\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"17\" state=\"8\" input=\"SyntaxPrimary '&lt;?'\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"17\" state=\"42\" input=\"'&lt;?'\" action=\"reduce\" nonterminal=\"SyntaxItem\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"17\" state=\"8\" input=\"SyntaxItem '&lt;?'\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"17\" state=\"13\" input=\"'&lt;?'\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"0\">\n" +
    "    <next state=\"1\" offset=\"20\" char=\"a\" codepoint=\"97\" class=\"23\" result=\"Name\"/>\n" +
    "    <next state=\"50\" offset=\"21\" char=\" \" codepoint=\"32\" class=\"3\"/>\n" +
    "    <done result=\"Name\" begin=\"20\" end=\"21\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"2\" offset=\"20\" state=\"34\" input=\"Name\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"10\">\n" +
    "    <next state=\"11\" offset=\"21\" char=\" \" codepoint=\"32\" class=\"3\" result=\"Space\"/>\n" +
    "    <next state=\"56\" offset=\"22\" char=\"/\" codepoint=\"47\" class=\"16\"/>\n" +
    "    <done result=\"Space\" begin=\"21\" end=\"22\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"2\" offset=\"21\" state=\"36\" input=\"Space\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"20\">\n" +
    "    <next state=\"21\" offset=\"22\" char=\"/\" codepoint=\"47\" class=\"16\"/>\n" +
    "    <next state=\"65\" offset=\"23\" char=\"*\" codepoint=\"42\" class=\"12\"/>\n" +
    "    <next state=\"65\" offset=\"24\" char=\"A\" codepoint=\"65\" class=\"23\"/>\n" +
    "    <next state=\"65\" offset=\"25\" char=\"*\" codepoint=\"42\" class=\"12\"/>\n" +
    "    <next state=\"65\" offset=\"26\" char=\"/\" codepoint=\"47\" class=\"16\"/>\n" +
    "    <next state=\"65\" offset=\"27\" char=\"?\" codepoint=\"63\" class=\"22\"/>\n" +
    "    <next state=\"85\" offset=\"28\" char=\">\" codepoint=\"62\" class=\"21\" result=\"DirPIContents\" trailing-context-size=\"2\"/>\n" +
    "    <done result=\"DirPIContents\" begin=\"22\" end=\"27\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"2\" offset=\"22\" state=\"38\" input=\"DirPIContents\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"2\">\n" +
    "    <next state=\"3\" offset=\"27\" char=\"?\" codepoint=\"63\" class=\"22\"/>\n" +
    "    <next state=\"51\" offset=\"28\" char=\">\" codepoint=\"62\" class=\"21\" result=\"'?>'\"/>\n" +
    "    <done result=\"'?>'\" begin=\"27\" end=\"29\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"2\" offset=\"27\" state=\"43\" input=\"'?>'\" action=\"shift reduce\" nonterminal=\"ProcessingInstruction\" count=\"5\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"13\" input=\"ProcessingInstruction\" action=\"shift reduce\" nonterminal=\"SyntaxPrimary\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"13\" input=\"SyntaxPrimary\" action=\"shift\"/>\n" +
    "  <tokenize thread=\"2\" tokenset=\"43\">\n" +
    "    <next state=\"44\" offset=\"29\" codepoint=\"0\" class=\"52\" result=\"EOF\"/>\n" +
    "    <done result=\"EOF\" begin=\"29\" end=\"29\"/>\n" +
    "  </tokenize>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"42\" input=\"EOF\" action=\"reduce\" nonterminal=\"SyntaxItem\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"13\" input=\"SyntaxItem EOF\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"13\" input=\"EOF\" action=\"reduce\" nonterminal=\"SyntaxSequence\" count=\"2\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"8\" input=\"SyntaxSequence EOF\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"41\" input=\"EOF\" action=\"reduce\" nonterminal=\"SyntaxChoice\" count=\"1\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"8\" input=\"SyntaxChoice EOF\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"12\" input=\"EOF\" action=\"reduce\" nonterminal=\"SyntaxProduction\" count=\"3\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"4\" input=\"SyntaxProduction EOF\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"4\" input=\"EOF\" action=\"reduce\" nonterminal=\"SyntaxDefinition\" count=\"2\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"1\" input=\"SyntaxDefinition EOF\" action=\"shift\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"3\" input=\"EOF\" action=\"shift reduce\" nonterminal=\"Grammar\" count=\"3\"/>\n" +
    "  <parse thread=\"2\" offset=\"29\" state=\"0\" input=\"Grammar\" action=\"accept\"/>\n" +
    "</trace>\n";
}
