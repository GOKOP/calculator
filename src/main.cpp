#include <iostream>

#include "Lexer.hpp"

int main() {
	auto lexer = Lexer("14+22-5+3");
	Token current_token;
	do {
		current_token = lexer.get_next_token();
		switch(current_token.type) {
			case Token::Plus: std::cout<<"Plus "; break;
			case Token::Minus: std::cout<<"Minus "; break;
			case Token::Number: std::cout<<"Number("<<current_token.value<<") "; break;
			case Token::Eof: std::cout<<"EOF "; break;
			default: std::cout<<"whoops "; break;
		}
	} while(current_token.type != Token::Eof);
}
