#pragma once

#include "Lexer.hpp"
#include "ASTNode.hpp"

#include <vector>
#include <memory>
#include <variant>
#include <utility>
#include <optional>

class Parser {
	Lexer lexer;
	Token current_token;
	std::string errors;

	void eat(Token::Type type);
	void eat(const std::vector<Token::Type>& types);
	std::optional<std::unique_ptr<ASTNode>> function();
	std::optional<std::unique_ptr<ASTNode>> constant();
	std::unique_ptr<ASTNode> factor();
	std::unique_ptr<ASTNode> pow_expr();
	std::unique_ptr<ASTNode> mul_expr();
	std::unique_ptr<ASTNode> add_expr();

public:
	Parser(std::string_view input);

	// ok this looks ugly but it's all because lexer errors are basically ignored
	// parse() returns a variant with either a correctly formed AST *and* lexer errors,
	// *or* lexer errors concatenated with parser errors
	std::variant<std::pair<std::unique_ptr<ASTNode>, std::string_view>, std::string> parse();
};
