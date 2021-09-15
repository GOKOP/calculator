#include "BinOpNode.hpp"
#include "NodeVisitor.hpp"

BinOpNode::BinOpNode(BinOpType type, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right):
	type(type),
	left(std::move(left)),
	right(std::move(right))
{}

void BinOpNode::accept(NodeVisitor& visitor) const {
	visitor.visit(*this);
}
