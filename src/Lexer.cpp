#include "Lexer.hpp"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(std::string input): input(input), current_char_index(0) {}

double Lexer::get_number() {
	std::string number_str;

	while(isdigit(input[current_char_index]) || input[current_char_index] == '.') {
		number_str += (input[current_char_index]);
		++current_char_index;
	}

	return std::stod(number_str);
}

void Lexer::skip_whitespace() {
	while(current_char_index < input.size() && isspace(input[current_char_index])) {
		++current_char_index;
	}
}

Token Lexer::get_next_token() {
	while(current_char_index < input.size()) {
		if(isspace(input[current_char_index])) {
			skip_whitespace();
			continue;
		}
	
		if(isdigit(input[current_char_index])) return { Token::Number, get_number() };
	
		++current_char_index;
		switch(input[current_char_index - 1]) {
			case '+': return { Token::Plus, 0 };
			case '-': return { Token::Minus, 0 };
			case '*': return { Token::Mul, 0 };
			case '/': return { Token::Div, 0 };
			case '(': return { Token::Lparen, 0 };
			case ')': return { Token::Rparen, 0 };
			default: throw(std::runtime_error("Invalid character"));
		}
	}

	return { Token::Eof, 0 };
}
