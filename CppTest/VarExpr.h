#pragma once
#include "Expr.h"

class VarExpr : public Expr
{
public:
	std::string name;
	std::vector<Expr*>* args;

	VarExpr(std::string& name, std::vector<Expr*>* args);
	~VarExpr();

	std::string toString() const override;
	void accept(Visitor* visitor) override;
};
