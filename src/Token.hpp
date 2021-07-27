#pragma once

struct Token {
	enum Type {
		Plus,
		Minus,
		Mul,
		Div,
		Lparen,
		Rparen,
		Number,
		Eof
	};

	Type type;
	double value; // only for numbers
};
