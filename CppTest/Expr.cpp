#include "Expr.h"

std::ostream& operator<<(std::ostream& out, const Expr& expr)
{
	out << expr.toString();
	return out;
}
