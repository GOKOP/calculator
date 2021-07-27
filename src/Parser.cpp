#include "Parser.hpp"
#include "BinOpNode.hpp"
#include "NumberNode.hpp"

#include <algorithm>

Parser::Parser(std::string input): lexer(Lexer(input)) {
	current_token = lexer.get_next_token();
}

void Parser::ignore_invalid() {
	while(current_token.type == Token::Invalid) {
		current_token = lexer.get_next_token();
	}
}

void Parser::eat(Token::Type type) {
	ignore_invalid();

	if(current_token.type == type || current_token.type == Token::Invalid) {
		current_token = lexer.get_next_token();
	} else {
		errors += "Parser error\n";
	}
}

void Parser::eat(std::vector<Token::Type> types) {
	ignore_invalid();

	if(std::find(types.begin(), types.end(), current_token.type) != types.end()) {
		current_token = lexer.get_next_token();
	} else {
		errors += "Parser error\n";
	}
}

std::unique_ptr<ASTNode> Parser::factor() {
	// factor: Number | Lparen add_expr Rparen

	std::unique_ptr<ASTNode> node;

	if(current_token.type == Token::Lparen) {
		eat(Token::Lparen);
		node = add_expr();
		eat(Token::Rparen);
	} else {
		node = std::make_unique<NumberNode>(current_token.value);
		eat(Token::Number);
	}

	return node;
}

std::unique_ptr<ASTNode> Parser::mul_expr() {
	// add_expr: mul_expr (Plus|Minus mul_expr)*

	auto node = factor();
	
	while(current_token.type == Token::Mul || current_token.type == Token::Div) {
		auto token = current_token;
		eat({Token::Mul, Token::Div});

		switch(token.type) {
		case Token::Mul:
			node = std::make_unique<BinOpNode>(BinOpNode::Mul, std::move(node), std::move(factor()));
			break;
		case Token::Div:
			node = std::make_unique<BinOpNode>(BinOpNode::Div, std::move(node), std::move(factor()));
			break;
		default: break; // impossible anyway
		}
	}

	return node;
}

std::unique_ptr<ASTNode> Parser::add_expr() {
	// add_expr: mul_expr (Plus|Minus mul_expr)*

	auto node = mul_expr();
	
	while(current_token.type == Token::Plus || current_token.type == Token::Minus) {
		auto token = current_token;
		eat({Token::Plus, Token::Minus});

		switch(token.type) {
		case Token::Plus:
			node = std::make_unique<BinOpNode>(BinOpNode::Plus, std::move(node), std::move(mul_expr()));
			break;
		case Token::Minus:
			node = std::make_unique<BinOpNode>(BinOpNode::Minus, std::move(node), std::move(mul_expr()));
			break;
		default: break; // impossible anyway
		}
	}

	return node;
}

std::variant<std::unique_ptr<ASTNode>, std::string> Parser::parse() {
	/* add_expr: mul_expr(Plus|Minus mul_expr)*
	 * mul_expr: factor(Mul|Div factor)*
	 * factor: Number | Lparen add_expr Rparen
	 */

	auto tree = add_expr();
	eat(Token::Eof);

	auto total_errors = lexer.get_errors() + errors;
	if(!total_errors.empty()) return total_errors;

	return tree;
}
