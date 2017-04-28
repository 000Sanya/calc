#pragma once
#include "Expr.h"

class BinaryExpr : public Expr
{
public:
	Expr* lv;
	Expr* rv;
	TokenKind op;

	BinaryExpr(Expr* lv, Expr* rv, TokenKind& op);
	~BinaryExpr() override;
	std::string toString() const override;
	void accept(Visitor* visitor) override;
};
