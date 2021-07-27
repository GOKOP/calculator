#include "Lexer.hpp"
#include <cctype>

Lexer::Lexer(std::string input): 
	input(input), 
	current_char_index(0),
	errors("")
{}

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
			default:
				// not using += so that right hand side is converted to std::string which allows +
				errors = errors + "Invalid character '" + input[current_char_index - 1] + "' at position " + std::to_string(current_char_index - 1) + "\n";
				return { Token::Invalid, 0 };
		}
	}

	return { Token::Eof, 0 };
}

std::string Lexer::get_errors() {
	return errors;
}
