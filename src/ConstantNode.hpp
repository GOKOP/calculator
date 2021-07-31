#pragma once

#include "ASTNode.hpp"

class ConstantNode: public ASTNode {
public:
	enum ConstantType {
		Pi,
		E
	};

	ConstantType type;

	ConstantNode(ConstantType type);
	virtual void accept(NodeVisitor& visitor) override;
};
