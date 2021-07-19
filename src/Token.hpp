#pragma once

struct Token {
	enum Type {
		Plus,
		Minus,
		Eof
	};

	Type type;
	int value; // only for numbers
};
