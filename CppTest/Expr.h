#pragma once
#include "Lexer.h"
#include "Visitor.h"

class Expr
{
public:
	virtual ~Expr() {};

	virtual std::string toString() const = 0;
	virtual void accept(Visitor* visitor) = 0;
};

std::ostream& operator<<(std::ostream& out, const Expr& expr);
