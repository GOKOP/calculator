#include <iostream>
#include <string>

#include "Parser.hpp"
#include "Evaluator.hpp"

int main() {
	std::string input;
	std::getline(std::cin, input);

	auto parser = Parser(input);
	auto tree = parser.parse();

	Evaluator ev;
	std::cout<<ev.evaluate(tree)<<std::endl;
}
