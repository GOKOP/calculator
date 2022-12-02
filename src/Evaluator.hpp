#pragma once

#include "NumberNode.hpp"
#include "BinOpNode.hpp"
#include "UnOpNode.hpp"
#include "ConstantNode.hpp"
#include "NodeVisitor.hpp"

#include <string>
#include <variant>

#define EPSILON 1.0e-15

class Evaluator: public NodeVisitor {
	double result;
	std::string errors;
public:
	Evaluator();

	virtual void visit(const NumberNode& node) override;
	virtual void visit(const BinOpNode& node) override;
	virtual void visit(const UnOpNode& node) override;
	virtual void visit(const ConstantNode& node) override;
	
	std::variant<double, std::string_view> evaluate(std::unique_ptr<ASTNode>& tree);
};
