#include "NumberNode.hpp"
#include "NodeVisitor.hpp"

NumberNode::NumberNode(double value): value(value) {}

void NumberNode::accept(NodeVisitor& visitor) const {
	visitor.visit(*this);
}
