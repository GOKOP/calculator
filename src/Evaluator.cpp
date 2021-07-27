#include "Evaluator.hpp"
#include <cmath>

Evaluator::Evaluator(): result(0) {}

void Evaluator::visit(NumberNode& node) {
	result = node.value;
}

void Evaluator::visit(BinOpNode& node) {
	node.left->accept(*this);
	auto left = result;

	node.right->accept(*this);
	auto right = result;

	switch(node.type) {
		case BinOpNode::Plus: result = left+right; break;
		case BinOpNode::Minus: result = left-right; break;
		case BinOpNode::Mul: result = left*right; break;
		case BinOpNode::Div: result = left/right; break;
		case BinOpNode::Pow: result = pow(left, right); break;
	}
}

double Evaluator::evaluate(std::unique_ptr<ASTNode>& tree) {
	tree->accept(*this);
	return result;
}
