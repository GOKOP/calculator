#include "Parser.hpp"
#include "BinOpNode.hpp"
#include "NumberNode.hpp"
#include "UnOpNode.hpp"
#include "ConstantNode.hpp"

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
		case Token::Root:    return "'root'";
		case Token::Sin:     return "'sin'";
		case Token::Cos:     return "'cos'";
		case Token::Tan:     return "'tan'";
		case Token::Ctg:     return "'ctg'";
		case Token::Asin:    return "'asin'";
		case Token::Acos:    return "'acos'";
		case Token::Atan:    return "'atan'";
		case Token::Ln:      return "'ln'";
		case Token::Log:     return "'log'";
		case Token::Pi:      return "'pi'";
		case Token::E:       return "'e'";
		case Token::Deg:     return "'deg'";
		case Token::Comma:   return "','";
		case Token::Lparen:  return "'('";
		case Token::Rparen:  return "')'";
		case Token::Number:  return "a number";
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

void Parser::eat(Token::Type type) {
	if(current_token.type == type) {
		current_token = lexer.get_next_token();
	} else {
		errors += "Invalid syntax at position " + std::to_string(current_token.pos);
		errors += ": expected " + show_token_type(type) + "; found ";
		errors += show_token_type(current_token.type) + "\n";
	}
}

void Parser::eat(std::vector<Token::Type> types) {
	if(std::find(types.begin(), types.end(), current_token.type) != types.end()) {
		current_token = lexer.get_next_token();
	} else {
		errors += "Invalid syntax at position " + std::to_string(current_token.pos);
		errors += ": expected one of: ";
		for(auto type : types) {
			errors += show_token_type(type) + ",";
		}
		errors += "; found " + show_token_type(current_token.type) + "\n";
	}
}

// this function is allowed not to return a value
// so that it can work as a check for whether or not there's a function
// otherwise factor() would have an ugly long case fallthrough
std::optional<std::unique_ptr<ASTNode>> Parser::function() {
	// function: (Sqrt|Cbrt|Sin|Cos|Tan|Ctg|Asin|Acos|Atan|Ln|Deg Lparen add_expr Rparen)|
	//           (Root|Log Lparen add_expr Comma add_expr)

	std::unique_ptr<ASTNode> node;

	auto token_type = current_token.type;
	auto func_tokens = {Token::Sqrt, Token::Cbrt, Token::Root, 
	                    Token::Sin, Token::Cos, Token::Tan, Token::Ctg,
	                    Token::Asin, Token::Acos, Token::Atan,
	                    Token::Ln, Token::Log, Token::Deg};
	if(std::find(func_tokens.begin(), func_tokens.end(), token_type) == func_tokens.end()) return {};
	eat(func_tokens);
	eat(Token::Lparen);
	
	switch(token_type) {
	case Token::Sqrt: 
		node = std::make_unique<UnOpNode>(UnOpNode::Sqrt, add_expr()); break;
	case Token::Cbrt:
		node = std::make_unique<UnOpNode>(UnOpNode::Cbrt, add_expr()); break;
	case Token::Root:
		node = add_expr();
		eat(Token::Comma);
		node = std::make_unique<BinOpNode>(BinOpNode::Root, std::move(node), add_expr());
		break;
	case Token::Sin:
		node = std::make_unique<UnOpNode>(UnOpNode::Sin, add_expr()); break;
	case Token::Cos:
		node = std::make_unique<UnOpNode>(UnOpNode::Cos, add_expr()); break;
	case Token::Tan:
		node = std::make_unique<UnOpNode>(UnOpNode::Tan, add_expr()); break;
	case Token::Ctg:
		node = std::make_unique<UnOpNode>(UnOpNode::Ctg, add_expr()); break;
	case Token::Asin:
		node = std::make_unique<UnOpNode>(UnOpNode::Asin, add_expr()); break;
	case Token::Acos:
		node = std::make_unique<UnOpNode>(UnOpNode::Acos, add_expr()); break;
	case Token::Atan:
		node = std::make_unique<UnOpNode>(UnOpNode::Atan, add_expr()); break;
	case Token::Ln:
		node = std::make_unique<UnOpNode>(UnOpNode::Ln, add_expr()); break;
	case Token::Log:
		node = add_expr();
		eat(Token::Comma);
		node = std::make_unique<BinOpNode>(BinOpNode::Log, std::move(node), add_expr());
		break;
	case Token::Deg:
		node = std::make_unique<UnOpNode>(UnOpNode::Deg, add_expr()); break;
	default: break;
	}

	eat(Token::Rparen);

	return node;
}

std::optional<std::unique_ptr<ASTNode>> Parser::constant() {
	// constant: Pi|E
	
	switch(current_token.type) {
	case Token::Pi: 
		eat(Token::Pi);
		return std::make_unique<ConstantNode>(ConstantNode::Pi);
	case Token::E: 
		eat(Token::E);
		return std::make_unique<ConstantNode>(ConstantNode::E);
	default: 
		return {};
	}
}

std::unique_ptr<ASTNode> Parser::factor() {
	// factor: (Plus|Minus) factor | Number | Lparen add_expr Rparen | function | constant

	auto maybe_node = function();
	if(maybe_node.has_value()) return std::move(maybe_node.value());

	maybe_node = constant();
	if(maybe_node.has_value()) return std::move(maybe_node.value());

	std::unique_ptr<ASTNode> node;

	switch(current_token.type) {
	case Token::Plus:
		eat(Token::Plus);
		node = std::make_unique<UnOpNode>(UnOpNode::Plus, factor());
		break;
	case Token::Minus:
		eat(Token::Minus);
		node = std::make_unique<UnOpNode>(UnOpNode::Minus, factor());
		break;
	case Token::Lparen:
		eat(Token::Lparen);
		node = add_expr();
		eat(Token::Rparen);
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
		node = std::make_unique<BinOpNode>(BinOpNode::Pow, std::move(node), factor());
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
			node = std::make_unique<BinOpNode>(BinOpNode::Mul, std::move(node), pow_expr());
			break;
		case Token::Div:
			node = std::make_unique<BinOpNode>(BinOpNode::Div, std::move(node), pow_expr());
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
			node = std::make_unique<BinOpNode>(BinOpNode::Plus, std::move(node), mul_expr());
			break;
		case Token::Minus:
			node = std::make_unique<BinOpNode>(BinOpNode::Minus, std::move(node), mul_expr());
			break;
		default: break; // impossible anyway
		}
	}

	return node;
}

std::variant<std::pair<std::unique_ptr<ASTNode>, std::string>, std::string> Parser::parse() {
	/* add_expr: mul_expr(Plus|Minus mul_expr)*
	 * mul_expr: pow_expr(Mul|Div pow_expr)*
	 * pow_expr: factor(Pow factor)*
	 * factor: (Plus|Minus) factor | Number | Lparen add_expr Rparen | function | constant
	 * function: (Sqrt|Cbrt|Sin|Cos|Tan|Ctg|Asin|Acos|Atan|Ln|Deg Lparen add_expr Rparen)|
	 *           (Root|Log Lparen add_expr Comma add_expr)
	 * constant: Pi|E
	 */

	auto tree = add_expr();
	eat(Token::Eof);

	if(!errors.empty()) return lexer.get_errors() + errors;

	return std::make_pair(std::move(tree), lexer.get_errors());
}
