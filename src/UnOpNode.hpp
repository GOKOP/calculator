#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "NodeVisitor.hpp"

class UnOpNode: public ASTNode {
public:
	enum UnOpType {
		Plus,
		Minus
	};

	UnOpType type;
	std::unique_ptr<ASTNode> arg;

	UnOpNode(UnOpType type, std::unique_ptr<ASTNode> arg);
	virtual void accept(NodeVisitor& vis) override;
};
