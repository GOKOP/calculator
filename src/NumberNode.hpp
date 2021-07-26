#pragma once

#include "ASTNode.hpp"

class NumberNode: public ASTNode {
public:
	int value;
	NumberNode(int value);
	virtual void accept(NodeVisitor& visitor) override;
};
