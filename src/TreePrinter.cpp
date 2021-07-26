#include "TreePrinter.hpp"
#include "NumberNode.hpp"
#include "BinOpNode.hpp"

#include <iostream>

void TreePrinter::visit(NumberNode& node) {
	std::cout<<"Number("<<node.value<<")";
}

void TreePrinter::visit(BinOpNode& node) {
	if(node.type == BinOpNode::Plus) std::cout<<"Plus(";
	else if(node.type == BinOpNode::Minus) std::cout<<"Minus(";
	node.left->accept(*this);
	std::cout<<", ";
	node.right->accept(*this);
	std::cout<<")";
}

void TreePrinter::print(std::unique_ptr<ASTNode>& tree) {
	tree->accept(*this);
	std::cout<<"\n";
}
