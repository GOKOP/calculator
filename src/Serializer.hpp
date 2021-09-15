#pragma once

#include "NumberNode.hpp"
#include "BinOpNode.hpp"
#include "UnOpNode.hpp"
#include "ConstantNode.hpp"
#include "NodeVisitor.hpp"

#include <string>

class Serializer: public NodeVisitor {
	std::string result;
public:
	Serializer();

	virtual void visit(const NumberNode& node) override;
	virtual void visit(const BinOpNode& node) override;
	virtual void visit(const UnOpNode& node) override;
	virtual void visit(const ConstantNode& node) override;
	
	std::string serialize(std::unique_ptr<ASTNode>& tree);
};
