#include "Lexer.hpp"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(std::string input): input(input), current_char_index(0) {}

Token Lexer::get_next_token() {
	if(current_char_index >= input.size()) return { Token::Eof, 0 };

	Token return_val;

	switch(input[current_char_index]) {
		case '+': return_val = { Token::Plus, 0 }; break;
		case '-': return_val = { Token::Minus, 0 }; break;
		default: throw(std::runtime_error("Invalid character"));
	}

	++current_char_index;
	return return_val;
}
