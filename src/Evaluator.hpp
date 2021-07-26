#pragma once

#include "NumberNode.hpp"
#include "BinOpNode.hpp"
#include "ASTNode.hpp"
#include "NodeVisitor.hpp"

class Evaluator: public NodeVisitor {
	int result;
public:
	Evaluator();

	virtual void visit(NumberNode& node) override;
	virtual void visit(BinOpNode& node) override;
	
	int evaluate(std::unique_ptr<ASTNode>& tree);
};
