#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

#include "Parser.hpp"
#include "Evaluator.hpp"

int main() {
	std::string input;

	while(true) {
		std::getline(std::cin, input);
	
		auto parser = Parser(input);
		std::unique_ptr<ASTNode> tree;

		try {
			tree = parser.parse();
		} 
		catch(std::runtime_error e) {
			std::cout<<e.what()<<std::endl;
			continue;
		}

		Evaluator ev;
		std::cout<<ev.evaluate(tree)<<std::endl;
	}
}
