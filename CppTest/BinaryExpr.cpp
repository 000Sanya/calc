#include "BinaryExpr.h"
#include <sstream>
#include "OperatorInfo.h"

BinaryExpr::BinaryExpr(Expr* lv, Expr* rv, TokenKind& op)
{
	this->lv = lv;
	this->rv = rv;
	this->op = op;
}

BinaryExpr::~BinaryExpr()
{
	delete lv;
	delete rv;
}

std::string BinaryExpr::toString() const
{
	std::stringstream stream = std::stringstream();
	stream << "[" << *lv << ' ' << OperatorInfo::getOpString(op) << ' ' << *rv << "]";
	return stream.str();
}

void BinaryExpr::accept(Visitor* visitor)
{
	visitor->visit(this);
}
