#pragma once

struct Token {
	enum Type {
		Plus,
		Minus,
		Mul,
		Div,
		Pow,
		Sqrt,
		Lparen,
		Rparen,
		Number,
		Invalid, // made from invalid input characters
		Eof
	};

	Type type;
	double value; // only for numbers
	std::size_t pos; // where in the input is the first character of this token
};
