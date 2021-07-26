#pragma once

class NodeVisitor;

class ASTNode {
public:
	virtual void accept(NodeVisitor& visitor) = 0;
	virtual ~ASTNode() {};
};

