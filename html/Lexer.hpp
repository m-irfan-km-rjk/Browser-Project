#pragma once

#include "Token.hpp"
#include <vector>

enum class LexerState {
	LX_CONTENT,
	LX_ATTRIBUTENAME,
	LX_ATTRIBUTEVALUE,
	LX_TAG
};

class Lexer {
private:
	int pos;
	int row, col;
	LexerState state;
	std::string code;
	char currentChar;
	std::vector<Token> tokens;

	
	char peek();
	void nextChar();
	void changeState(LexerState s);

public:
	Lexer(const std::string& code);

	std::vector<Token> tokenize();
	void handleContent();
	void handleTag();
	void handleAttributeName();
	void handleAttributeValue();
};