#pragma once

#include <memory>
#include "ASTNode.hpp"

class BinOpNode: public ASTNode {
public:
	enum BinOpType {
		Plus,
		Minus,
		Mul,
		Div
	};

	BinOpType type;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;

	BinOpNode(BinOpType type, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);
	virtual void accept(NodeVisitor& visitor) override;
};
