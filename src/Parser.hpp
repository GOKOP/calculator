#pragma once

#include "Lexer.hpp"
#include "ASTNode.hpp"

#include <vector>
#include <memory>
#include <variant>

class Parser {
	Lexer lexer;
	Token current_token;
	std::string errors;

	void ignore_invalid();
	void eat(Token::Type type);
	void eat(std::vector<Token::Type> types);
	std::unique_ptr<ASTNode> factor();
	std::unique_ptr<ASTNode> mul_expr();
	std::unique_ptr<ASTNode> add_expr();

public:
	Parser(std::string input);
	std::variant<std::unique_ptr<ASTNode>, std::string> parse();
};
