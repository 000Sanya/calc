#include "Parser.h"
#include "ConstExrp.h"
#include "VarExpr.h"
#include "exception"
#include "BinaryExpr.h"
#include "iostream"
#include "UnaryExpr.h"

Parser::Parser(Lexer* lexer)
{
	if (lexer == nullptr)
		throw std::exception("Lexer must be not null");
	this->lexer = lexer;
	this->operator_precedence = std::map<TokenKind, int32_t>();
	this->operator_info = std::map<TokenKind, OperatorInfo>();
	this->initOps();
}

Parser::~Parser()
{
}

void Parser::initOps()
{
	this->operator_info[POW] = OperatorInfo(50, RIGHT);
	this->operator_info[DIV] = OperatorInfo(40, LEFT);
	this->operator_info[MUL] = OperatorInfo(40, LEFT);
	this->operator_info[ADD] = OperatorInfo(30, LEFT);
	this->operator_info[SUB] = OperatorInfo(30, LEFT);
}

OperatorInfo& Parser::getOperatorInfo(TokenKind op)
{
	if (this->operator_info.find(op) != this->operator_info.end())
		return this->operator_info[op];
	return OperatorInfo::None;
}

Expr* Parser::parseExpr()
{
	Expr* left = this->parsePrimary();
	return this->parseBinary(left, OperatorInfo::None);
}

Expr* Parser::parseConst()
{
	Token* token = lexer->pick();
	if(token->kind == TokenKind::NUMBER)
	{
		Expr* expr = new ConstExpr(token->value_d);
		lexer->pop();
		return expr;
	}
	return nullptr;
}

Expr* Parser::parseVar()
{
	Token* token = lexer->pick();
	std::vector<Expr*>* argsList = new std::vector<Expr*>();
	if(token->kind == TokenKind::ID)
	{
		lexer->pop();
		if(lexer->pick()->kind == LEFTP )
		{
			lexer->pop();
			if(lexer->pick()->kind != RIGHTP)
			{
				Expr* expr = parseExpr();
				argsList->push_back(expr);
				while (lexer->pick()->kind != RIGHTP)
				{
					lexer->pop();
					if(lexer->pick()->kind == EOC)
						break;
					if (lexer->pick()->kind != COMMA)
						error("Expecting ','");
					else
						lexer->pop();
					Expr* e = parseExpr();
					argsList->push_back(e);
				}
				lexer->pop();
			}
			else lexer->pop();
		}
		return new VarExpr(token->value_str, argsList);
	}
	return nullptr;
}

Expr* Parser::parseParenExpr()
{
	if(lexer->pick()->kind == LEFTP)
	{
		lexer->pop();
		Expr* expr = this->parseExpr();
		if (lexer->pick()->kind != RIGHTP)
			error("Expecting ')'");
		else
			lexer->pop();
		return expr;
	}
	return nullptr;
}

Expr* Parser::parsePrimary()
{
	Token* token = this->lexer->pick();
	switch (token->kind)
	{
		case ID:
			return this->parseVar();
		case LEFTP:
			return this->parseParenExpr();
		case ADD:
		case SUB:
			return this->parseUnary();
		case NUMBER:
			return this->parseConst();
		case EOC:
			return nullptr;
		default:
			error("Unexpected token");
			lexer->pop();
			return nullptr;
	}
}

Expr* Parser::parseUnary()
{
	Token* token = lexer->pick();
	if(token->kind == ADD || token->kind == SUB)
	{
		lexer->pop();
		Expr* expr = parsePrimary();
		if (expr == nullptr)
			return nullptr;
		return new UnaryExpr(token->kind, expr);
	}
	return nullptr;
}

Expr* Parser::parseBinary(Expr* left, OperatorInfo& opInfo)
{
	while(true)
	{
		Token* currOp = lexer->pick();
		OperatorInfo currOpInfo = this->getOperatorInfo(currOp->kind);

		if (currOpInfo.precendence < opInfo.precendence || currOpInfo.precendence == -1)
			return left;

		lexer->pop();
		Expr* nextExpr = parsePrimary();
		if (nextExpr == nullptr)
			error("Expression not found");
		Token* nextOp = lexer->pick(); // этот токен не выкидываем, ибо заглядываем вперед
		OperatorInfo nextOpInfo = this->getOperatorInfo(nextOp->kind);

		if (currOpInfo.precendence <= nextOpInfo.precendence)
		{
			if(currOpInfo.associavity == LEFT)
				currOpInfo.precendence++;
			nextExpr = parseBinary(nextExpr, currOpInfo);
		}
		left = new BinaryExpr(left, nextExpr, currOp->kind);
	}
}

void Parser::error(const char* message)
{
	std::cerr << message << std::endl;
	throw std::exception(message);
}
