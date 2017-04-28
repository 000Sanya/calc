#pragma once
#include "Expr.h"

class ConstExpr : public Expr
{
public:
	double value;

	ConstExpr(double& value);
	~ConstExpr() override;
	std::string toString() const override;
	void accept(Visitor* visitor) override;
};
