#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include "EvalVisitor.h"
#include "Calculate.h"

//typedef double(*func)(double x);
using func = std::function<double(double)>;

double devirative(func f, double x, double eps);

double otrezok_popolam(double a, double b, double eps, func f);
double hord(double a, double b, double esp, func f);
double newton(double c0, double eps, func f, func df);
double newton2(double c0, double eps, func f);


double cube(double x)
{
	return pow(x, 3.0) + 2;
}

double dcube(double x)
{
	return 3 * pow(x, 2.0);
}

void main()
{
	std::string strExpr;

	std::cout << "Please, enter the expression: ";
	std::cin >> strExpr;
	Calculate* calc = new Calculate(strExpr);
	double solve = newton2(-10, 10, [calc] (double x) mutable {return calc->calculate(x);});
	std::cout << solve << std::endl;
	system("pause");
	delete calc;
}

double devirative(func f, double x, double eps)
{
	double prev_h, h;
	double prev_value, value, dv;

	prev_value = 0;
	h = 1E-12;
	value = (f(x + h) - f(x)) / h;

	return value;
}

double otrezok_popolam(double a, double b, double eps, func f)
{
	double eps2 = eps * 2;
	double ak, bk, ck;
	double value_a, value_b, value_c;
	int i;

	ak = fmin(a, b);
	bk = fmax(a, b);

	value_a = f(ak);
	value_b = f(bk);

	if(value_a * value_b > 0)
	{
		return NAN;
	}

	while(true)
	{
		ck = (ak + bk) / 2;
		
		value_c = f(ck);
		value_a = f(ak);
		value_b = f(bk);

		//printf("ak: %lf\tvalue: %lf\nbk: %lf\tvalue: %lf\nck: %lf\tvalue: %lf\n\n", ak, value_a, bk, value_b, ck, value_c);
		
		if(value_a * value_c < 0)
		{
			bk = ck;
		}
		else if (value_b * value_c < 0)
		{
			ak = ck;
		}

		if (fabs(ak - bk) < eps2)
			return ck;
	}
}

double hord(double a, double b, double eps, func f)
{
	double ak, bk, ck, last_c;
	double va, vb, vc;

	ak = a;
	bk = b;

	ck = 0.;

	do
	{
		last_c = ck;

		va = f(ak);
		vb = f(bk);

		ck = ak - (bk - ak) / (vb - va)*va;
		vc = f(ck);
		if (va * vc < 0)
			bk = ck;
		if (vb * vc < 0)
			ak = ck;
		//printf("ak: %lf\tvalue: %lf\nbk: %lf\tvalue: %lf\nck: %lf\tvalue: %lf\nlast c: %lf\n\n", ak, va, bk, vb, ck, vc, last_c);
	} while (fabs(ck - last_c) > eps);

	return ck;
}

double newton(double c0, double eps, func f, func df)
{
	double ck, ck_1, dc;
	double fc, dfc;

	ck_1 = c0;
	ck = 0;
	do
	{
		fc = f(ck_1);
		dfc = df(ck_1);
		if (dfc == 0.)
			return NAN;
		ck = ck_1 - fc / dfc;
		printf("ck: %lf\tck-1: %lf\n", ck, ck_1);
		dc = ck - ck_1;
		ck_1 = ck;
	} while (fabs(dc) > eps);
	return ck;
}

double newton2(double c0, double eps, func f)
{
	double ck, ck_1, dc;
	double fc, dfc;

	ck_1 = c0;
	ck = 0;
	do
	{
		fc = f(ck_1);
		dfc = devirative(f, ck_1, eps);
		if (dfc == 0.)
			return NAN;
		ck = ck_1 - fc / dfc;
		printf("ck: %lf\tck-1: %lf\n", ck, ck_1);
		dc = ck - ck_1;
		ck_1 = ck;
	} while (fabs(dc) > eps);
	return ck;
}
