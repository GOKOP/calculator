#include "Token.hpp"

bool operator==(const Token& lhs, const Token& rhs) {
	return lhs.type == rhs.type && lhs.value == rhs.value && lhs.pos == rhs.pos;
}
