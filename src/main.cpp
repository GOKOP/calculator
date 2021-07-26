#include <iostream>

#include "Parser.hpp"
#include "TreePrinter.hpp"

int main() {
	auto parser = Parser("14+22-5+3");
	auto tree = parser.parse();
	TreePrinter printer;
	printer.print(tree);
}
