#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

#include "Parser.hpp"
#include "Evaluator.hpp"
#include "Serializer.hpp"

void print_help() {
	std::cout<<"Valid operations:\n"
		"(x and y are numbers, constants, named functions or expressions in parentheses)\n"
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
		"deg(x)\t\tconvert degrees to radians\n"
		"asin(x)\t\tarcsine\n"
		"acos(x)\t\tarccosine\n"
		"atan(x)\t\tarctangent\n"
		"ln(x)\t\tnatural logarithm\n"
		"log(x, y)\tlogarithm of base y\n\n"
		"Valid constants are:\n"
		"pi\t\tpi\n"
		"e\t\te\n";
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
		auto maybe_tree = parser.parse();
		if(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string>>(maybe_tree)) {
			auto res = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string>>(maybe_tree));

			if(!res.second.empty()) std::cout<<res.second;

			Evaluator ev;
			Serializer se;

			auto equation = se.serialize(res.first);
			auto maybe_result = ev.evaluate(res.first);

			if(std::holds_alternative<double>(maybe_result)) {
				std::cout<<std::setprecision(15)<<equation<<" = "<<std::get<double>(maybe_result)<<std::endl;
			} else {
				std::cout<<equation<<std::endl<<std::get<std::string>(maybe_result);
			}

		} else {
			std::cout<<std::get<std::string>(maybe_tree)<<std::endl;
		}
	}
}
