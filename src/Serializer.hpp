#pragma once

#include "NumberNode.hpp"
#include "BinOpNode.hpp"
#include "UnOpNode.hpp"
#include "NodeVisitor.hpp"

#include <string>

class Serializer: public NodeVisitor {
	std::string result;
public:
	Serializer();

	virtual void visit(NumberNode& node) override;
	virtual void visit(BinOpNode& node) override;
	virtual void visit(UnOpNode& node) override;
	
	std::string serialize(std::unique_ptr<ASTNode>& tree);
};
