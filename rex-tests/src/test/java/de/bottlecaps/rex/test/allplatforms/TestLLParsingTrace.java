package de.bottlecaps.rex.test.allplatforms;

import java.io.IOException;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithTrace;

public class TestLLParsingTrace extends RExExecutionWithTrace
{
  @BeforeEach
  public void before() throws IOException
  {
    init
    (
      "-trace -name XQuery31",
      "test.xq",
      new NamedFile("REC-xquery-31-20170321.ebnf"),
      new NamedFile
      (
        "test.xq",
        "declare default function namespace \'http://www.w3.org/2005/xpath-functions\'; <x><element>;-)</element></x>/(let $e := element let (:\uD83D\uDE09:) {';-('} let $f := element let(:(::):)$g := concat($e, $f) return $g)"
      )
    );
    expectedStdout = XML_DECLARATION;
    expectedStderr = TRACE;
  }

  private static final String TRACE =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
    "<trace>\n" +
    "  <parse startnonterminal=\"XQuery\"/>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"0\" char=\"d\" codepoint=\"100\" class=\"44\"/>\n" +
    "    <next state=\"403\" offset=\"1\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"648\" offset=\"2\" char=\"c\" codepoint=\"99\" class=\"43\"/>\n" +
    "    <next state=\"899\" offset=\"3\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"1128\" offset=\"4\" char=\"a\" codepoint=\"97\" class=\"41\"/>\n" +
    "    <next state=\"1321\" offset=\"5\" char=\"r\" codepoint=\"114\" class=\"56\"/>\n" +
    "    <next state=\"1462\" offset=\"6\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"1573\" offset=\"7\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'declare'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'declare'\" begin=\"0\" end=\"7\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"Module\" input=\"'declare'\"/>\n" +
    "  <parse startnonterminal=\"MainModule\" input=\"'declare'\"/>\n" +
    "  <parse startnonterminal=\"Prolog\" input=\"'declare'\"/>\n" +
    "  <tokenize tokenset=\"148\">\n" +
    "    <next state=\"149\" offset=\"7\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"8\" char=\"d\" codepoint=\"100\" class=\"44\"/>\n" +
    "    <done result=\"S\" begin=\"7\" end=\"8\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"148\">\n" +
    "    <next state=\"149\" offset=\"8\" char=\"d\" codepoint=\"100\" class=\"44\"/>\n" +
    "    <next state=\"356\" offset=\"9\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"468\" offset=\"10\" char=\"f\" codepoint=\"102\" class=\"46\"/>\n" +
    "    <next state=\"714\" offset=\"11\" char=\"a\" codepoint=\"97\" class=\"41\"/>\n" +
    "    <next state=\"966\" offset=\"12\" char=\"u\" codepoint=\"117\" class=\"59\"/>\n" +
    "    <next state=\"1181\" offset=\"13\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"1361\" offset=\"14\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"1496\" offset=\"15\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'default'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'default'\" begin=\"8\" end=\"15\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"122\">\n" +
    "    <next state=\"123\" offset=\"15\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"16\" char=\"f\" codepoint=\"102\" class=\"46\"/>\n" +
    "    <done result=\"S\" begin=\"15\" end=\"16\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"122\">\n" +
    "    <next state=\"123\" offset=\"16\" char=\"f\" codepoint=\"102\" class=\"46\"/>\n" +
    "    <next state=\"254\" offset=\"17\" char=\"u\" codepoint=\"117\" class=\"59\"/>\n" +
    "    <next state=\"464\" offset=\"18\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"729\" offset=\"19\" char=\"c\" codepoint=\"99\" class=\"43\"/>\n" +
    "    <next state=\"980\" offset=\"20\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"1192\" offset=\"21\" char=\"i\" codepoint=\"105\" class=\"49\"/>\n" +
    "    <next state=\"1370\" offset=\"22\" char=\"o\" codepoint=\"111\" class=\"53\"/>\n" +
    "    <next state=\"1500\" offset=\"23\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"1600\" offset=\"24\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'function'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'function'\" begin=\"16\" end=\"24\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"DefaultNamespaceDecl\" input=\"'declare' 'default' 'function'\"/>\n" +
    "  <parse terminal=\"'declare'\" input=\"'default' 'function'\"/>\n" +
    "  <parse terminal=\"'default'\" input=\"'function'\"/>\n" +
    "  <parse terminal=\"'function'\"/>\n" +
    "  <tokenize tokenset=\"50\">\n" +
    "    <next state=\"51\" offset=\"24\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"25\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <done result=\"S\" begin=\"24\" end=\"25\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"50\">\n" +
    "    <next state=\"51\" offset=\"25\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"241\" offset=\"26\" char=\"a\" codepoint=\"97\" class=\"41\"/>\n" +
    "    <next state=\"452\" offset=\"27\" char=\"m\" codepoint=\"109\" class=\"51\"/>\n" +
    "    <next state=\"720\" offset=\"28\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"971\" offset=\"29\" char=\"s\" codepoint=\"115\" class=\"57\"/>\n" +
    "    <next state=\"1185\" offset=\"30\" char=\"p\" codepoint=\"112\" class=\"54\"/>\n" +
    "    <next state=\"1364\" offset=\"31\" char=\"a\" codepoint=\"97\" class=\"41\"/>\n" +
    "    <next state=\"1498\" offset=\"32\" char=\"c\" codepoint=\"99\" class=\"43\"/>\n" +
    "    <next state=\"1598\" offset=\"33\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"1684\" offset=\"34\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'namespace'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'namespace'\" begin=\"25\" end=\"34\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"'namespace'\"/>\n" +
    "  <tokenize tokenset=\"19\">\n" +
    "    <next state=\"20\" offset=\"34\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"35\" char=\"'\" codepoint=\"39\" class=\"8\"/>\n" +
    "    <done result=\"S\" begin=\"34\" end=\"35\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"19\">\n" +
    "    <next state=\"20\" offset=\"35\" char=\"'\" codepoint=\"39\" class=\"8\"/>\n" +
    "    <next state=\"219\" offset=\"36\" char=\"h\" codepoint=\"104\" class=\"48\"/>\n" +
    "    <next state=\"219\" offset=\"37\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"219\" offset=\"38\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"219\" offset=\"39\" char=\"p\" codepoint=\"112\" class=\"54\"/>\n" +
    "    <next state=\"219\" offset=\"40\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"219\" offset=\"41\" char=\"/\" codepoint=\"47\" class=\"16\"/>\n" +
    "    <next state=\"219\" offset=\"42\" char=\"/\" codepoint=\"47\" class=\"16\"/>\n" +
    "    <next state=\"219\" offset=\"43\" char=\"w\" codepoint=\"119\" class=\"61\"/>\n" +
    "    <next state=\"219\" offset=\"44\" char=\"w\" codepoint=\"119\" class=\"61\"/>\n" +
    "    <next state=\"219\" offset=\"45\" char=\"w\" codepoint=\"119\" class=\"61\"/>\n" +
    "    <next state=\"219\" offset=\"46\" char=\".\" codepoint=\"46\" class=\"15\"/>\n" +
    "    <next state=\"219\" offset=\"47\" char=\"w\" codepoint=\"119\" class=\"61\"/>\n" +
    "    <next state=\"219\" offset=\"48\" char=\"3\" codepoint=\"51\" class=\"17\"/>\n" +
    "    <next state=\"219\" offset=\"49\" char=\".\" codepoint=\"46\" class=\"15\"/>\n" +
    "    <next state=\"219\" offset=\"50\" char=\"o\" codepoint=\"111\" class=\"53\"/>\n" +
    "    <next state=\"219\" offset=\"51\" char=\"r\" codepoint=\"114\" class=\"56\"/>\n" +
    "    <next state=\"219\" offset=\"52\" char=\"g\" codepoint=\"103\" class=\"47\"/>\n" +
    "    <next state=\"219\" offset=\"53\" char=\"/\" codepoint=\"47\" class=\"16\"/>\n" +
    "    <next state=\"219\" offset=\"54\" char=\"2\" codepoint=\"50\" class=\"17\"/>\n" +
    "    <next state=\"219\" offset=\"55\" char=\"0\" codepoint=\"48\" class=\"17\"/>\n" +
    "    <next state=\"219\" offset=\"56\" char=\"0\" codepoint=\"48\" class=\"17\"/>\n" +
    "    <next state=\"219\" offset=\"57\" char=\"5\" codepoint=\"53\" class=\"17\"/>\n" +
    "    <next state=\"219\" offset=\"58\" char=\"/\" codepoint=\"47\" class=\"16\"/>\n" +
    "    <next state=\"219\" offset=\"59\" char=\"x\" codepoint=\"120\" class=\"62\"/>\n" +
    "    <next state=\"219\" offset=\"60\" char=\"p\" codepoint=\"112\" class=\"54\"/>\n" +
    "    <next state=\"219\" offset=\"61\" char=\"a\" codepoint=\"97\" class=\"41\"/>\n" +
    "    <next state=\"219\" offset=\"62\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"219\" offset=\"63\" char=\"h\" codepoint=\"104\" class=\"48\"/>\n" +
    "    <next state=\"219\" offset=\"64\" char=\"-\" codepoint=\"45\" class=\"14\"/>\n" +
    "    <next state=\"219\" offset=\"65\" char=\"f\" codepoint=\"102\" class=\"46\"/>\n" +
    "    <next state=\"219\" offset=\"66\" char=\"u\" codepoint=\"117\" class=\"59\"/>\n" +
    "    <next state=\"219\" offset=\"67\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"219\" offset=\"68\" char=\"c\" codepoint=\"99\" class=\"43\"/>\n" +
    "    <next state=\"219\" offset=\"69\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"219\" offset=\"70\" char=\"i\" codepoint=\"105\" class=\"49\"/>\n" +
    "    <next state=\"219\" offset=\"71\" char=\"o\" codepoint=\"111\" class=\"53\"/>\n" +
    "    <next state=\"219\" offset=\"72\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"219\" offset=\"73\" char=\"s\" codepoint=\"115\" class=\"57\"/>\n" +
    "    <next state=\"219\" offset=\"74\" char=\"'\" codepoint=\"39\" class=\"8\" result=\"StringLiteral\"/>\n" +
    "    <next state=\"433\" offset=\"75\" char=\";\" codepoint=\"59\" class=\"19\"/>\n" +
    "    <done result=\"StringLiteral\" begin=\"35\" end=\"75\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"URILiteral\" input=\"StringLiteral\"/>\n" +
    "  <parse terminal=\"StringLiteral\"/>\n" +
    "  <parse endnonterminal=\"URILiteral\"/>\n" +
    "  <parse endnonterminal=\"DefaultNamespaceDecl\"/>\n" +
    "  <tokenize tokenset=\"30\">\n" +
    "    <next state=\"31\" offset=\"75\" char=\";\" codepoint=\"59\" class=\"19\" result=\"';'\"/>\n" +
    "    <done result=\"';'\" begin=\"75\" end=\"76\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"Separator\" input=\"';'\"/>\n" +
    "  <parse terminal=\"';'\"/>\n" +
    "  <parse endnonterminal=\"Separator\"/>\n" +
    "  <tokenize tokenset=\"190\">\n" +
    "    <next state=\"191\" offset=\"76\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"77\" char=\"&lt;\" codepoint=\"60\" class=\"20\"/>\n" +
    "    <done result=\"S\" begin=\"76\" end=\"77\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"190\">\n" +
    "    <next state=\"191\" offset=\"77\" char=\"&lt;\" codepoint=\"60\" class=\"20\" result=\"'&lt;'\"/>\n" +
    "    <next state=\"421\" offset=\"78\" char=\"x\" codepoint=\"120\" class=\"62\"/>\n" +
    "    <done result=\"'&lt;'\" begin=\"77\" end=\"78\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"Prolog\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"QueryBody\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"Expr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"NodeConstructor\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"DirectConstructor\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"DirElemConstructor\" input=\"'&lt;'\"/>\n" +
    "  <parse terminal=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"QName\"/>\n" +
    "  <tokenize tokenset=\"171\">\n" +
    "    <next state=\"172\" offset=\"78\" char=\"x\" codepoint=\"120\" class=\"62\"/>\n" +
    "    <next state=\"396\" offset=\"79\" char=\">\" codepoint=\"62\" class=\"22\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"78\" end=\"79\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse startnonterminal=\"DirAttributeList\"/>\n" +
    "  <tokenize tokenset=\"21\">\n" +
    "    <next state=\"22\" offset=\"79\" char=\">\" codepoint=\"62\" class=\"22\" result=\"'>'\"/>\n" +
    "    <done result=\"'>'\" begin=\"79\" end=\"80\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"DirAttributeList\" input=\"'>'\"/>\n" +
    "  <parse terminal=\"'>'\"/>\n" +
    "  <tokenize tokenset=\"129\">\n" +
    "    <next state=\"130\" offset=\"80\" char=\"&lt;\" codepoint=\"60\" class=\"20\" result=\"'&lt;'\"/>\n" +
    "    <next state=\"298\" offset=\"81\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <done result=\"'&lt;'\" begin=\"80\" end=\"81\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"DirElemContent\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"DirectConstructor\" input=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"DirElemConstructor\" input=\"'&lt;'\"/>\n" +
    "  <parse terminal=\"'&lt;'\"/>\n" +
    "  <parse startnonterminal=\"QName\"/>\n" +
    "  <tokenize tokenset=\"171\">\n" +
    "    <next state=\"172\" offset=\"81\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"381\" offset=\"82\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"594\" offset=\"83\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"843\" offset=\"84\" char=\"m\" codepoint=\"109\" class=\"51\"/>\n" +
    "    <next state=\"1072\" offset=\"85\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"1271\" offset=\"86\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"1429\" offset=\"87\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"1552\" offset=\"88\" char=\">\" codepoint=\"62\" class=\"22\" result=\"'element'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'element'\" begin=\"81\" end=\"88\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"'element'\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse startnonterminal=\"DirAttributeList\"/>\n" +
    "  <tokenize tokenset=\"21\">\n" +
    "    <next state=\"22\" offset=\"88\" char=\">\" codepoint=\"62\" class=\"22\" result=\"'>'\"/>\n" +
    "    <done result=\"'>'\" begin=\"88\" end=\"89\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"DirAttributeList\" input=\"'>'\"/>\n" +
    "  <parse terminal=\"'>'\"/>\n" +
    "  <tokenize tokenset=\"129\">\n" +
    "    <next state=\"130\" offset=\"89\" char=\";\" codepoint=\"59\" class=\"19\" result=\"ElementContentChar\"/>\n" +
    "    <done result=\"ElementContentChar\" begin=\"89\" end=\"90\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"DirElemContent\" input=\"ElementContentChar\"/>\n" +
    "  <parse terminal=\"ElementContentChar\"/>\n" +
    "  <parse endnonterminal=\"DirElemContent\"/>\n" +
    "  <tokenize tokenset=\"129\">\n" +
    "    <next state=\"130\" offset=\"90\" char=\"-\" codepoint=\"45\" class=\"14\" result=\"ElementContentChar\"/>\n" +
    "    <done result=\"ElementContentChar\" begin=\"90\" end=\"91\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"DirElemContent\" input=\"ElementContentChar\"/>\n" +
    "  <parse terminal=\"ElementContentChar\"/>\n" +
    "  <parse endnonterminal=\"DirElemContent\"/>\n" +
    "  <tokenize tokenset=\"129\">\n" +
    "    <next state=\"130\" offset=\"91\" char=\")\" codepoint=\"41\" class=\"10\" result=\"ElementContentChar\"/>\n" +
    "    <done result=\"ElementContentChar\" begin=\"91\" end=\"92\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"DirElemContent\" input=\"ElementContentChar\"/>\n" +
    "  <parse terminal=\"ElementContentChar\"/>\n" +
    "  <parse endnonterminal=\"DirElemContent\"/>\n" +
    "  <tokenize tokenset=\"129\">\n" +
    "    <next state=\"130\" offset=\"92\" char=\"&lt;\" codepoint=\"60\" class=\"20\" result=\"'&lt;'\"/>\n" +
    "    <next state=\"298\" offset=\"93\" char=\"/\" codepoint=\"47\" class=\"16\" result=\"'&lt;/'\"/>\n" +
    "    <done result=\"'&lt;/'\" begin=\"92\" end=\"94\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"'&lt;/'\"/>\n" +
    "  <parse startnonterminal=\"QName\"/>\n" +
    "  <tokenize tokenset=\"171\">\n" +
    "    <next state=\"172\" offset=\"94\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"381\" offset=\"95\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"594\" offset=\"96\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"843\" offset=\"97\" char=\"m\" codepoint=\"109\" class=\"51\"/>\n" +
    "    <next state=\"1072\" offset=\"98\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"1271\" offset=\"99\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"1429\" offset=\"100\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"1552\" offset=\"101\" char=\">\" codepoint=\"62\" class=\"22\" result=\"'element'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'element'\" begin=\"94\" end=\"101\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"'element'\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <tokenize tokenset=\"14\">\n" +
    "    <next state=\"15\" offset=\"101\" char=\">\" codepoint=\"62\" class=\"22\" result=\"'>'\"/>\n" +
    "    <done result=\"'>'\" begin=\"101\" end=\"102\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"'>'\"/>\n" +
    "  <parse endnonterminal=\"DirElemConstructor\"/>\n" +
    "  <parse endnonterminal=\"DirectConstructor\"/>\n" +
    "  <parse endnonterminal=\"DirElemContent\"/>\n" +
    "  <tokenize tokenset=\"129\">\n" +
    "    <next state=\"130\" offset=\"102\" char=\"&lt;\" codepoint=\"60\" class=\"20\" result=\"'&lt;'\"/>\n" +
    "    <next state=\"298\" offset=\"103\" char=\"/\" codepoint=\"47\" class=\"16\" result=\"'&lt;/'\"/>\n" +
    "    <done result=\"'&lt;/'\" begin=\"102\" end=\"104\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"'&lt;/'\"/>\n" +
    "  <parse startnonterminal=\"QName\"/>\n" +
    "  <tokenize tokenset=\"171\">\n" +
    "    <next state=\"172\" offset=\"104\" char=\"x\" codepoint=\"120\" class=\"62\"/>\n" +
    "    <next state=\"396\" offset=\"105\" char=\">\" codepoint=\"62\" class=\"22\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"104\" end=\"105\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <tokenize tokenset=\"14\">\n" +
    "    <next state=\"15\" offset=\"105\" char=\">\" codepoint=\"62\" class=\"22\" result=\"'>'\"/>\n" +
    "    <done result=\"'>'\" begin=\"105\" end=\"106\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"'>'\"/>\n" +
    "  <parse endnonterminal=\"DirElemConstructor\"/>\n" +
    "  <parse endnonterminal=\"DirectConstructor\"/>\n" +
    "  <parse endnonterminal=\"NodeConstructor\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"106\" char=\"/\" codepoint=\"47\" class=\"16\" result=\"'/'\"/>\n" +
    "    <next state=\"333\" offset=\"107\" char=\"(\" codepoint=\"40\" class=\"9\"/>\n" +
    "    <done result=\"'/'\" begin=\"106\" end=\"107\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"'/'\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"'/'\"/>\n" +
    "  <parse terminal=\"'/'\"/>\n" +
    "  <tokenize tokenset=\"187\">\n" +
    "    <next state=\"188\" offset=\"107\" char=\"(\" codepoint=\"40\" class=\"9\" result=\"'('\"/>\n" +
    "    <next state=\"216\" offset=\"108\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <done result=\"'('\" begin=\"107\" end=\"108\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"'('\"/>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"'('\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"'('\"/>\n" +
    "  <parse startnonterminal=\"ParenthesizedExpr\" input=\"'('\"/>\n" +
    "  <parse terminal=\"'('\"/>\n" +
    "  <tokenize tokenset=\"191\">\n" +
    "    <next state=\"192\" offset=\"108\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"408\" offset=\"109\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"668\" offset=\"110\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"919\" offset=\"111\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'let'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'let'\" begin=\"108\" end=\"111\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"Expr\" input=\"'let'\"/>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"'let'\"/>\n" +
    "  <tokenize tokenset=\"165\">\n" +
    "    <next state=\"166\" offset=\"111\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"112\" char=\"$\" codepoint=\"36\" class=\"5\"/>\n" +
    "    <done result=\"S\" begin=\"111\" end=\"112\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"165\">\n" +
    "    <next state=\"166\" offset=\"112\" char=\"$\" codepoint=\"36\" class=\"5\" result=\"'$'\"/>\n" +
    "    <done result=\"'$'\" begin=\"112\" end=\"113\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"FLWORExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"InitialClause\" input=\"'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"LetClause\" input=\"'let' '$'\"/>\n" +
    "  <parse terminal=\"'let'\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"LetBinding\" input=\"'$'\"/>\n" +
    "  <parse terminal=\"'$'\"/>\n" +
    "  <tokenize tokenset=\"174\">\n" +
    "    <next state=\"175\" offset=\"113\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"381\" offset=\"114\" char=\" \" codepoint=\"32\" class=\"1\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"113\" end=\"114\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"VarName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"EQName\"/>\n" +
    "  <parse endnonterminal=\"VarName\"/>\n" +
    "  <tokenize tokenset=\"75\">\n" +
    "    <next state=\"76\" offset=\"114\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"115\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <done result=\"S\" begin=\"114\" end=\"115\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"75\">\n" +
    "    <next state=\"76\" offset=\"115\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"222\" offset=\"116\" char=\"=\" codepoint=\"61\" class=\"21\" result=\"':='\"/>\n" +
    "    <done result=\"':='\" begin=\"115\" end=\"117\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"':='\"/>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"117\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"118\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <done result=\"S\" begin=\"117\" end=\"118\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"118\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"404\" offset=\"119\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"651\" offset=\"120\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"904\" offset=\"121\" char=\"m\" codepoint=\"109\" class=\"51\"/>\n" +
    "    <next state=\"1132\" offset=\"122\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"1325\" offset=\"123\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"1466\" offset=\"124\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"1577\" offset=\"125\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'element'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'element'\" begin=\"118\" end=\"125\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"'element'\"/>\n" +
    "  <tokenize tokenset=\"196\">\n" +
    "    <next state=\"197\" offset=\"125\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"126\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <done result=\"S\" begin=\"125\" end=\"126\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"196\">\n" +
    "    <next state=\"197\" offset=\"126\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"385\" offset=\"127\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"611\" offset=\"128\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"858\" offset=\"129\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'let'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'let'\" begin=\"126\" end=\"129\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"68\">\n" +
    "    <next state=\"69\" offset=\"129\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"130\" char=\"(\" codepoint=\"40\" class=\"9\"/>\n" +
    "    <done result=\"S\" begin=\"129\" end=\"130\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"68\">\n" +
    "    <next state=\"69\" offset=\"130\" char=\"(\" codepoint=\"40\" class=\"9\"/>\n" +
    "    <next state=\"216\" offset=\"131\" char=\":\" codepoint=\"58\" class=\"18\" result=\"'(:'\"/>\n" +
    "    <done result=\"'(:'\" begin=\"130\" end=\"132\"/>\n" +
    "  </tokenize>\n" +
    "  <try startnonterminal=\"Whitespace\" input=\"'(:'\"/>\n" +
    "  <try startnonterminal=\"Comment\" input=\"'(:'\"/>\n" +
    "  <parse terminal=\"'(:'\"/>\n" +
    "  <tokenize tokenset=\"61\">\n" +
    "    <next state=\"62\" offset=\"132\" codepoint=\"128521\" class=\"30\"/>\n" +
    "    <next state=\"251\" offset=\"134\" char=\":\" codepoint=\"58\" class=\"18\" result=\"CommentContents\" trailing-context-size=\"1\"/>\n" +
    "    <next state=\"463\" offset=\"135\" char=\")\" codepoint=\"41\" class=\"10\"/>\n" +
    "    <done result=\"CommentContents\" begin=\"132\" end=\"134\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"CommentContents\"/>\n" +
    "  <tokenize tokenset=\"61\">\n" +
    "    <next state=\"62\" offset=\"134\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"253\" offset=\"135\" char=\")\" codepoint=\"41\" class=\"10\" result=\"':)'\"/>\n" +
    "    <done result=\"':)'\" begin=\"134\" end=\"136\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"':)'\"/>\n" +
    "  <try endnonterminal=\"Comment\"/>\n" +
    "  <try endnonterminal=\"Whitespace\"/>\n" +
    "  <tokenize tokenset=\"68\">\n" +
    "    <next state=\"69\" offset=\"136\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"137\" char=\"{\" codepoint=\"123\" class=\"65\"/>\n" +
    "    <done result=\"S\" begin=\"136\" end=\"137\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"68\">\n" +
    "    <next state=\"69\" offset=\"137\" char=\"{\" codepoint=\"123\" class=\"65\" result=\"'{'\"/>\n" +
    "    <done result=\"'{'\" begin=\"137\" end=\"138\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"'element' 'let' '{'\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"'element' 'let' '{'\"/>\n" +
    "  <parse startnonterminal=\"NodeConstructor\" input=\"'element' 'let' '{'\"/>\n" +
    "  <parse startnonterminal=\"ComputedConstructor\" input=\"'element' 'let' '{'\"/>\n" +
    "  <parse startnonterminal=\"CompElemConstructor\" input=\"'element' 'let' '{'\"/>\n" +
    "  <parse terminal=\"'element'\" input=\"'let' '{'\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"'let' '{'\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"'let' '{'\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"'let' '{'\"/>\n" +
    "  <parse terminal=\"'let'\" input=\"'{'\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\" input=\"'{'\"/>\n" +
    "  <parse endnonterminal=\"QName\" input=\"'{'\"/>\n" +
    "  <parse endnonterminal=\"EQName\" input=\"'{'\"/>\n" +
    "  <parse startnonterminal=\"EnclosedContentExpr\" input=\"'{'\"/>\n" +
    "  <parse startnonterminal=\"EnclosedExpr\" input=\"'{'\"/>\n" +
    "  <parse terminal=\"'{'\"/>\n" +
    "  <tokenize tokenset=\"194\">\n" +
    "    <next state=\"195\" offset=\"138\" char=\"'\" codepoint=\"39\" class=\"8\"/>\n" +
    "    <next state=\"219\" offset=\"139\" char=\";\" codepoint=\"59\" class=\"19\"/>\n" +
    "    <next state=\"219\" offset=\"140\" char=\"-\" codepoint=\"45\" class=\"14\"/>\n" +
    "    <next state=\"219\" offset=\"141\" char=\"(\" codepoint=\"40\" class=\"9\"/>\n" +
    "    <next state=\"219\" offset=\"142\" char=\"'\" codepoint=\"39\" class=\"8\" result=\"StringLiteral\"/>\n" +
    "    <next state=\"433\" offset=\"143\" char=\"}\" codepoint=\"125\" class=\"67\"/>\n" +
    "    <done result=\"StringLiteral\" begin=\"138\" end=\"143\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"Expr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"StringLiteral\"/>\n" +
    "  <parse startnonterminal=\"Literal\" input=\"StringLiteral\"/>\n" +
    "  <parse terminal=\"StringLiteral\"/>\n" +
    "  <parse endnonterminal=\"Literal\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"143\" char=\"}\" codepoint=\"125\" class=\"67\" result=\"'}'\"/>\n" +
    "    <next state=\"314\" offset=\"144\" char=\" \" codepoint=\"32\" class=\"1\"/>\n" +
    "    <done result=\"'}'\" begin=\"143\" end=\"144\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"Expr\" input=\"'}'\"/>\n" +
    "  <parse terminal=\"'}'\"/>\n" +
    "  <parse endnonterminal=\"EnclosedExpr\"/>\n" +
    "  <parse endnonterminal=\"EnclosedContentExpr\"/>\n" +
    "  <parse endnonterminal=\"CompElemConstructor\"/>\n" +
    "  <parse endnonterminal=\"ComputedConstructor\"/>\n" +
    "  <parse endnonterminal=\"NodeConstructor\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"144\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"145\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <done result=\"S\" begin=\"144\" end=\"145\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"145\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"364\" offset=\"146\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"576\" offset=\"147\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"765\" offset=\"148\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'let'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'let'\" begin=\"145\" end=\"148\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"LetBinding\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"LetClause\" input=\"'let'\"/>\n" +
    "  <parse endnonterminal=\"InitialClause\" input=\"'let'\"/>\n" +
    "  <parse startnonterminal=\"IntermediateClause\" input=\"'let'\"/>\n" +
    "  <parse startnonterminal=\"InitialClause\" input=\"'let'\"/>\n" +
    "  <parse startnonterminal=\"LetClause\" input=\"'let'\"/>\n" +
    "  <parse terminal=\"'let'\"/>\n" +
    "  <tokenize tokenset=\"23\">\n" +
    "    <next state=\"24\" offset=\"148\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"149\" char=\"$\" codepoint=\"36\" class=\"5\"/>\n" +
    "    <done result=\"S\" begin=\"148\" end=\"149\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"23\">\n" +
    "    <next state=\"24\" offset=\"149\" char=\"$\" codepoint=\"36\" class=\"5\" result=\"'$'\"/>\n" +
    "    <done result=\"'$'\" begin=\"149\" end=\"150\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"LetBinding\" input=\"'$'\"/>\n" +
    "  <parse terminal=\"'$'\"/>\n" +
    "  <tokenize tokenset=\"174\">\n" +
    "    <next state=\"175\" offset=\"150\" char=\"f\" codepoint=\"102\" class=\"46\"/>\n" +
    "    <next state=\"382\" offset=\"151\" char=\" \" codepoint=\"32\" class=\"1\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"150\" end=\"151\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"VarName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"EQName\"/>\n" +
    "  <parse endnonterminal=\"VarName\"/>\n" +
    "  <tokenize tokenset=\"75\">\n" +
    "    <next state=\"76\" offset=\"151\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"152\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <done result=\"S\" begin=\"151\" end=\"152\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"75\">\n" +
    "    <next state=\"76\" offset=\"152\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"222\" offset=\"153\" char=\"=\" codepoint=\"61\" class=\"21\" result=\"':='\"/>\n" +
    "    <done result=\"':='\" begin=\"152\" end=\"154\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"':='\"/>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"154\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"155\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <done result=\"S\" begin=\"154\" end=\"155\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"155\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"404\" offset=\"156\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"651\" offset=\"157\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"904\" offset=\"158\" char=\"m\" codepoint=\"109\" class=\"51\"/>\n" +
    "    <next state=\"1132\" offset=\"159\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"1325\" offset=\"160\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"1466\" offset=\"161\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"1577\" offset=\"162\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'element'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'element'\" begin=\"155\" end=\"162\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"'element'\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"'element'\"/>\n" +
    "  <tokenize tokenset=\"196\">\n" +
    "    <next state=\"197\" offset=\"162\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"163\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <done result=\"S\" begin=\"162\" end=\"163\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"196\">\n" +
    "    <next state=\"197\" offset=\"163\" char=\"l\" codepoint=\"108\" class=\"50\"/>\n" +
    "    <next state=\"385\" offset=\"164\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"611\" offset=\"165\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"858\" offset=\"166\" char=\"(\" codepoint=\"40\" class=\"9\" result=\"'let'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'let'\" begin=\"163\" end=\"166\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"68\">\n" +
    "    <next state=\"69\" offset=\"166\" char=\"(\" codepoint=\"40\" class=\"9\"/>\n" +
    "    <next state=\"216\" offset=\"167\" char=\":\" codepoint=\"58\" class=\"18\" result=\"'(:'\"/>\n" +
    "    <done result=\"'(:'\" begin=\"166\" end=\"168\"/>\n" +
    "  </tokenize>\n" +
    "  <try startnonterminal=\"Whitespace\" input=\"'(:'\"/>\n" +
    "  <try startnonterminal=\"Comment\" input=\"'(:'\"/>\n" +
    "  <parse terminal=\"'(:'\"/>\n" +
    "  <tokenize tokenset=\"61\">\n" +
    "    <next state=\"62\" offset=\"168\" char=\"(\" codepoint=\"40\" class=\"9\"/>\n" +
    "    <next state=\"252\" offset=\"169\" char=\":\" codepoint=\"58\" class=\"18\" result=\"'(:'\"/>\n" +
    "    <done result=\"'(:'\" begin=\"168\" end=\"170\"/>\n" +
    "  </tokenize>\n" +
    "  <try startnonterminal=\"Comment\" input=\"'(:'\"/>\n" +
    "  <parse terminal=\"'(:'\"/>\n" +
    "  <tokenize tokenset=\"61\">\n" +
    "    <next state=\"62\" offset=\"170\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"253\" offset=\"171\" char=\")\" codepoint=\"41\" class=\"10\" result=\"':)'\"/>\n" +
    "    <done result=\"':)'\" begin=\"170\" end=\"172\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"':)'\"/>\n" +
    "  <try endnonterminal=\"Comment\"/>\n" +
    "  <tokenize tokenset=\"61\">\n" +
    "    <next state=\"62\" offset=\"172\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"253\" offset=\"173\" char=\")\" codepoint=\"41\" class=\"10\" result=\"':)'\"/>\n" +
    "    <done result=\"':)'\" begin=\"172\" end=\"174\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"':)'\"/>\n" +
    "  <try endnonterminal=\"Comment\"/>\n" +
    "  <try endnonterminal=\"Whitespace\"/>\n" +
    "  <tokenize tokenset=\"68\">\n" +
    "    <next state=\"69\" offset=\"174\" char=\"$\" codepoint=\"36\" class=\"5\" result=\"'$'\"/>\n" +
    "    <done result=\"'$'\" begin=\"174\" end=\"175\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"AxisStep\" input=\"'element' 'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"ForwardStep\" input=\"'element' 'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"AbbrevForwardStep\" input=\"'element' 'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"NodeTest\" input=\"'element' 'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"NameTest\" input=\"'element' 'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"'element' 'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"'element' 'let' '$'\"/>\n" +
    "  <parse terminal=\"'element'\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"QName\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"EQName\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"NameTest\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"NodeTest\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"AbbrevForwardStep\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"ForwardStep\" input=\"'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"PredicateList\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"PredicateList\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"AxisStep\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"LetBinding\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"LetClause\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"InitialClause\" input=\"'let' '$'\"/>\n" +
    "  <parse endnonterminal=\"IntermediateClause\" input=\"'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"IntermediateClause\" input=\"'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"InitialClause\" input=\"'let' '$'\"/>\n" +
    "  <parse startnonterminal=\"LetClause\" input=\"'let' '$'\"/>\n" +
    "  <parse terminal=\"'let'\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"LetBinding\" input=\"'$'\"/>\n" +
    "  <parse terminal=\"'$'\"/>\n" +
    "  <tokenize tokenset=\"174\">\n" +
    "    <next state=\"175\" offset=\"175\" char=\"g\" codepoint=\"103\" class=\"47\"/>\n" +
    "    <next state=\"383\" offset=\"176\" char=\" \" codepoint=\"32\" class=\"1\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"175\" end=\"176\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"VarName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"EQName\"/>\n" +
    "  <parse endnonterminal=\"VarName\"/>\n" +
    "  <tokenize tokenset=\"75\">\n" +
    "    <next state=\"76\" offset=\"176\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"177\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <done result=\"S\" begin=\"176\" end=\"177\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"75\">\n" +
    "    <next state=\"76\" offset=\"177\" char=\":\" codepoint=\"58\" class=\"18\"/>\n" +
    "    <next state=\"222\" offset=\"178\" char=\"=\" codepoint=\"61\" class=\"21\" result=\"':='\"/>\n" +
    "    <done result=\"':='\" begin=\"177\" end=\"179\"/>\n" +
    "  </tokenize>\n" +
    "  <parse terminal=\"':='\"/>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"179\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"180\" char=\"c\" codepoint=\"99\" class=\"43\"/>\n" +
    "    <done result=\"S\" begin=\"179\" end=\"180\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"180\" char=\"c\" codepoint=\"99\" class=\"43\"/>\n" +
    "    <next state=\"402\" offset=\"181\" char=\"o\" codepoint=\"111\" class=\"53\"/>\n" +
    "    <next state=\"647\" offset=\"182\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"399\" offset=\"183\" char=\"c\" codepoint=\"99\" class=\"43\"/>\n" +
    "    <next state=\"399\" offset=\"184\" char=\"a\" codepoint=\"97\" class=\"41\"/>\n" +
    "    <next state=\"399\" offset=\"185\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"399\" offset=\"186\" char=\"(\" codepoint=\"40\" class=\"9\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"180\" end=\"186\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"QName\"/>\n" +
    "  <tokenize tokenset=\"161\">\n" +
    "    <next state=\"162\" offset=\"186\" char=\"(\" codepoint=\"40\" class=\"9\" result=\"'('\"/>\n" +
    "    <next state=\"216\" offset=\"187\" char=\"$\" codepoint=\"36\" class=\"5\"/>\n" +
    "    <done result=\"'('\" begin=\"186\" end=\"187\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"QName '('\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"QName '('\"/>\n" +
    "  <parse startnonterminal=\"FunctionCall\" input=\"QName '('\"/>\n" +
    "  <parse startnonterminal=\"FunctionEQName\" input=\"QName '('\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName '('\"/>\n" +
    "  <parse terminal=\"QName\" input=\"'('\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\" input=\"'('\"/>\n" +
    "  <parse endnonterminal=\"FunctionEQName\" input=\"'('\"/>\n" +
    "  <parse startnonterminal=\"ArgumentList\" input=\"'('\"/>\n" +
    "  <parse terminal=\"'('\"/>\n" +
    "  <tokenize tokenset=\"191\">\n" +
    "    <next state=\"192\" offset=\"187\" char=\"$\" codepoint=\"36\" class=\"5\" result=\"'$'\"/>\n" +
    "    <done result=\"'$'\" begin=\"187\" end=\"188\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"Argument\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"VarRef\" input=\"'$'\"/>\n" +
    "  <parse terminal=\"'$'\"/>\n" +
    "  <tokenize tokenset=\"174\">\n" +
    "    <next state=\"175\" offset=\"188\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"381\" offset=\"189\" char=\",\" codepoint=\"44\" class=\"13\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"188\" end=\"189\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"VarName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"EQName\"/>\n" +
    "  <parse endnonterminal=\"VarName\"/>\n" +
    "  <parse endnonterminal=\"VarRef\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"189\" char=\",\" codepoint=\"44\" class=\"13\" result=\"','\"/>\n" +
    "    <done result=\"','\" begin=\"189\" end=\"190\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"','\"/>\n" +
    "  <parse endnonterminal=\"Argument\" input=\"','\"/>\n" +
    "  <parse terminal=\"','\"/>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"190\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"191\" char=\"$\" codepoint=\"36\" class=\"5\"/>\n" +
    "    <done result=\"S\" begin=\"190\" end=\"191\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"191\" char=\"$\" codepoint=\"36\" class=\"5\" result=\"'$'\"/>\n" +
    "    <done result=\"'$'\" begin=\"191\" end=\"192\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"Argument\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"VarRef\" input=\"'$'\"/>\n" +
    "  <parse terminal=\"'$'\"/>\n" +
    "  <tokenize tokenset=\"174\">\n" +
    "    <next state=\"175\" offset=\"192\" char=\"f\" codepoint=\"102\" class=\"46\"/>\n" +
    "    <next state=\"382\" offset=\"193\" char=\")\" codepoint=\"41\" class=\"10\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"192\" end=\"193\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"VarName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"EQName\"/>\n" +
    "  <parse endnonterminal=\"VarName\"/>\n" +
    "  <parse endnonterminal=\"VarRef\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"193\" char=\")\" codepoint=\"41\" class=\"10\" result=\"')'\"/>\n" +
    "    <done result=\"')'\" begin=\"193\" end=\"194\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"Argument\" input=\"')'\"/>\n" +
    "  <parse terminal=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ArgumentList\"/>\n" +
    "  <parse endnonterminal=\"FunctionCall\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"194\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"195\" char=\"r\" codepoint=\"114\" class=\"56\"/>\n" +
    "    <done result=\"S\" begin=\"194\" end=\"195\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"195\" char=\"r\" codepoint=\"114\" class=\"56\"/>\n" +
    "    <next state=\"246\" offset=\"196\" char=\"e\" codepoint=\"101\" class=\"45\"/>\n" +
    "    <next state=\"457\" offset=\"197\" char=\"t\" codepoint=\"116\" class=\"58\"/>\n" +
    "    <next state=\"724\" offset=\"198\" char=\"u\" codepoint=\"117\" class=\"59\"/>\n" +
    "    <next state=\"975\" offset=\"199\" char=\"r\" codepoint=\"114\" class=\"56\"/>\n" +
    "    <next state=\"1189\" offset=\"200\" char=\"n\" codepoint=\"110\" class=\"52\"/>\n" +
    "    <next state=\"1367\" offset=\"201\" char=\" \" codepoint=\"32\" class=\"1\" result=\"'return'\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"'return'\" begin=\"195\" end=\"201\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"LetBinding\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"LetClause\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"InitialClause\" input=\"'return'\"/>\n" +
    "  <parse endnonterminal=\"IntermediateClause\" input=\"'return'\"/>\n" +
    "  <parse startnonterminal=\"ReturnClause\" input=\"'return'\"/>\n" +
    "  <parse terminal=\"'return'\"/>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"201\" char=\" \" codepoint=\"32\" class=\"1\" result=\"S\"/>\n" +
    "    <next state=\"215\" offset=\"202\" char=\"$\" codepoint=\"36\" class=\"5\"/>\n" +
    "    <done result=\"S\" begin=\"201\" end=\"202\"/>\n" +
    "  </tokenize>\n" +
    "  <tokenize tokenset=\"189\">\n" +
    "    <next state=\"190\" offset=\"202\" char=\"$\" codepoint=\"36\" class=\"5\" result=\"'$'\"/>\n" +
    "    <done result=\"'$'\" begin=\"202\" end=\"203\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"ExprSingle\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"OrExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"AndExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ComparisonExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"StringConcatExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"RangeExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"AdditiveExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"MultiplicativeExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"UnionExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"IntersectExceptExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"InstanceofExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"TreatExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"CastableExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"CastExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ArrowExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"UnaryExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"ValueExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"SimpleMapExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PathExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"RelativePathExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"StepExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PostfixExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"PrimaryExpr\" input=\"'$'\"/>\n" +
    "  <parse startnonterminal=\"VarRef\" input=\"'$'\"/>\n" +
    "  <parse terminal=\"'$'\"/>\n" +
    "  <tokenize tokenset=\"174\">\n" +
    "    <next state=\"175\" offset=\"203\" char=\"g\" codepoint=\"103\" class=\"47\"/>\n" +
    "    <next state=\"383\" offset=\"204\" char=\")\" codepoint=\"41\" class=\"10\" result=\"QName\" trailing-context-size=\"1\"/>\n" +
    "    <done result=\"QName\" begin=\"203\" end=\"204\"/>\n" +
    "  </tokenize>\n" +
    "  <parse startnonterminal=\"VarName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"EQName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"QName\" input=\"QName\"/>\n" +
    "  <parse startnonterminal=\"FunctionName\" input=\"QName\"/>\n" +
    "  <parse terminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"FunctionName\"/>\n" +
    "  <parse endnonterminal=\"QName\"/>\n" +
    "  <parse endnonterminal=\"EQName\"/>\n" +
    "  <parse endnonterminal=\"VarName\"/>\n" +
    "  <parse endnonterminal=\"VarRef\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"204\" char=\")\" codepoint=\"41\" class=\"10\" result=\"')'\"/>\n" +
    "    <done result=\"')'\" begin=\"204\" end=\"205\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ReturnClause\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"FLWORExpr\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"')'\"/>\n" +
    "  <parse endnonterminal=\"Expr\" input=\"')'\"/>\n" +
    "  <parse terminal=\"')'\"/>\n" +
    "  <parse endnonterminal=\"ParenthesizedExpr\"/>\n" +
    "  <parse endnonterminal=\"PrimaryExpr\"/>\n" +
    "  <tokenize tokenset=\"164\">\n" +
    "    <next state=\"165\" offset=\"205\" codepoint=\"0\" class=\"69\" result=\"EOF\"/>\n" +
    "    <done result=\"EOF\" begin=\"205\" end=\"205\"/>\n" +
    "  </tokenize>\n" +
    "  <parse endnonterminal=\"PostfixExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"StepExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"RelativePathExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"PathExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"SimpleMapExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"ValueExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"UnaryExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"ArrowExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"CastExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"CastableExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"TreatExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"InstanceofExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"IntersectExceptExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"UnionExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"MultiplicativeExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"AdditiveExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"RangeExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"StringConcatExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"ComparisonExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"AndExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"OrExpr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"ExprSingle\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"Expr\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"QueryBody\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"MainModule\" input=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"Module\" input=\"EOF\"/>\n" +
    "  <parse terminal=\"EOF\"/>\n" +
    "  <parse endnonterminal=\"XQuery\"/>\n" +
    "</trace>\n";
  }
