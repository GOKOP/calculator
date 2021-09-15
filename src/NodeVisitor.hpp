#pragma once

class NumberNode;
class BinOpNode;
class UnOpNode;
class ConstantNode;

class NodeVisitor {
public:
	virtual void visit(const NumberNode& node) = 0;
	virtual void visit(const BinOpNode& node) = 0;
	virtual void visit(const UnOpNode& node) = 0;
	virtual void visit(const ConstantNode& node) = 0;
};
