#pragma once
#include "Token.h"
#include <vector>

class Lexer
{
public:
	Lexer(std::string& code);
	~Lexer();

	Token* get_next_token();
	Token* current_token();

	Token* pick();
	Token* pop();
	
private:
	std::string code;
	const char* pos;

	std::vector<Token*> tokens;
	std::vector<Token*>::iterator head;

	double read_double();
	std::string read_id();
	Token* add_token(Token* token);
};