#include "Token.h"

Token::Token(TokenKind kind)
{
	this->kind = kind;
	this->value_d = 0.;
	this->value_str = std::string();
}

Token::Token(TokenKind kind, std::string& value)
{
	this->kind = kind;
	this->value_d = 0.;
	this->value_str = value;
}

Token::Token(TokenKind kind, double value)
{
	this->kind = kind;
	this->value_d = value;
	this->value_str = std::string();
}

Token::~Token()
{
}

Token::operator bool() const
{
	return this->kind != EOC;
}

std::string Token::toString() const
{
	std::string kindStr;
	std::string valueStr;
	std::string ret;
	switch (kind)
	{
		case EOC:
			kindStr = std::string("Type: EOC");
			break;
		case ERROR: 
			kindStr = std::string("Type: ERROR");
			break;
		case ID:
			kindStr = std::string("Type: ID");
			valueStr = std::string("\tValue: ") + this->value_str;
			break;
		case NUMBER:
			kindStr = std::string("Type: NUMBER");
			valueStr = std::string("\tValue: ") + std::to_string(this->value_d);
			break;
		case ADD:
			kindStr = std::string("Type: +");
			break;
		case SUB:
			kindStr = std::string("Type: -");
			break;
		case MUL:
			kindStr = std::string("Type: *");
			break;
		case DIV:
			kindStr = std::string("Type: /");
			break;
		case POW:			
			kindStr = std::string("Type: ^");
			break;
		case LEFTP:			
			kindStr = std::string("Type: (");
			break;
		case RIGHTP:			
			kindStr = std::string("Type: )");
			break;
		case COMMA:			
			kindStr = std::string("Type: ,");
			break;
		default: ;
	}
	ret = kindStr + valueStr;
	return ret;
}

std::ostream& operator<<(std::ostream& out, const Token& token)
{
	std::string str = token.toString();
	return (out << str);
}
