#pragma once

struct Token {
	enum Type {
		Plus,
		Minus,
		Mul,
		Div,
		Number,
		Eof
	};

	Type type;
	int value; // only for numbers
};
