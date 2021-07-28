#include "Serializer.hpp"

Serializer::Serializer(): result("") {}

void Serializer::visit(NumberNode& node) {
	result += std::to_string(node.value);
	result.erase(result.find_last_not_of("0") + 1);
	if(result.back() == '.') result.pop_back();
}

void Serializer::visit(BinOpNode& node) {
	auto brackets = true;
	if(result.empty() || result.back() == '(') brackets = false;

	if(brackets) result += "(";
	node.left->accept(*this);

	switch(node.type) {
		case BinOpNode::Plus: result += " + "; break;
		case BinOpNode::Minus: result += " - "; break;
		case BinOpNode::Mul: result += " * "; break;
		case BinOpNode::Div: result += " / "; break;
		case BinOpNode::Pow: result += " ^ "; break;
	}

	node.right->accept(*this);
	if(brackets) result += ")";
}

void Serializer::visit(UnOpNode& node) {
	switch(node.type) {
	case UnOpNode::Plus:
		node.arg->accept(*this);
		break;
	case UnOpNode::Minus:
		result += '-';
		node.arg->accept(*this);
		break;
	case UnOpNode::Sqrt:
		result += "sqrt(";
		node.arg->accept(*this);
		result += ")";
		break;
	case UnOpNode::Cbrt:
		result += "cbrt(";
		node.arg->accept(*this);
		result += ")";
	}
}

std::string Serializer::serialize(std::unique_ptr<ASTNode>& tree) {
	tree->accept(*this);
	return result;
}
