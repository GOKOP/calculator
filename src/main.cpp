#include <iostream>
#include <string>
#include <memory>

#include "Parser.hpp"
#include "Evaluator.hpp"

int main() {
	std::string input;

	while(true) {
		std::cout<<"> ";
		std::getline(std::cin, input);
	
		auto parser = Parser(input);
		std::unique_ptr<ASTNode> tree;

		auto maybe_tree = parser.parse();
		if(std::holds_alternative<std::unique_ptr<ASTNode>>(maybe_tree)) {
			auto tree = std::move(std::get<std::unique_ptr<ASTNode>>(maybe_tree));
			Evaluator ev;
			std::cout<<ev.evaluate(tree)<<std::endl;
		} else {
			std::cout<<std::get<std::string>(maybe_tree)<<std::endl;
		}
	}
}
