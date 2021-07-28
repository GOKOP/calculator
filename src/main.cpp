#include <iostream>
#include <string>
#include <memory>

#include "Parser.hpp"
#include "Evaluator.hpp"
#include "Serializer.hpp"

void print_help() {
	std::cout<<"Valid operations:\n"
		"(x and y are numbers, named functions or expressions in parentheses)\n"
		"+x\t\tunary plus\n"
		"-y\t\tunary minus\n"
		"x + y\t\taddition\n"
		"x - y\t\tsubtraction\n"
		"x * y\t\tmultiplication\n"
		"x / y\t\tdivision\n"
		"x ^ y\t\tx to the power of y\n"
		"sqrt(x)\t\tsquare root\n"
		"cbrt(x)\t\tcubic root\n"
		"root(x, y)\troot of base y\n"
		"sin(x)\t\tsine\n"
		"cos(x)\t\tcosine\n"
		"tan(x)\t\ttangent\n"
		"ctg(x)\t\tcotangent\n"
		"asin(x)\t\tarcsine\n"
		"acos(x)\t\tarccosine\n"
		"atan(x)\t\tarctangent\n";
}

int main() {
	std::cout<<"Type ':q' to quit, ':h' for help"<<std::endl;
	std::string input;

	while(true) {
		std::cout<<"> ";
		std::getline(std::cin, input);

		if(input == ":q") break;
		if(input == ":h") {
			print_help();
			continue;
		}
	
		auto parser = Parser(input);
		std::unique_ptr<ASTNode> tree;

		auto maybe_tree = parser.parse();
		if(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string>>(maybe_tree)) {
			auto res = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string>>(maybe_tree));

			if(!res.second.empty()) std::cout<<res.second;

			Evaluator ev;
			Serializer se;

			std::cout<<se.serialize(res.first)<<" = "<<ev.evaluate(res.first)<<std::endl;
		} else {
			std::cout<<std::get<std::string>(maybe_tree)<<std::endl;
		}
	}
}
