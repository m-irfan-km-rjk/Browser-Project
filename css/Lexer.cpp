#include "Lexer.hpp"
#include <string>
#include <iostream>

Lexer::Lexer(const std::string& code) : code(code),pos(0),currentChar(code[pos]),col(1),row(1) {
}

void Lexer::nextChar() {
	if (pos < code.size()) {
		pos++;
		col++;
		currentChar = code[pos];
	}
	else {
		currentChar = '\0';
	}
}

char Lexer::peek() {
	size_t nextPos = pos + 1;
	if (nextPos < code.size())
		return code[nextPos];
	else
		return '\0';
}

std::vector<Token> Lexer::tokenize() {
	while (currentChar != '\0') {
		if (isspace(currentChar)) {
			if (currentChar == '\n') {
				row++;
				col = 1;
			}
			nextChar();
		}
		else if (currentChar == '{') {
			tokens.push_back({CSSTokenType::LBRACE,"{",row,col});
			nextChar();
		}
		else if (currentChar == '}') {
			tokens.push_back({ CSSTokenType::RBRACE,"}",row,col });
			nextChar();
		}
		else if (currentChar == ':') {
			tokens.push_back({ CSSTokenType::COLON,":",row,col });
			nextChar();
		}
		else if (currentChar == ';') {
			tokens.push_back({ CSSTokenType::SEMICOLON,";",row,col });
			nextChar();
		}
		else if (currentChar == '#') {
			tokens.push_back({ CSSTokenType::HASH,"#",row,col });
			nextChar();
		}
		else if (currentChar == '.') {
			tokens.push_back({ CSSTokenType::DOT,".",row,col });
			nextChar();
		}
		else if (currentChar == ',') {
			tokens.push_back({ CSSTokenType::COMMA,",",row,col });
			nextChar();
		}
		else if (isdigit(currentChar) || (currentChar == '-' && isdigit(peek()))) {
			std::string text = "";

			if (currentChar == '-') {
				text += '-';
				nextChar();
			}

			bool hasDot = false;

			while (isdigit(currentChar) || (currentChar == '.' && !hasDot)) {
				if (currentChar == '.')
					hasDot = true;
				text += currentChar;
				nextChar();
			}

			tokens.push_back({ CSSTokenType::NUMBER,text,row,col });

			text = "";

			if (isalpha(currentChar)) {
				while (isalpha(currentChar)) {
					text += currentChar;
					nextChar();
				}

				tokens.push_back({ CSSTokenType::UNIT,text,row,col });
			}
			else if (currentChar == '%') {
				text = "%";
				nextChar();
				tokens.push_back({ CSSTokenType::UNIT,text,row,col });
			}
		}
		else if (isalpha(currentChar)) {
			std::string text = "";
			while (isalnum(currentChar) || currentChar == '_' || currentChar == '-') {
				text += currentChar;
				nextChar();
			}

			tokens.push_back({ CSSTokenType::IDENTIFIER,text,row,col });
		}
		else if (currentChar == '"') {
			nextChar();

			std::string text;

			while (currentChar != '"' && currentChar != '\0') {
				text += currentChar;
				nextChar();
			}

			nextChar();

			tokens.push_back({ CSSTokenType::STRING,text,row,col });
		}
		else {
			std::cout << "Error at" << row << ":" << col;
			nextChar();
		}
	}

	tokens.push_back({ CSSTokenType::EOF_TOKEN,"EOF",row,col });
	return tokens;
}