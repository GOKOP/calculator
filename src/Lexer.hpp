#pragma once

#include <string>
#include "Token.hpp"

class Lexer {
	std::string input;
	std::size_t current_char_index;
	
	double get_number();
	void skip_whitespace();
public:
	Lexer(std::string input);
	Token get_next_token();
};
