#pragma once
#include <string>

enum TokenKind
{
	EOC,
	ERROR,
	ID,
	NUMBER,
	ADD,
	SUB,
	MUL,
	DIV,
	POW,
	LEFTP,
	RIGHTP,
	COMMA
};

class Token
{
public:
	TokenKind kind;
	std::string value_str;
	double value_d;

	Token(TokenKind kind);
	Token(TokenKind kind, std::string& value);
	Token(TokenKind kind, double value);
	~Token();
	operator bool() const;

	std::string toString() const;
};

std::ostream& operator<<(std::ostream& out, const Token& token);
