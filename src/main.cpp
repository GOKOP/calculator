#include <iostream>
#include <string>
#include <memory>

#include "Parser.hpp"
#include "Evaluator.hpp"
#include "Serializer.hpp"

void print_help() {
	std::cout<<"Valid operations:\n"
		"(x and y are numbers, named functions or expressions in parentheses)\n"
		"+x\n"
		"-y\n"
		"x + y\n"
		"x - y\n"
		"x * y\n"
		"x / y\n"
		"x ^ y\n"
		"sqrt(x)\n"
		"cbrt(x)\n"
		"root(x, y)\n"
		"sin(x)\n"
		"cos(x)\n"
		"tan(x)\n"
		"ctg(x)\n"
		"asin(x)\n"
		"acos(x)\n"
		"atan(x)\n";
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
