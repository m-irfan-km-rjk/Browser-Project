#pragma once
#include <string>

enum class TokenType {
	TAG_OPEN,
	TAG_CLOSE,
	TAG_SLASH,
	TAG_NAME,
	IDENTIFIER,
	EQUALS,
	TEXT_CONTENT,
	EOF_TOKEN,
	ATTRIBUTE_NAME,
	ATTRIBUTE_VALUE
};

struct Token {
	TokenType type;
	std::string value;
	int line;
	int col;
};