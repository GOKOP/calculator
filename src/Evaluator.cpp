#include "Evaluator.hpp"
#include <cmath>

Evaluator::Evaluator(): 
	result(0),
	errors("")
{}

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
		case BinOpNode::Div: 
			if(right == 0) errors += "Error: division by zero\n";
			result = left/right; break;
		case BinOpNode::Pow: result = pow(left, right); break;
		case BinOpNode::Root: 
			if(fmod(right, 2) == 0 && left < 0) errors += "Error: Even root of a negative number\n";
			else if(left < 0) result = -pow(-left, 1/right);
			else result = pow(left, 1/right);
			break;
		case BinOpNode::Log:
			if(right == 1) errors += "Error: logarithm of base 1\n";
			else if(right < 0) errors += "Error: logarithm of negative base\n";
			else if(left < 0) errors += "Error: logarithm with negative argument\n";
			else if(right == 10) result = log10(left);
			else result = log(left) / log(right);
			break;
	}
}

void Evaluator::visit(UnOpNode& node) {
	node.arg->accept(*this);
	auto arg = result;

	switch(node.type) {
		case UnOpNode::Plus: result = arg; break;
		case UnOpNode::Minus: result = -arg; break;
		case UnOpNode::Sqrt: 
			if(arg < 0) errors += "Error: Square root of negative number\n";
			result = sqrt(arg); break;
		case UnOpNode::Cbrt: result = cbrt(arg); break;
		case UnOpNode::Sin: result = sin(arg); break;
		case UnOpNode::Cos: result = cos(arg); break;
		case UnOpNode::Tan: result = tan(arg); break;
		case UnOpNode::Ctg: result = 1/tan(arg); break;
		case UnOpNode::Asin: 
			if(arg < -1 || arg > 1) errors += "Error: arcsine out of <-1,1> range\n";
			result = asin(arg); break;
		case UnOpNode::Acos:
			if(arg < -1 || arg > 1) errors += "Error: arccosine out of <-1,1> range\n";
			result = acos(arg); break;
		case UnOpNode::Atan: result = atan(arg); break;
		case UnOpNode::Ln: 
			if(arg < 0) errors += "Error: logarithm with negative argument\n";
			else result = log(arg); 
			break;
	}
}

void Evaluator::visit(ConstantNode& node) {
	switch(node.type) {
		case ConstantNode::Pi: result = M_PI; break;
		case ConstantNode::E: result = M_E; break;
	}
}

std::variant<double, std::string> Evaluator::evaluate(std::unique_ptr<ASTNode>& tree) {
	tree->accept(*this);
	if(!errors.empty()) return errors;
	if(result < 1.0e-15 && result > -1.0e-15) result = 0;
	return result;
}
