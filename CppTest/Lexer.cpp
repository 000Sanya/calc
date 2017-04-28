#include "Lexer.h"
#include <cctype>
#include <vector>
#include <memory>

Lexer::Lexer(std::string& code)
{
	this->code = code;
	this->pos = code.c_str();
}

Lexer::~Lexer()
{
	for(auto i = tokens.begin(); i != tokens.end(); ++i)
	{
		delete *i;
	}
}

Token* Lexer::get_next_token()
{
	while(*pos)
	{
		switch(*pos)
		{
			case '+':
				pos++;
				return add_token(new Token(ADD));
			case '-':
				pos++;
				return add_token(new Token(SUB));
			case '*':
				pos++;
				return add_token(new Token(MUL));
			case '/':
				pos++;
				return add_token(new Token(DIV));
			case '^':
				pos++;
				return add_token(new Token(POW));
			case ',':
				pos++;
				return add_token(new Token(COMMA));
			case '(':
				pos++;
				return add_token(new Token(LEFTP));
			case ')':
				pos++;
				return add_token(new Token(RIGHTP));
			default:
				if (isspace(*pos))
				{
					pos++;
					continue;
				}
				if(isdigit(*pos))
				{
					return add_token(new Token(NUMBER, read_double()));
				}
				if(isalpha(*pos))
				{
					return add_token(new Token(ID, read_id()));
				}
				pos++;
				return add_token(new Token(ERROR));
		}
		
	}
	return add_token(new Token(EOC));
}

Token* Lexer::current_token()
{
	auto it = tokens.back();
	return it;
}

Token* Lexer::pick()
{
	if (tokens.size() == 0)
		this->pop();
	std::vector<Token*>::iterator it = tokens.end() - 1;
	return *it;
}

Token* Lexer::pop()
{
	this->get_next_token();
	return this->pick();
}

double Lexer::read_double()
{
	bool isHasDot = false;
	std::vector<char> buffer = std::vector<char>();
	while(isdigit(*pos) || *pos == '.')
	{
		if (*pos == '.')
		{
			if(isHasDot)
			{
				pos++;
				continue;
			}
			isHasDot = true;
		}
		buffer.push_back(*pos);
		pos++;
	}
	std::string str = std::string(buffer.begin(), buffer.end());
	return stod(str);
}

std::string Lexer::read_id()
{
	std::vector<char> buffer = std::vector<char>();
	while(isalpha(*pos))
	{
		buffer.push_back(*pos);
		pos++;
	}
	return std::string(buffer.begin(), buffer.end());
}

Token* Lexer::add_token(Token* token)
{
	if(token != nullptr)
	{
		tokens.push_back(token);
		return token;
	}
	throw std::exception("Token must be not null");
}
