#pragma once

class NumberNode;
class BinOpNode;

class NodeVisitor {
public:
	virtual void visit(NumberNode& node) = 0;
	virtual void visit(BinOpNode& node) = 0;
};
