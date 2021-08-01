#include "catch.hpp"
#include "Evaluator.hpp"
#include <cmath>

TEST_CASE("Evaluator performs basic operations", "[evaluator]") {
	// 1 + (2 * 3^4) / 5
	
	std::unique_ptr<ASTNode> one = std::make_unique<NumberNode>(1);
	std::unique_ptr<ASTNode> two = std::make_unique<NumberNode>(2);
	std::unique_ptr<ASTNode> three = std::make_unique<NumberNode>(3);
	std::unique_ptr<ASTNode> four = std::make_unique<NumberNode>(4);
	std::unique_ptr<ASTNode> five = std::make_unique<NumberNode>(5);

	std::unique_ptr<ASTNode> pow = std::make_unique<BinOpNode>(BinOpNode::Pow, std::move(three), std::move(four));
	std::unique_ptr<ASTNode> mul = std::make_unique<BinOpNode>(BinOpNode::Mul, std::move(two), std::move(pow));
	std::unique_ptr<ASTNode> div = std::make_unique<BinOpNode>(BinOpNode::Div, std::move(mul), std::move(five));
	std::unique_ptr<ASTNode> add = std::make_unique<BinOpNode>(BinOpNode::Plus, std::move(one), std::move(div));

	Evaluator ev;
	auto maybe_res = ev.evaluate(add);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(res == 33.4);
}

TEST_CASE("Evaluator correctly interprets unary operations", "[evaluator]") {
	std::unique_ptr<ASTNode> one = std::make_unique<NumberNode>(1);
	std::unique_ptr<ASTNode> two = std::make_unique<NumberNode>(2);
	std::unique_ptr<ASTNode> plus = std::make_unique<UnOpNode>(UnOpNode::Plus, std::move(one));
	std::unique_ptr<ASTNode> minus = std::make_unique<UnOpNode>(UnOpNode::Minus, std::move(two));

	Evaluator ev;
	auto maybe_res = ev.evaluate(plus);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(res == 1);

	maybe_res = ev.evaluate(minus);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(res == -2);
}

TEST_CASE("Evaluator understands constants", "[evaluator]") {
	std::unique_ptr<ASTNode> pi = std::make_unique<ConstantNode>(ConstantNode::Pi);
	std::unique_ptr<ASTNode> e = std::make_unique<ConstantNode>(ConstantNode::E);

	Evaluator ev;
	auto maybe_res = ev.evaluate(pi);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - M_PI) < EPSILON);
	
	maybe_res = ev.evaluate(e);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - M_E) < EPSILON);
}

TEST_CASE("Evaluator understands trigonometric functions", "[evaluator]") {
	std::unique_ptr<ASTNode> pi = std::make_unique<ConstantNode>(ConstantNode::Pi);
	std::unique_ptr<ASTNode> pi2 = std::make_unique<NumberNode>(M_PI/2);
	std::unique_ptr<ASTNode> pi4 = std::make_unique<NumberNode>(M_PI/4);
	std::unique_ptr<ASTNode> pi4_2 = std::make_unique<NumberNode>(M_PI/4);

	std::unique_ptr<ASTNode> sin = std::make_unique<UnOpNode>(UnOpNode::Sin, std::move(pi2));
	std::unique_ptr<ASTNode> cos = std::make_unique<UnOpNode>(UnOpNode::Cos, std::move(pi));
	std::unique_ptr<ASTNode> tan = std::make_unique<UnOpNode>(UnOpNode::Tan, std::move(pi4));
	std::unique_ptr<ASTNode> ctg = std::make_unique<UnOpNode>(UnOpNode::Ctg, std::move(pi4_2));

	Evaluator ev;
	auto maybe_res = ev.evaluate(sin);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 1) < EPSILON);
	
	maybe_res = ev.evaluate(cos);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res + 1) < EPSILON);

	maybe_res = ev.evaluate(tan);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 1) < EPSILON);

	maybe_res = ev.evaluate(ctg);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 1) < EPSILON);
}

TEST_CASE("Evaluator rounds numbers floating-error-small to zero", "[evaluator]") {
	std::unique_ptr<ASTNode> pi = std::make_unique<ConstantNode>(ConstantNode::Pi);
	std::unique_ptr<ASTNode> sin = std::make_unique<UnOpNode>(UnOpNode::Sin, std::move(pi));

	Evaluator ev;
	auto maybe_res = ev.evaluate(sin);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(res == 0);

	std::unique_ptr<ASTNode> pi2 = std::make_unique<ConstantNode>(ConstantNode::Pi);
	std::unique_ptr<ASTNode> sin2 = std::make_unique<UnOpNode>(UnOpNode::Sin, std::move(pi2));
	std::unique_ptr<ASTNode> one = std::make_unique<NumberNode>(1);
	std::unique_ptr<ASTNode> div = std::make_unique<BinOpNode>(BinOpNode::Div, std::move(one), std::move(sin2));

	maybe_res = ev.evaluate(div);
	REQUIRE(std::holds_alternative<std::string>(maybe_res));
}

TEST_CASE("Evaluator understands cyclometric functions", "[evaluator]") {
	std::unique_ptr<ASTNode> one = std::make_unique<NumberNode>(1);
	std::unique_ptr<ASTNode> one2 = std::make_unique<NumberNode>(1);
	std::unique_ptr<ASTNode> m_one = std::make_unique<NumberNode>(-1);

	std::unique_ptr<ASTNode> asin = std::make_unique<UnOpNode>(UnOpNode::Asin, std::move(one));
	std::unique_ptr<ASTNode> acos = std::make_unique<UnOpNode>(UnOpNode::Acos, std::move(m_one));
	std::unique_ptr<ASTNode> atan = std::make_unique<UnOpNode>(UnOpNode::Atan, std::move(one2));

	Evaluator ev;
	auto maybe_res = ev.evaluate(asin);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - M_PI/2) < EPSILON);

	maybe_res = ev.evaluate(acos);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - M_PI) < EPSILON);

	maybe_res = ev.evaluate(atan);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - M_PI/4) < EPSILON);
}

TEST_CASE("Evaluator understands root functions", "[evaluator]") {
	std::unique_ptr<ASTNode> sixteen = std::make_unique<NumberNode>(16);
	std::unique_ptr<ASTNode> twenty_seven = std::make_unique<NumberNode>(27);
	std::unique_ptr<ASTNode> four = std::make_unique<NumberNode>(4);
	std::unique_ptr<ASTNode> alot = std::make_unique<NumberNode>(256);

	std::unique_ptr<ASTNode> sqrt = std::make_unique<UnOpNode>(UnOpNode::Sqrt, std::move(sixteen));
	std::unique_ptr<ASTNode> cbrt = std::make_unique<UnOpNode>(UnOpNode::Cbrt, std::move(twenty_seven));
	std::unique_ptr<ASTNode> root = std::make_unique<BinOpNode>(BinOpNode::Root, std::move(alot), std::move(four));

	Evaluator ev;
	auto maybe_res = ev.evaluate(sqrt);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 4) < EPSILON);

	maybe_res = ev.evaluate(cbrt);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 3) < EPSILON);

	maybe_res = ev.evaluate(root);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 4) < EPSILON);
}

TEST_CASE("Evaluator understands log functions", "[evaluator]") {
	std::unique_ptr<ASTNode> e = std::make_unique<ConstantNode>(ConstantNode::E);
	std::unique_ptr<ASTNode> nine = std::make_unique<NumberNode>(9);
	std::unique_ptr<ASTNode> eighty_one = std::make_unique<NumberNode>(81);

	std::unique_ptr<ASTNode> ln = std::make_unique<UnOpNode>(UnOpNode::Ln, std::move(e));
	std::unique_ptr<ASTNode> log = std::make_unique<BinOpNode>(BinOpNode::Log, std::move(eighty_one), std::move(nine));

	Evaluator ev;
	auto maybe_res = ev.evaluate(ln);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	auto res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 1) < EPSILON);

	maybe_res = ev.evaluate(log);
	REQUIRE(std::holds_alternative<double>(maybe_res));
	res = std::get<double>(maybe_res);
	REQUIRE(std::abs(res - 2) < EPSILON);
}

TEST_CASE("Evaluator returns errors", "[evaluator]") {
	// 1/0 + root(-2,2)
	std::unique_ptr<ASTNode> one = std::make_unique<NumberNode>(5);
	std::unique_ptr<ASTNode> zero = std::make_unique<NumberNode>(0);
	std::unique_ptr<ASTNode> m_two = std::make_unique<NumberNode>(-2);
	std::unique_ptr<ASTNode> two = std::make_unique<NumberNode>(2);

	std::unique_ptr<ASTNode> div = std::make_unique<BinOpNode>(BinOpNode::Div, std::move(one), std::move(zero));
	std::unique_ptr<ASTNode> root = std::make_unique<BinOpNode>(BinOpNode::Root, std::move(m_two), std::move(two));
	std::unique_ptr<ASTNode> add = std::make_unique<BinOpNode>(BinOpNode::Plus, std::move(div), std::move(root));

	Evaluator ev;
	auto maybe_res = ev.evaluate(add);
	REQUIRE(std::holds_alternative<std::string>(maybe_res));
}
