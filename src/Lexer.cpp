#include "Lexer.hpp"
#include <cctype>

Lexer::Lexer(std::string input): 
	input(input), 
	current_pos(0),
	errors("")
{}

double Lexer::get_number() {
	std::string number_str;

	while(isdigit(input[current_pos]) || input[current_pos] == '.') {
		number_str += (input[current_pos]);
		++current_pos;
	}

	return std::stod(number_str);
}

std::string Lexer::get_word() {
	std::string result;

	while(isalnum(input[current_pos])) {
		result += input[current_pos];
		++current_pos;
	}

	return result;
}

void Lexer::skip_whitespace() {
	while(current_pos < input.size() && isspace(input[current_pos])) {
		++current_pos;
	}
}

Token Lexer::get_next_token() {
	while(current_pos < input.size()) {
		if(isspace(input[current_pos])) {
			skip_whitespace();
			continue;
		}
	
		if(isdigit(input[current_pos])) return { Token::Number, get_number(), current_pos+1 };

		if(isalnum(input[current_pos])) {
			auto word = get_word();
			if(word == "sqrt") return { Token::Sqrt, 0, current_pos+1 };
			errors += "Invalid function '" + word + "' at position " + std::to_string(current_pos+1);
		}
	
		++current_pos;
		switch(input[current_pos - 1]) {
			case '+': return { Token::Plus, 0, current_pos };
			case '-': return { Token::Minus, 0, current_pos };
			case '*': return { Token::Mul, 0, current_pos };
			case '/': return { Token::Div, 0, current_pos };
			case '^': return { Token::Pow, 0, current_pos };
			case '(': return { Token::Lparen, 0, current_pos };
			case ')': return { Token::Rparen, 0, current_pos };
			default:
				// not using += so that right hand side is converted to std::string which allows +
				errors = errors + "Invalid character '" + input[current_pos - 1] + "' at position " + std::to_string(current_pos - 1) + "\n";
				return { Token::Invalid, 0, current_pos };
		}
	}

	return { Token::Eof, 0, current_pos+1 };
}

std::string Lexer::get_errors() {
	return errors;
}
