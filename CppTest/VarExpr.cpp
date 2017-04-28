#include "VarExpr.h"
#include <sstream>

VarExpr::VarExpr(std::string& name, std::vector<Expr*>* args)
{
	this->name = name;
	this->args = args;
}

VarExpr::~VarExpr()
{
	for(Expr* expr : *args)
	{
		delete expr;
	}
	delete args;
}

std::string VarExpr::toString() const
{
	std::vector<Expr*>::iterator it = this->args->begin();
	std::stringstream ss = std::stringstream();
	ss << this->name;
	if (args->size() != 0)
	{
		ss << "(" << ' ' << **it;
		++it;
		for(; it != args->end(); ++it)
		{
			ss << ", " << **it;
		}
		ss << ' ' << ')';
	}
	return ss.str();
}

void VarExpr::accept(Visitor* visitor)
{
	visitor->visit(this);
}
