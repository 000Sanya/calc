#include "Calculate.h"

Calculate::Calculate(std::string& strExpr)
{
	this->lexer = new Lexer(strExpr);
	this->parser = new Parser(lexer);
	this->expr = this->parser->parseExpr();
	this->visitor = new EvalVisitor();
}

Calculate::~Calculate()
{
	delete visitor;
	delete expr;
	delete parser;
	delete lexer;
}

double Calculate::calculate(double x)
{
	visitor->setVariable("x", x);
	expr->accept(visitor);
	return visitor->getTopValue();
}
