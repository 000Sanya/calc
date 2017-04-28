#include "OperatorInfo.h"

OperatorInfo OperatorInfo::None = OperatorInfo(-1, LEFT);

OperatorInfo::OperatorInfo(): precendence(0), associavity()
{
}

OperatorInfo::OperatorInfo(int32_t prec, Associavity assoc)
{
	this->associavity = assoc;
	this->precendence = prec;
}

std::string OperatorInfo::getOpString(const TokenKind& kind)
{
	switch (kind)
	{
		case ADD: return std::string("+");
		case SUB: return std::string("-");
		case MUL: return std::string("*");
		case DIV: return std::string("/");
		case POW: return std::string("^");
		default: throw std::exception("Is not operator");
	}
}
