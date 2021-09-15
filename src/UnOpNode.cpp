#include "UnOpNode.hpp"

UnOpNode::UnOpNode(UnOpType type, std::unique_ptr<ASTNode> arg):
	type(type),
	arg(std::move(arg))
{}

void UnOpNode::accept(NodeVisitor& vis) const {
	vis.visit(*this);
}
