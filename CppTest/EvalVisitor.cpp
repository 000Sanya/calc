#include "EvalVisitor.h"

EvalVisitor::EvalVisitor()
{
	this->variables = std::map<std::string, double>();
	this->functions = std::map<std::string, VmFunc>();
}

EvalVisitor::~EvalVisitor()
{
}

void EvalVisitor::visit(Expr* expr)
{
}

void EvalVisitor::visit(ConstExpr* expr)
{
	stack.push(expr->value);
}

void EvalVisitor::visit(VarExpr* expr)
{
	for(Expr* arg : *expr->args)
	{
		arg->accept(this);
	}
	double d = this->callFunc(expr->name.c_str());
	stack.push(d);
}

void EvalVisitor::visit(BinaryExpr* expr)
{
	expr->lv->accept(this);
	expr->rv->accept(this);

	double rv = stack.top();
	stack.pop();
	double lv = stack.top();
	stack.pop();

	double result;
	switch (expr->op)
	{
		case ADD:
			result = lv + rv;
			break;
		case SUB: 
			result = lv - rv;
			break;
		case MUL: 
			result = lv * rv;
			break;
		case DIV:
			result = lv / rv;
			break;
		case POW: 
			result = std::pow(lv, rv);
			break;
		default: ;
	}
	stack.push(result);
}

void EvalVisitor::visit(UnaryExpr* expr)
{
	expr->expr->accept(this);
	double v = stack.top(); stack.pop();
	if (expr->op == SUB)
		stack.push(v * -1.f);
	else if (expr->op == ADD)
		stack.push(v);
}

double EvalVisitor::getTopValue()
{
	return stack.top();
}

void EvalVisitor::addFunc(const char* name, VmFunc func)
{
	functions[name] = func;
}

void EvalVisitor::removeFunc(const char* name, VmFunc func)
{
}

double EvalVisitor::callFunc(const char* name)
{
	if(functions.find(name) != functions.end())
	{
		return functions[name](stack);
	}
	if(variables.find(name) != variables.end())
	{
		getVariable(name);
	}
	else throw std::exception("Function not found");
}

void EvalVisitor::setVariable(const char* name, double value)
{
	variables[name] = value;
}

double EvalVisitor::getVariable(const char* name)
{
	if (variables.find(name) != variables.end())
		return variables[name];
	return NAN;
}
