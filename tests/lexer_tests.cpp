#include "catch.hpp"
#include "Lexer.hpp"

TEST_CASE("Lexer generates correct tokens for basic operations", "[lexer]") {
	auto lexer = Lexer("2+(1-3)*6^3/2");
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 2});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 3});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 1, 4});
	REQUIRE(lexer.get_next_token() == Token {Token::Minus, 0, 5});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 3, 6});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 7});
	REQUIRE(lexer.get_next_token() == Token {Token::Mul, 0, 8});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 6, 9});
	REQUIRE(lexer.get_next_token() == Token {Token::Pow, 0, 10});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 3, 11});
	REQUIRE(lexer.get_next_token() == Token {Token::Div, 0, 12});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 13});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 14});
	REQUIRE(lexer.get_errors().empty());
}

TEST_CASE("Lexer ignores whitespace", "[lexer]") {
	auto lexer = Lexer("2     +1\t\t/3\n*2");
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 7});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 1, 8});
	REQUIRE(lexer.get_next_token() == Token {Token::Div, 0, 11});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 3, 12});
	REQUIRE(lexer.get_next_token() == Token {Token::Mul, 0, 14});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 15});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 16});
	REQUIRE(lexer.get_errors().empty());
}

TEST_CASE("Lexer generates correct tokens for constants", "[lexer]") {
	auto lexer = Lexer("pi + pi/2 * e");
	REQUIRE(lexer.get_next_token() == Token {Token::Pi, 0, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 4});
	REQUIRE(lexer.get_next_token() == Token {Token::Pi, 0, 6});
	REQUIRE(lexer.get_next_token() == Token {Token::Div, 0, 8});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 9});
	REQUIRE(lexer.get_next_token() == Token {Token::Mul, 0, 11});
	REQUIRE(lexer.get_next_token() == Token {Token::E, 0, 13});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 14});
	REQUIRE(lexer.get_errors().empty());
}

TEST_CASE("Lexer generates correct tokens for trigonometric functions", "[lexer]") {
	auto lexer = Lexer("sin(10) + cos(2) / tan(1) * ctg(3)");
	REQUIRE(lexer.get_next_token() == Token {Token::Sin, 0, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 4});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 10, 5});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 7});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 9});
	REQUIRE(lexer.get_next_token() == Token {Token::Cos, 0, 11});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 14});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 15});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 16});
	REQUIRE(lexer.get_next_token() == Token {Token::Div, 0, 18});
	REQUIRE(lexer.get_next_token() == Token {Token::Tan, 0, 20});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 23});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 1, 24});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 25});
	REQUIRE(lexer.get_next_token() == Token {Token::Mul, 0, 27});
	REQUIRE(lexer.get_next_token() == Token {Token::Ctg, 0, 29});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 32});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 3, 33});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 34});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 35});
	REQUIRE(lexer.get_errors().empty());
}

TEST_CASE("Lexer generates correct tokens for cyclometric functions", "[lexer]") {
	auto lexer = Lexer("asin(10) + acos(2) / atan(5)");
	REQUIRE(lexer.get_next_token() == Token {Token::Asin, 0, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 5});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 10, 6});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 8});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 10});
	REQUIRE(lexer.get_next_token() == Token {Token::Acos, 0, 12});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 16});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 17});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 18});
	REQUIRE(lexer.get_next_token() == Token {Token::Div, 0, 20});
	REQUIRE(lexer.get_next_token() == Token {Token::Atan, 0, 22});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 26});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 5, 27});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 28});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 29});
	REQUIRE(lexer.get_errors().empty());
}

TEST_CASE("Lexer generates correct tokens for root functions", "[lexer]") {
	auto lexer = Lexer("sqrt(4) + cbrt(8) + root(256,4)");
	REQUIRE(lexer.get_next_token() == Token {Token::Sqrt, 0, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 5});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 4, 6});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 7});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 9});
	REQUIRE(lexer.get_next_token() == Token {Token::Cbrt, 0, 11});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 15});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 8, 16});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 17});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 19});
	REQUIRE(lexer.get_next_token() == Token {Token::Root, 0, 21});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 25});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 256, 26});
	REQUIRE(lexer.get_next_token() == Token {Token::Comma, 0, 29});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 4, 30});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 31});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 32});
	REQUIRE(lexer.get_errors().empty());
}

TEST_CASE("Lexer generates correct tokens for log functions", "[lexer]") {
	auto lexer = Lexer("ln(2) + log(16,4)");
	REQUIRE(lexer.get_next_token() == Token {Token::Ln, 0, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 3});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 4});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 5});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 7});
	REQUIRE(lexer.get_next_token() == Token {Token::Log, 0, 9});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 12});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 16, 13});
	REQUIRE(lexer.get_next_token() == Token {Token::Comma, 0, 15});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 4, 16});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 17});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 18});
	REQUIRE(lexer.get_errors().empty());
}

TEST_CASE("Lexer reports and ignores errors", "[lexer]") {
	auto lexer = Lexer("foo(2) &+ #3");
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 4});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 2, 5});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 6});
	REQUIRE(lexer.get_next_token() == Token {Token::Plus, 0, 9});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 3, 12});
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 13});
	REQUIRE(lexer.get_errors() == "Unknown name 'foo' ignored at position 1\n"
			"Invalid character '&' ignored at position 8\n"
			"Invalid character '#' ignored at position 11\n");
}

TEST_CASE("Lexer returns correct token for deg function", "[lexer]") {
	auto lexer = Lexer("deg(10)");
	REQUIRE(lexer.get_next_token() == Token {Token::Deg, 0, 1});
	REQUIRE(lexer.get_next_token() == Token {Token::Lparen, 0, 4});
	REQUIRE(lexer.get_next_token() == Token {Token::Number, 10, 5});
	REQUIRE(lexer.get_next_token() == Token {Token::Rparen, 0, 7});
	REQUIRE(lexer.get_errors().empty());
}
