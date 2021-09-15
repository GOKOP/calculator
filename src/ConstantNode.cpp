#include "ConstantNode.hpp"
#include "NodeVisitor.hpp"

ConstantNode::ConstantNode(ConstantType type): type(type) {}

void ConstantNode::accept(NodeVisitor& visitor) const {
	visitor.visit(*this);
}
