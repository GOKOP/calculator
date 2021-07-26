#include <iostream>

#include "Parser.hpp"
#include "Evaluator.hpp"

int main() {
	auto parser = Parser("14+22-5+3");
	auto tree = parser.parse();
	Evaluator ev;
	std::cout<<ev.evaluate(tree)<<std::endl;
}
