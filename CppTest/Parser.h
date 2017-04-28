#pragma once
#include "Expr.h"
#include "map"
#include "OperatorInfo.h"

class Parser
{
private:
	std::map<TokenKind, int32_t> operator_precedence;
	std::map<TokenKind, OperatorInfo> operator_info;
	Lexer* lexer;

	void initOps();
	OperatorInfo& getOperatorInfo(TokenKind op);
public:
	Parser(Lexer* lexer);
	~Parser();

	Expr* parseExpr();
	Expr* parseConst();
	Expr* parseVar();
	Expr* parseParenExpr();
	Expr* parsePrimary();
	Expr* parseUnary();
	Expr* parseBinary(Expr* left, OperatorInfo& opInfo);

	void error(const char* message);
};
