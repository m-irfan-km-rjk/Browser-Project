#pragma once
#include <string>
#include <vector>
#include "Token.hpp"

class Lexer {
private:
	int pos;
	int row;
	int col;
	char currentChar;
	std::string code;
	std::vector<Token> tokens;

	void nextChar();
	char peek();

public:
	Lexer(const std::string& code);

	std::vector<Token> tokenize();
	
};