#pragma once

class BinOpNode: ASTNode {
public:
	enum BinOpType {
		Plus,
		Minus
	};

	BinOpType type;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;
};
