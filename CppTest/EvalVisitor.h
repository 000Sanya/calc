#pragma once
#include "Expr.h"
#include "ConstExrp.h"
#include "VarExpr.h"
#include "BinaryExpr.h"
#include "UnaryExpr.h"
#include <stack>
#include <map>
#include <functional>

#define FUNC1(func) \
	[] (std::stack<double> stack) { double d = stack.top(); stack.pop(); return func(d); }
#define FUNC2(func) \
	[] (std::stack<double> stack) { double d1 = stack.top(); stack.pop(); double d2 = stack.top(); stack.pop(); return func(d2, d1); }

using VmFunc = std::function<double(std::stack<double>&)>;

class EvalVisitor : public Visitor
{
private:
	std::stack<double> stack;
	std::map<std::string, double> variables;
	std::map<std::string, VmFunc> functions;
public:
	EvalVisitor();
	~EvalVisitor();

	void visit(Expr* expr) override;
	void visit(ConstExpr* expr) override;
	void visit(VarExpr* expr) override;
	void visit(BinaryExpr* expr) override;
	void visit(UnaryExpr* expr) override;

	double getTopValue();

	void addFunc(const char* name, VmFunc func);
	void removeFunc(const char* name, VmFunc func);
	double callFunc(const char* name);

	void setVariable(const char* name, double value);
	double getVariable(const char* name);
	
};
