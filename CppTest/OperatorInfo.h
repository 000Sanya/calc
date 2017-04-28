#pragma once
#include <cstdint>
#include <string>
#include "Token.h"

enum Associavity
{
	LEFT,
	RIGHT
};

class OperatorInfo
{
public:
	static OperatorInfo None;

	int32_t precendence;
	Associavity associavity;

	OperatorInfo();
	OperatorInfo(int32_t prec, Associavity assoc);

	static std::string getOpString(const TokenKind& kind);
};
