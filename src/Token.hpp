#pragma once

#include <cstddef>

struct Token {
	enum Type {
		Plus,
		Minus,
		Mul,
		Div,
		Pow,
		Sqrt,
		Cbrt,
		Root,
		Sin,
		Cos,
		Tan,
		Ctg,
		Acos,
		Asin,
		Atan,
		Ln,
		Log,
		Pi,
		E,
		Deg,
		Comma,
		Lparen,
		Rparen,
		Number,
		Eof
	};

	Type type;
	double value; // only for numbers
	std::size_t pos; // where in the input is the first character of this token
};

bool operator==(const Token& lhs, const Token& rhs);
