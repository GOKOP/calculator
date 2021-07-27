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
		Invalid, // made from invalid input characters
		Eof
	};

	Type type;
	double value; // only for numbers
};
