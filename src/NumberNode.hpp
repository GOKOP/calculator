#pragma once

#include "ASTNode.hpp"

class NumberNode: public ASTNode {
public:
	double value;
	NumberNode(double value);
	virtual void accept(NodeVisitor& visitor) const override;
};
