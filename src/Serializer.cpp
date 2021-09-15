#include "Serializer.hpp"

#include <vector>

// helper functions

std::size_t match_bracket(const std::string& text, std::size_t pos) {
	if(pos >= text.size()) return std::string::npos;
	if(text[pos] != '(') return std::string::npos;

	auto brackets_open = 1;
	std::size_t i;
	for(i=pos+1; i<text.size(); ++i) {
		if(text[i] == '(') ++brackets_open;
		else if(text[i] == ')') --brackets_open;
		if(brackets_open == 0) break;
	}

	if(i > text.size()) return std::string::npos;
	if(text[i] != ')') return std::string::npos;
	return i;
}

std::string reduce_brackets(std::string text) {
	auto new_text = text;

	// see if the bracket at the beginning matches a bracket at the end
	if(text.front() == '(') {
		auto match = match_bracket(text, 0);

		if(match == text.size() - 1) {
			new_text.pop_back();
			new_text.erase(new_text.begin());
		}
	}
	
	// replace all matching double brackets with single brackets, rinse and repeat
	bool altered;
	do {
		altered = false;

		std::vector<std::size_t> positions;
		auto pos = new_text.find("((");
		while(pos != std::string::npos) {
			positions.push_back(pos);
			pos = new_text.find("((", pos+1);
		}

		if(positions.empty()) return new_text; // nothing more to do

		// starting from the last one allows modifying the string
		// without affecting positions of brackes that are left to check
		for(auto cur_pos = positions.end()-1; cur_pos>=positions.begin(); --cur_pos) {
			auto first_match = match_bracket(new_text, *cur_pos);
			auto sec_match = match_bracket(new_text, *cur_pos+1);

			if(first_match != std::string::npos && 
			   sec_match != std::string::npos &&
			   first_match == sec_match + 1) 
			{
				new_text.erase(first_match, 1);
				new_text.erase(*cur_pos, 1);
				altered = true;
			}
		}
	} while(altered);


	return new_text;
}

// end of helper functions

Serializer::Serializer(): result("") {}

void Serializer::visit(const NumberNode& node) {
	result += std::to_string(node.value);
	result.erase(result.find_last_not_of("0") + 1);
	if(result.back() == '.') result.pop_back();
}

void Serializer::visit(const BinOpNode& node) {
	if(node.type == BinOpNode::Root || node.type == BinOpNode::Log) {

		switch(node.type) {
			case BinOpNode::Root: result += "root("; break;
			case BinOpNode::Log: result += "log("; break;
			default: break;
		}
		node.left->accept(*this);
		result += ", ";
		node.right->accept(*this);
		result += ")";
		return;
	}

	result += "(";
	node.left->accept(*this);

	switch(node.type) {
		case BinOpNode::Plus: result += " + "; break;
		case BinOpNode::Minus: result += " - "; break;
		case BinOpNode::Mul: result += " * "; break;
		case BinOpNode::Div: result += " / "; break;
		case BinOpNode::Pow: result += " ^ "; break;
		default: break; // checked before to not be the case
	}

	node.right->accept(*this);
	result += ")";
}

void Serializer::visit(const UnOpNode& node) {
	switch(node.type) {
		case UnOpNode::Plus: break;
		case UnOpNode::Minus: result += '-'; break;
		case UnOpNode::Sqrt: result += "sqrt("; break;
		case UnOpNode::Cbrt: result += "cbrt("; break;
		case UnOpNode::Sin: result += "sin("; break;
		case UnOpNode::Cos: result += "cos("; break;
		case UnOpNode::Tan: result += "tan("; break;
		case UnOpNode::Ctg: result += "ctg("; break;
		case UnOpNode::Asin: result += "asin("; break;
		case UnOpNode::Acos: result += "acos("; break;
		case UnOpNode::Atan: result += "atan("; break;
		case UnOpNode::Ln: result += "ln("; break;
		case UnOpNode::Deg: result += "deg("; break;
	}

	node.arg->accept(*this);
	if(node.type != UnOpNode::Plus && node.type != UnOpNode::Minus) result += ")";
}

void Serializer::visit(const ConstantNode& node) {
	switch(node.type) {
		case ConstantNode::Pi: result += "pi"; break;
		case ConstantNode::E: result += "e"; break;
	}
}

std::string Serializer::serialize(std::unique_ptr<ASTNode>& tree) {
	tree->accept(*this);
	return reduce_brackets(result);
}
