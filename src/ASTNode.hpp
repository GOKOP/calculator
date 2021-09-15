#pragma once

class NodeVisitor;

class ASTNode {
public:
	virtual void accept(NodeVisitor& visitor) const = 0;
	virtual ~ASTNode() {};
};

