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
		case BinOpNode::Root: result = pow(left, 1/right); break;
	}
}

void Evaluator::visit(UnOpNode& node) {
	node.arg->accept(*this);
	auto arg = result;

	switch(node.type) {
		case UnOpNode::Plus: result = arg; break;
		case UnOpNode::Minus: result = -arg; break;
		case UnOpNode::Sqrt: result = sqrt(arg); break;
		case UnOpNode::Cbrt: result = cbrt(arg); break;
		case UnOpNode::Sin: result = sin(arg); break;
		case UnOpNode::Cos: result = cos(arg); break;
		case UnOpNode::Tan: result = tan(arg); break;
		case UnOpNode::Ctg: result = 1/tan(arg); break;
		case UnOpNode::Asin: result = asin(arg); break;
		case UnOpNode::Acos: result = acos(arg); break;
		case UnOpNode::Atan: result = atan(arg); break;
	}
}

double Evaluator::evaluate(std::unique_ptr<ASTNode>& tree) {
	tree->accept(*this);
	return result;
}
