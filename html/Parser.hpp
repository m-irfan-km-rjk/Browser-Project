#pragma once

#include <string>
#include <unordered_map>
#include "Token.hpp"
#include <vector>

enum class DOMNodeType {
	HTML,
	HEAD,
	BODY,
	DIV,
	P,
	TITLE
};

struct DOMNode {
	DOMNodeType type;
	std::string text;
	std::unordered_map<std::string, std::string> attribs;
	DOMNode* children[];
};

class Parser {
public:
	Parser(std::vector<Token> tokens);

	void parse();

private:
	int pos;
	std::vector<Token> tokens;
	Token currentToken;
	DOMNode* root;

	void nextToken();
	Token peek();

};
