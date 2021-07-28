#include "Serializer.hpp"

Serializer::Serializer(): result("") {}

void Serializer::visit(NumberNode& node) {
	result += std::to_string(node.value);
	result.erase(result.find_last_not_of("0") + 1);
	if(result.back() == '.') result.pop_back();
}

void Serializer::visit(BinOpNode& node) {
	if(node.type == BinOpNode::Root) {
		result += "root(";
		node.left->accept(*this);
		result += ", ";
		node.right->accept(*this);
		result += ")";
		return;
	}

	auto brackets = true;
	if(result.empty() || result.back() == '(' ||
	   (result.back() == ' ' && result.at(result.size()-2) == ',')) brackets = false;

	if(brackets) result += "(";
	node.left->accept(*this);

	switch(node.type) {
		case BinOpNode::Plus: result += " + "; break;
		case BinOpNode::Minus: result += " - "; break;
		case BinOpNode::Mul: result += " * "; break;
		case BinOpNode::Div: result += " / "; break;
		case BinOpNode::Pow: result += " ^ "; break;
		default: break; // checked before to not be the case
	}

	node.right->accept(*this);
	if(brackets) result += ")";
}

void Serializer::visit(UnOpNode& node) {
	switch(node.type) {
		case UnOpNode::Plus: break;
		case UnOpNode::Minus: result += '-'; break;
		case UnOpNode::Sqrt: result += "sqrt("; break;
		case UnOpNode::Cbrt: result += "cbrt("; break;
		case UnOpNode::Sin: result += "sin("; break;
		case UnOpNode::Cos: result += "cos("; break;
		case UnOpNode::Tan: result += "tan("; break;
		case UnOpNode::Ctg: result += "ctg("; break;
		case UnOpNode::Asin: result += "asin("; break;
		case UnOpNode::Acos: result += "acos("; break;
		case UnOpNode::Atan: result += "atan("; break;
	}

	node.arg->accept(*this);
	if(node.type != UnOpNode::Plus && node.type != UnOpNode::Minus) result += ")";
}

std::string Serializer::serialize(std::unique_ptr<ASTNode>& tree) {
	tree->accept(*this);
	return result;
}
