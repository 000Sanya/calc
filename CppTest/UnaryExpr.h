#pragma once
#include "Expr.h"

class UnaryExpr : public Expr
{
public:
	TokenKind op;
	Expr* expr;

	UnaryExpr(TokenKind op, Expr* expr);
	~UnaryExpr();
	std::string toString() const override;
	void accept(Visitor* visitor) override;
};
