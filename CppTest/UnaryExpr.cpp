#include "UnaryExpr.h"
#include <sstream>

UnaryExpr::UnaryExpr(TokenKind op, Expr* expr)
{
	this->op = op;
	this->expr = expr;
}

UnaryExpr::~UnaryExpr()
{
	delete expr;
}

std::string UnaryExpr::toString() const
{
	std::stringstream ss = std::stringstream();
	if (this->op == ADD)
		ss << '+';
	else if (this->op == SUB)
		ss << '-';
	ss << *expr;
	return ss.str();
}

void UnaryExpr::accept(Visitor* visitor)
{
	visitor->visit(this);
}
