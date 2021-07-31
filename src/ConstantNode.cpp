#include "ConstantNode.hpp"
#include "NodeVisitor.hpp"

ConstantNode::ConstantNode(ConstantType type): type(type) {}

void ConstantNode::accept(NodeVisitor& visitor) {
	visitor.visit(*this);
}
