#pragma once

class NumberNode;
class BinOpNode;
class UnOpNode;
class ConstantNode;

class NodeVisitor {
public:
	virtual void visit(NumberNode& node) = 0;
	virtual void visit(BinOpNode& node) = 0;
	virtual void visit(UnOpNode& node) = 0;
	virtual void visit(ConstantNode& node) = 0;
};
