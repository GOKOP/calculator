#include "NumberNode.hpp"
#include "NodeVisitor.hpp"

NumberNode::NumberNode(double value): value(value) {}

void NumberNode::accept(NodeVisitor& visitor) {
	visitor.visit(*this);
}
