#include "NumberNode.hpp"
#include "NodeVisitor.hpp"

NumberNode::NumberNode(int value): value(value) {}

void NumberNode::accept(NodeVisitor& visitor) {
	visitor.visit(*this);
}
