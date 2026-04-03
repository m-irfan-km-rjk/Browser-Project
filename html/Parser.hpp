#pragma once

#include <string>
#include "Token.hpp"
#include <vector>
#include "DOM.hpp"

class Parser {
public:
	Parser(std::vector<Token> &tokens);

	Document parse();
	

private:
	int pos;
	std::vector<Token> tokens;
	Token currentToken;
	std::vector<DOMNode*> stack;
	DOMNode* currentNode;

	void nextToken();
	Token peek();
	bool hasNext();
	void push(DOMNode* t);
	DOMNode* pop();
	DOMNode* top();
	std::vector<std::string> parseClassList(std::string s);
};
