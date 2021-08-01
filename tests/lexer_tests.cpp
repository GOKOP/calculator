#include <catch2/catch.hpp>
#include "Lexer.hpp"

TEST_CASE("Lexer generates correct tokens for basic operations", "[lexer]") {
	auto lexer = Lexer("2+(1-3)*6^3");
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
	REQUIRE(lexer.get_next_token() == Token {Token::Eof, 0, 12});
	REQUIRE(lexer.get_errors().empty());
}
