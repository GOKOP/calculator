#include "Parser.hpp"
#include "BinOpNode.hpp"
#include "NumberNode.hpp"
#include "UnOpNode.hpp"

#include <algorithm>

std::string show_token_type(Token::Type type) {
	switch(type) {
		case Token::Plus:    return "'+'";
		case Token::Minus:   return "'-'";
		case Token::Mul:     return "'*'";
		case Token::Div:     return "'/'";
		case Token::Pow:     return "'^'";
		case Token::Sqrt:    return "'sqrt'";
		case Token::Cbrt:    return "'cbrt'";
		case Token::Lparen:  return "'('";
		case Token::Rparen:  return "')'";
		case Token::Number:  return "a number";
		case Token::Invalid: return "invalid token";
		case Token::Eof:     return "end of input";
	}
	return "abomination";
}

Parser::Parser(std::string input): 
	lexer(Lexer(input)),
	errors("")
{
	current_token = lexer.get_next_token();
}

void Parser::ignore_invalid() {
	while(current_token.type == Token::Invalid) {
		current_token = lexer.get_next_token();
	}
}

void Parser::eat(Token::Type type) {
	ignore_invalid();

	if(current_token.type == type) {
		current_token = lexer.get_next_token();
	} else {
		errors += "Invalid syntax at position " + std::to_string(current_token.pos) + ": expected " + show_token_type(type) + "; found " + show_token_type(current_token.type) + "\n";
	}
}

void Parser::eat(std::vector<Token::Type> types) {
	ignore_invalid();

	if(std::find(types.begin(), types.end(), current_token.type) != types.end()) {
		current_token = lexer.get_next_token();
	} else {
		errors += "Invalid syntax at position " + std::to_string(current_token.pos) + ": expected one of: ";
		for(auto type : types) {
			errors += show_token_type(type) + ",";
		}
		errors += "; found " + show_token_type(current_token.type) + "\n";
	}
}

std::unique_ptr<ASTNode> Parser::function() {
	// function: Sqrt|Cbrt Lparen add_expr Rparen

	std::unique_ptr<ASTNode> node;
	
	switch(current_token.type) {
	case Token::Sqrt:
		eat(Token::Sqrt);
		eat(Token::Lparen);
		node = std::make_unique<UnOpNode>(UnOpNode::Sqrt, std::move(add_expr()));
		eat(Token::Rparen);
		break;
	case Token::Cbrt:
		eat(Token::Cbrt);
		eat(Token::Lparen);
		node = std::make_unique<UnOpNode>(UnOpNode::Cbrt, std::move(add_expr()));
		eat(Token::Rparen);
		break;
	default:
		eat({Token::Sqrt, Token::Cbrt});
	}

	return node;
}

std::unique_ptr<ASTNode> Parser::factor() {
	// factor: (Plus|Minus) factor | Number | Lparen add_expr Rparen | function

	std::unique_ptr<ASTNode> node;

	switch(current_token.type) {
	case Token::Plus:
		eat(Token::Plus);
		node = std::make_unique<UnOpNode>(UnOpNode::Plus, std::move(factor()));
		break;
	case Token::Minus:
		eat(Token::Minus);
		node = std::make_unique<UnOpNode>(UnOpNode::Minus, std::move(factor()));
		break;
	case Token::Lparen:
		eat(Token::Lparen);
		node = add_expr();
		eat(Token::Rparen);
		break;
	case Token::Sqrt: 
	case Token::Cbrt:
		node = function();
		break;
	default:
		node = std::make_unique<NumberNode>(current_token.value);
		eat(Token::Number);
	}

	return node;
}

std::unique_ptr<ASTNode> Parser::pow_expr() {
	// pow_expr: mul_expr (Pow mul_expr)*

	auto node = factor();
	
	while(current_token.type == Token::Pow) {
		eat(Token::Pow);
		node = std::make_unique<BinOpNode>(BinOpNode::Pow, std::move(node), std::move(factor()));
	}

	return node;
}

std::unique_ptr<ASTNode> Parser::mul_expr() {
	// mul_expr: pow_expr (Mul|Div mul_expr)*

	auto node = pow_expr();
	
	while(current_token.type == Token::Mul || current_token.type == Token::Div) {
		auto token = current_token;
		eat({Token::Mul, Token::Div});

		switch(token.type) {
		case Token::Mul:
			node = std::make_unique<BinOpNode>(BinOpNode::Mul, std::move(node), std::move(pow_expr()));
			break;
		case Token::Div:
			node = std::make_unique<BinOpNode>(BinOpNode::Div, std::move(node), std::move(pow_expr()));
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
	 * mul_expr: pow_expr(Mul|Div pow_expr)*
	 * pow_expr: factor(Pow factor)*
	 * factor: (Plus|Minus) factor | Number | Lparen add_expr Rparen | function
	 * function: Sqrt|Cbrt Lparen add_expr Rparen
	 */

	auto tree = add_expr();
	eat(Token::Eof);

	auto total_errors = lexer.get_errors() + errors;
	if(!total_errors.empty()) return total_errors;

	return tree;
}
