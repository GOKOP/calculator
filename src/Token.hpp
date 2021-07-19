#pragma once

struct Token {
	enum Type {
		Plus,
		Minus,
		Number,
		Eof
	};

	Type type;
	int value; // only for numbers
};
