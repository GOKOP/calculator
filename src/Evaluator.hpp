#pragma once

#include "NumberNode.hpp"
#include "BinOpNode.hpp"
#include "UnOpNode.hpp"
#include "NodeVisitor.hpp"

#include <string>
#include <variant>

class Evaluator: public NodeVisitor {
	double result;
	std::string errors;
public:
	Evaluator();

	virtual void visit(NumberNode& node) override;
	virtual void visit(BinOpNode& node) override;
	virtual void visit(UnOpNode& node) override;
	
	std::variant<double, std::string> evaluate(std::unique_ptr<ASTNode>& tree);
};
