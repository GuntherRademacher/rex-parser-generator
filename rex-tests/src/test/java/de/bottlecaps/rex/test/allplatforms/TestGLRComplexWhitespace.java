package de.bottlecaps.rex.test.allplatforms;

import org.junit.jupiter.api.BeforeEach;

import de.bottlecaps.rex.test.base.RExExecutionWithResult;

public class TestGLRComplexWhitespace extends RExExecutionWithResult
{
  @BeforeEach
  public void before()
  {
    init
    (
      "-glalr 1 -tree -name XQ",
      "{41(:(::):)+1}",
      new NamedFile("REC-xquery-31-20170321.ebnf")
    );
    expectedStdout = TREE;
  }

  private static final String TREE =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?><XQuery><Module><MainModule><Prolog/><QueryBody><Expr><ExprSingle><OrExpr><AndExpr><ComparisonExpr><StringConcatExpr><RangeExpr><AdditiveExpr><MultiplicativeExpr><UnionExpr><IntersectExceptExpr><InstanceofExpr><TreatExpr><CastableExpr><CastExpr><ArrowExpr><UnaryExpr><ValueExpr><SimpleMapExpr><PathExpr><RelativePathExpr><StepExpr><PostfixExpr><PrimaryExpr><Literal><NumericLiteral><IntegerLiteral>41</IntegerLiteral></NumericLiteral></Literal></PrimaryExpr></PostfixExpr></StepExpr></RelativePathExpr></PathExpr></SimpleMapExpr></ValueExpr></UnaryExpr></ArrowExpr></CastExpr></CastableExpr></TreatExpr></InstanceofExpr></IntersectExceptExpr></UnionExpr></MultiplicativeExpr>(:(::):)<TOKEN>+</TOKEN><MultiplicativeExpr><UnionExpr><IntersectExceptExpr><InstanceofExpr><TreatExpr><CastableExpr><CastExpr><ArrowExpr><UnaryExpr><ValueExpr><SimpleMapExpr><PathExpr><RelativePathExpr><StepExpr><PostfixExpr><PrimaryExpr><Literal><NumericLiteral><IntegerLiteral>1</IntegerLiteral></NumericLiteral></Literal></PrimaryExpr></PostfixExpr></StepExpr></RelativePathExpr></PathExpr></SimpleMapExpr></ValueExpr></UnaryExpr></ArrowExpr></CastExpr></CastableExpr></TreatExpr></InstanceofExpr></IntersectExceptExpr></UnionExpr></MultiplicativeExpr></AdditiveExpr></RangeExpr></StringConcatExpr></ComparisonExpr></AndExpr></OrExpr></ExprSingle></Expr></QueryBody></MainModule></Module><EOF/></XQuery>";
}
