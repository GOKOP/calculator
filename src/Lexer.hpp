#pragma once

#include <string>
#include "Token.hpp"

class Lexer {
	std::string input;
	std::size_t current_char_index;
	
public:
	Lexer(std::string input);
	Token get_next_token();
};
