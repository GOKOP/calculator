#include "catch.hpp"
#include "Parser.hpp"
#include "BinOpNode.hpp"
#include "UnOpNode.hpp"
#include "NumberNode.hpp"
#include "ConstantNode.hpp"

TEST_CASE("Parser generates AST with correct order of operations", "[parser]") {
	auto parser = Parser("1+2^3*4");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	// tree should start with addition operation
	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Plus);
	
	// left argument should be 1
	std::unique_ptr<NumberNode> left;
	REQUIRE_NOTHROW(left = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*binop->left)));
	REQUIRE(left->value == 1);
	
	// right argument should be multiplication
	std::unique_ptr<BinOpNode> right;
	REQUIRE_NOTHROW(right = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop->right))));
	REQUIRE(right->type == BinOpNode::Mul);
	
	// its left argument should be power operation 2^3
	std::unique_ptr<BinOpNode> mul_left;
	REQUIRE_NOTHROW(mul_left = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*right->left))));
	REQUIRE(mul_left->type == BinOpNode::Pow);

	std::unique_ptr<NumberNode> pow_left;
	REQUIRE_NOTHROW(pow_left = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*mul_left->left)));
	REQUIRE(pow_left->value == 2);

	std::unique_ptr<NumberNode> pow_right;
	REQUIRE_NOTHROW(pow_right = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*mul_left->right)));
	REQUIRE(pow_right->value == 3);
	
	// multiplication's right argument should be 4
	std::unique_ptr<NumberNode> mul_right;
	REQUIRE_NOTHROW(mul_right = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*right->right)));
	REQUIRE(mul_right->value == 4);
}

TEST_CASE("Parser gives parentheses precendence", "[parser]") {
	auto parser = Parser("(1+2)*3");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	// tree should start with multiplication
	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Mul);
	
	// left argument should be addition
	std::unique_ptr<BinOpNode> left;
	REQUIRE_NOTHROW(left = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop->left))));
	REQUIRE(left->type == BinOpNode::Plus);

	// its left argument should be 1
	std::unique_ptr<NumberNode> plus_left;
	REQUIRE_NOTHROW(plus_left = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*left->left)));
	REQUIRE(plus_left->value == 1);

	// right argument should be 2
	std::unique_ptr<NumberNode> plus_right;
	REQUIRE_NOTHROW(plus_right = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*left->right)));
	REQUIRE(plus_right->value == 2);
	
	// multiplication's right argument should be 3
	std::unique_ptr<NumberNode> right;
	REQUIRE_NOTHROW(right = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*binop->right)));
	REQUIRE(right->value == 3);
}

TEST_CASE("Parser understands unary operations", "[parser]") {
	auto parser = Parser("+3+(-2)");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	// starting node should be addition
	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Plus);

	// left argument should unary plus with the argument 3
	std::unique_ptr<UnOpNode> left;
	REQUIRE_NOTHROW(left = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop->left))));
	REQUIRE(left->type == UnOpNode::Plus);

	std::unique_ptr<NumberNode> unplus_arg;
	REQUIRE_NOTHROW(unplus_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*left->arg)));
	REQUIRE(unplus_arg->value == 3);

	// addition's right argument should be unary minus with argument 2
	std::unique_ptr<UnOpNode> right;
	REQUIRE_NOTHROW(right = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop->right))));
	REQUIRE(right->type == UnOpNode::Minus);

	std::unique_ptr<NumberNode> unminus_arg;
	REQUIRE_NOTHROW(unminus_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*right->arg)));
	REQUIRE(unminus_arg->value == 2);
}

TEST_CASE("Parser understands constants", "[parser]") {
	auto parser = Parser("pi + e");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Plus);

	std::unique_ptr<ConstantNode> left;
	REQUIRE_NOTHROW(left = std::make_unique<ConstantNode>(dynamic_cast<ConstantNode&>(*binop->left)));
	REQUIRE(left->type == ConstantNode::Pi);

	std::unique_ptr<ConstantNode> right;
	REQUIRE_NOTHROW(right = std::make_unique<ConstantNode>(dynamic_cast<ConstantNode&>(*binop->right)));
	REQUIRE(right->type == ConstantNode::E);
}

TEST_CASE("Parser understands trigonometric functions", "[parser]") {
	auto parser = Parser("sin(1) + cos(2) + tan(3) + ctg(4)");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	// the tree structure will be ((sin(1) + cos(2)) + tan(3)) + ctg(4)
	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Plus);

	std::unique_ptr<BinOpNode> binop2;
	REQUIRE_NOTHROW(binop2 = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop->left))));
	REQUIRE(binop2->type == BinOpNode::Plus);

	std::unique_ptr<BinOpNode> binop3;
	REQUIRE_NOTHROW(binop3 = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop2->left))));
	REQUIRE(binop3->type == BinOpNode::Plus);

	std::unique_ptr<UnOpNode> sine;
	REQUIRE_NOTHROW(sine = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop3->left))));
	REQUIRE(sine->type == UnOpNode::Sin);

	std::unique_ptr<NumberNode> sine_arg;
	REQUIRE_NOTHROW(sine_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*sine->arg)));
	REQUIRE(sine_arg->value == 1);

	std::unique_ptr<UnOpNode> cosine;
	REQUIRE_NOTHROW(cosine = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop3->right))));
	REQUIRE(cosine->type == UnOpNode::Cos);

	std::unique_ptr<NumberNode> cosine_arg;
	REQUIRE_NOTHROW(cosine_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*cosine->arg)));
	REQUIRE(cosine_arg->value == 2);

	std::unique_ptr<UnOpNode> tangent;
	REQUIRE_NOTHROW(tangent = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop2->right))));
	REQUIRE(tangent->type == UnOpNode::Tan);

	std::unique_ptr<NumberNode> tangent_arg;
	REQUIRE_NOTHROW(tangent_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*tangent->arg)));
	REQUIRE(tangent_arg->value == 3);

	std::unique_ptr<UnOpNode> cotangent;
	REQUIRE_NOTHROW(cotangent = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop->right))));
	REQUIRE(cotangent->type == UnOpNode::Ctg);

	std::unique_ptr<NumberNode> cotangent_arg;
	REQUIRE_NOTHROW(cotangent_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*cotangent->arg)));
	REQUIRE(cotangent_arg->value == 4);

}

TEST_CASE("Parser understands cyclometric functions", "[parser]") {
	auto parser = Parser("asin(1) + acos(2) + atan(3)");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Plus);

	std::unique_ptr<BinOpNode> binop2;
	REQUIRE_NOTHROW(binop2 = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop->left))));
	REQUIRE(binop2->type == BinOpNode::Plus);

	std::unique_ptr<UnOpNode> arcsine;
	REQUIRE_NOTHROW(arcsine = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop2->left))));
	REQUIRE(arcsine->type == UnOpNode::Asin);

	std::unique_ptr<NumberNode> arcsine_arg;
	REQUIRE_NOTHROW(arcsine_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*arcsine->arg)));
	REQUIRE(arcsine_arg->value == 1);

	std::unique_ptr<UnOpNode> arccosine;
	REQUIRE_NOTHROW(arccosine = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop2->right))));
	REQUIRE(arccosine->type == UnOpNode::Acos);

	std::unique_ptr<NumberNode> arccosine_arg;
	REQUIRE_NOTHROW(arccosine_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*arccosine->arg)));
	REQUIRE(arccosine_arg->value == 2);

	std::unique_ptr<UnOpNode> arctangent;
	REQUIRE_NOTHROW(arctangent = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop->right))));
	REQUIRE(arctangent->type == UnOpNode::Atan);

	std::unique_ptr<NumberNode> arctangent_arg;
	REQUIRE_NOTHROW(arctangent_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*arctangent->arg)));
	REQUIRE(arctangent_arg->value == 3);
}

TEST_CASE("Parser understands root functions", "[parser]") {
	auto parser = Parser("sqrt(1) + cbrt(2) + root(3, 4)");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Plus);

	std::unique_ptr<BinOpNode> binop2;
	REQUIRE_NOTHROW(binop2 = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop->left))));
	REQUIRE(binop2->type == BinOpNode::Plus);

	std::unique_ptr<UnOpNode> sqrt;
	REQUIRE_NOTHROW(sqrt = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop2->left))));
	REQUIRE(sqrt->type == UnOpNode::Sqrt);

	std::unique_ptr<NumberNode> sqrt_arg;
	REQUIRE_NOTHROW(sqrt_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*sqrt->arg)));
	REQUIRE(sqrt_arg->value == 1);

	std::unique_ptr<UnOpNode> cbrt;
	REQUIRE_NOTHROW(cbrt = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop2->right))));
	REQUIRE(cbrt->type == UnOpNode::Cbrt);

	std::unique_ptr<NumberNode> cbrt_arg;
	REQUIRE_NOTHROW(cbrt_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*cbrt->arg)));
	REQUIRE(cbrt_arg->value == 2);

	std::unique_ptr<BinOpNode> root;
	REQUIRE_NOTHROW(root = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop->right))));
	REQUIRE(root->type == BinOpNode::Root);

	std::unique_ptr<NumberNode> root_left;
	REQUIRE_NOTHROW(root_left = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*root->left)));
	REQUIRE(root_left->value == 3);

	std::unique_ptr<NumberNode> root_right;
	REQUIRE_NOTHROW(root_right = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*root->right)));
	REQUIRE(root_right->value == 4);
}

TEST_CASE("Parser understands logarithm functions", "[parser]") {
	auto parser = Parser("ln(1) + log(2,3)");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);

	std::unique_ptr<BinOpNode> binop;
	REQUIRE_NOTHROW(binop = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*tree))));
	REQUIRE(binop->type == BinOpNode::Plus);

	std::unique_ptr<UnOpNode> ln;
	REQUIRE_NOTHROW(ln = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*binop->left))));
	REQUIRE(ln->type == UnOpNode::Ln);

	std::unique_ptr<NumberNode> ln_arg;
	REQUIRE_NOTHROW(ln_arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*ln->arg)));
	REQUIRE(ln_arg->value == 1);

	std::unique_ptr<BinOpNode> log;
	REQUIRE_NOTHROW(log = std::make_unique<BinOpNode>(std::move(dynamic_cast<BinOpNode&>(*binop->right))));
	REQUIRE(log->type == BinOpNode::Log);

	std::unique_ptr<NumberNode> log_left;
	REQUIRE_NOTHROW(log_left = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*log->left)));
	REQUIRE(log_left->value == 2);

	std::unique_ptr<NumberNode> log_right;
	REQUIRE_NOTHROW(log_right = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*log->right)));
	REQUIRE(log_right->value == 3);
}

TEST_CASE("Parser passes on lexer errors", "[parser]") {
	auto parser = Parser("%4+dud 2!");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto errs = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).second);

	REQUIRE(!errs.empty());
}

TEST_CASE("Parser returns syntax errors", "[parser]") {
	auto parser = Parser("3+");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::string>(maybe_tree));
	auto errs = std::get<std::string>(maybe_tree);
	REQUIRE(!errs.empty());

	parser = Parser("2+log(4)");
	maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::string>(maybe_tree));
	errs = std::get<std::string>(maybe_tree);
	REQUIRE(!errs.empty());

	parser = Parser("*7+2");
	maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::string>(maybe_tree));
	errs = std::get<std::string>(maybe_tree);
	REQUIRE(!errs.empty());

	parser = Parser("");
	maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::string>(maybe_tree));
	errs = std::get<std::string>(maybe_tree);
	REQUIRE(!errs.empty());

	parser = Parser("sin(4");
	maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::string>(maybe_tree));
	errs = std::get<std::string>(maybe_tree);
	REQUIRE(!errs.empty());
}

TEST_CASE("Parser understands the deg function", "[parser]") {
	auto parser = Parser("deg(90)");
	auto maybe_tree = parser.parse();

	REQUIRE(std::holds_alternative<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree));
	auto tree = std::move(std::get<std::pair<std::unique_ptr<ASTNode>, std::string_view>>(maybe_tree).first);
	
	std::unique_ptr<UnOpNode> deg;
	REQUIRE_NOTHROW(deg = std::make_unique<UnOpNode>(std::move(dynamic_cast<UnOpNode&>(*tree))));
	REQUIRE(deg->type == UnOpNode::Deg);

	std::unique_ptr<NumberNode> arg;
	REQUIRE_NOTHROW(arg = std::make_unique<NumberNode>(dynamic_cast<NumberNode&>(*deg->arg)));
	REQUIRE(arg->value == 90);
}
