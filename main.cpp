#include <iostream>
#include "html/Lexer.hpp"
#include "html/Token.hpp"

std::string tokenTypeToString(TokenType type) {
	switch (type) {
	case TokenType::TAG_OPEN: return "TAG_OPEN";
	case TokenType::TAG_CLOSE: return "TAG_CLOSE";
	case TokenType::TAG_NAME: return "TAG_NAME";
	case TokenType::TAG_SLASH: return "TAG_SLASH";
	case TokenType::ATTRIBUTE_NAME: return "ATTRIBUTE_NAME";
	case TokenType::ATTRIBUTE_VALUE: return "ATTRIBUTE_VALUE";
	case TokenType::EQUALS: return "EQUALS";
	case TokenType::TEXT_CONTENT: return "TEXT_CONTENT";
	default: return "UNKNOWN";
	}
}

int main() {

	std::string cd =
		"<div   class = \"box\"   id=\"a\">"
		"Hello <b>world</b>"
		"<img src=\"img.png\"/>"
		"</div>";
	Lexer lexer(cd);

	auto tokens = lexer.tokenize();

	for (const auto& token : tokens) {
		std::cout << tokenTypeToString(token.type) << " : " << token.value << std::endl;
	}

	return 0;
}