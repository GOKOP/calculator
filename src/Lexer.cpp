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
	
		if(isdigit(input[current_pos])) {
			auto pos = current_pos + 1;
			return { Token::Number, get_number(), pos };
		}

		if(isalnum(input[current_pos])) {
			auto pos = current_pos + 1;
			auto word = get_word();
			if(word == "sqrt") return { Token::Sqrt, 0, pos };
			if(word == "cbrt") return { Token::Cbrt, 0, pos };
			if(word == "root") return { Token::Root, 0, pos };
			if(word == "sin") return { Token::Sin, 0, pos };
			if(word == "cos") return { Token::Cos, 0, pos };
			if(word == "tan") return { Token::Tan, 0, pos };
			if(word == "ctg") return { Token::Ctg, 0, pos };
			if(word == "asin") return { Token::Asin, 0, pos };
			if(word == "acos") return { Token::Acos, 0, pos };
			if(word == "atan") return { Token::Atan, 0, pos };
			if(word == "ln") return { Token::Ln, 0, pos };
			if(word == "log") return { Token::Log, 0, pos };
			errors += "Invalid function '" + word + "' ignored at position ";
			errors += std::to_string(pos) + "\n";
			continue;
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
			case ',': return { Token::Comma, 0, current_pos };
			default:
				errors += std::string("Invalid character '") + input[current_pos - 1];
				errors += "' ignored at position " + std::to_string(current_pos) + "\n";
				continue;
		}
	}

	return { Token::Eof, 0, current_pos+1 };
}

std::string Lexer::get_errors() {
	return errors;
}
