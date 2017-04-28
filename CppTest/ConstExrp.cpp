#include "ConstExrp.h"
#include "sstream"

ConstExpr::ConstExpr(double& value)
{
	this->value = value;
}

ConstExpr::~ConstExpr()
{}

std::string ConstExpr::toString() const
{
	std::stringstream stream = std::stringstream();
	stream << value;
	return stream.str();
}

void ConstExpr::accept(Visitor* visitor)
{
	visitor->visit(this);
}
