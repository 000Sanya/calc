#pragma once
#include <string>
#include "Expr.h"
#include "Parser.h"
#include "EvalVisitor.h"

class Calculate
{
public:
	Calculate(std::string& strExpr);
	~Calculate();

	double calculate(double x);


private:
	Expr* expr;
	Lexer* lexer;
	Parser* parser;
	EvalVisitor* visitor;
};
