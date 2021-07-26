#pragma once

#include "NodeVisitor.hpp"
#include "ASTNode.hpp"
#include <memory>

class TreePrinter: public NodeVisitor {
public:
	virtual void visit(NumberNode& node) override;
	virtual void visit(BinOpNode& node) override;

	void print(std::unique_ptr<ASTNode>& tree);
};
