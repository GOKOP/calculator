#pragma once

#include "Lexer.hpp"
#include "ASTNode.hpp"

#include <vector>
#include <memory>

class Parser {
	Lexer lexer;
	Token current_token;

	void eat(Token::Type type);
	void eat(std::vector<Token::Type> types);
	std::unique_ptr<ASTNode> factor();
	std::unique_ptr<ASTNode> expr();

public:
	Parser(std::string input);
	std::unique_ptr<ASTNode> parse();
};
