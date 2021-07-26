#include "Parser.hpp"
#include "BinOpNode.hpp"
#include "NumberNode.hpp"

#include <stdexcept>
#include <algorithm>

Parser::Parser(std::string input): lexer(Lexer(input)) {
	current_token = lexer.get_next_token();
}

void Parser::eat(Token::Type type) {
	if(current_token.type == type) {
		current_token = lexer.get_next_token();
	} else {
		throw(std::runtime_error("Invalid syntax"));
	}
}

void Parser::eat(std::vector<Token::Type> types) {
	if(std::find(types.begin(), types.end(), current_token.type) != types.end()) {
		current_token = lexer.get_next_token();
	} else {
		throw(std::runtime_error("Invalid syntax"));
	}
}

std::unique_ptr<ASTNode> Parser::factor() {
	auto node = std::make_unique<ASTNode>(NumberNode(current_token.value));
	eat(Token::Number);
	return node;
}

std::unique_ptr<ASTNode> Parser::expr() {
	auto node = factor();
	
	while(current_token.type == Token::Plus || current_token.type == Token::Minus) {
		auto token = current_token;
		eat({Token::Plus, Token::Minus});

		switch(token.type) {
		case Token::Plus:
			node = std::make_unique<ASTNode>(BinOpNode(BinOpNode::Plus, std::move(node), std::move(factor())));
			break;
		case Token::Minus:
			node = std::make_unique<ASTNode>(BinOpNode(BinOpNode::Minus, std::move(node), std::move(factor())));
			break;
		default: break; // impossible anyway
		}
	}

	return node;
}

std::unique_ptr<ASTNode> Parser::parse() {
	auto tree = expr();
	eat(Token::Eof);
	return tree;
}
