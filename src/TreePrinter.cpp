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
	TreePrinter vis;
	node.left->accept(vis);
	std::cout<<", ";
	node.right->accept(vis);
	std::cout<<")";
}

void TreePrinter::print(std::unique_ptr<ASTNode>& tree) {
	TreePrinter vis;
	tree->accept(vis);
	std::cout<<"\n";
}
