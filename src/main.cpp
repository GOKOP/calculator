#include <iostream>

#include "Parser.hpp"

int main() {
	auto parser = Parser("14+22-5+3");
	auto tree = parser.parse();
}
