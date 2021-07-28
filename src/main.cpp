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
		if(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string>>(maybe_tree)) {
			auto res = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string>>(maybe_tree));
			Evaluator ev;
			if(!res.second.empty()) std::cout<<res.second;
			std::cout<<ev.evaluate(res.first)<<std::endl;
		} else {
			std::cout<<std::get<std::string>(maybe_tree)<<std::endl;
		}
	}
}
