#pragma once

class Expr;
class ConstExpr;
class VarExpr;
class BinaryExpr;
class UnaryExpr;

class Visitor
{
public:
	virtual ~Visitor() = default;
	virtual void visit(Expr* expr) = 0;
	virtual void visit(ConstExpr* expr) = 0;
	virtual void visit(VarExpr* expr) = 0;
	virtual void visit(BinaryExpr* expr) = 0;
	virtual void visit(UnaryExpr* expr) = 0;
};
