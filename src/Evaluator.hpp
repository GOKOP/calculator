#pragma once

#include "NumberNode.hpp"
#include "BinOpNode.hpp"
#include "ASTNode.hpp"
#include "NodeVisitor.hpp"

class Evaluator: public NodeVisitor {
	double result;
public:
	Evaluator();

	virtual void visit(NumberNode& node) override;
	virtual void visit(BinOpNode& node) override;
	
	double evaluate(std::unique_ptr<ASTNode>& tree);
};
