#include "Lexer.hpp"
#include "Token.hpp"
#include <vector>
#include <string>
#include <cctype>

Lexer::Lexer(const std::string& code): code(code), pos(0), currentChar('\0'), state(LexerState::LX_CONTENT) {
	if (!this->code.empty()) {
		currentChar = code[0];
	}
}

char Lexer::peek() {
	size_t nextPos = pos + 1;
	if (nextPos < code.size())
		return code[nextPos];
	else
		return '\0';
}

void Lexer::nextChar() {
	if (pos < code.size())
		currentChar = code[++pos];
	else
		currentChar = '\0';
}

void Lexer::changeState(LexerState s) {
	state = s;
}

std::vector<Token> Lexer::tokenize() {

	int eof = 0;

	while (currentChar != '\0') {
		switch (state) {
			case LexerState::LX_CONTENT:
				handleContent();
				break;
			case LexerState::LX_ATTRIBUTENAME:
				handleAttributeName();
				break;
			case LexerState::LX_ATTRIBUTEVALUE:
				handleAttributeValue();
				break;
			case LexerState::LX_TAG:
				handleTag();
				break;

		}
	}

	return tokens;
}

void Lexer::handleContent() {
	if (currentChar == '<') {
		tokens.push_back({TokenType::TAG_OPEN,"<",row,col});
		changeState(LexerState::LX_TAG);
		nextChar();
		return;
	}

	std::string text;

	while (currentChar != '<' && currentChar != '\0') {
		text += currentChar;
		nextChar();
	}

	tokens.push_back({TokenType::TEXT_CONTENT,text,row,col});
}

void Lexer::handleTag() {
	if (currentChar == '>') {
		tokens.push_back({ TokenType::TAG_CLOSE,">",row,col });
		changeState(LexerState::LX_CONTENT);
		nextChar();
		return;
	}

	if (currentChar == '/') {
		tokens.push_back({ TokenType::TAG_SLASH,"/",row,col });
		nextChar();
	}

	std::string value;

	while (currentChar != '>' && currentChar != '\0' && currentChar != ' ' && currentChar != '/') {
		value += currentChar;
		nextChar();
	}

	if(!value.empty())
		tokens.push_back({TokenType::TAG_NAME,value,row,col});

	while (currentChar == ' ') {
		nextChar();
	}

	if (currentChar == '>') {
		tokens.push_back({ TokenType::TAG_CLOSE, ">", row, col });
		changeState(LexerState::LX_CONTENT);
		nextChar();
		return;
	}

	changeState(LexerState::LX_ATTRIBUTENAME);
}

void Lexer::handleAttributeName() {
	while (currentChar == ' ') {
		nextChar();
	}

	std::string value;

	while (isalnum(currentChar) || currentChar == '-') {
		value += currentChar;
		nextChar();
	}

	if(!value.empty())
		tokens.push_back({TokenType::ATTRIBUTE_NAME,value,row,col});

	while (currentChar == ' ') {
		nextChar();
	}

	if (currentChar == '=') {
		tokens.push_back({ TokenType::EQUALS,"=",row,col});
		nextChar();
		changeState(LexerState::LX_ATTRIBUTEVALUE);
		return;
	}

	if (currentChar == '/' || currentChar == '>') {
		changeState(LexerState::LX_TAG);
		return;
	}
}

void Lexer::handleAttributeValue() {
	while (currentChar == ' ') {
		nextChar();
	}

	std::string value;

	if (currentChar == '"') {
		nextChar();
		while (currentChar != '"' && currentChar != '\0') {
			value += currentChar;
			nextChar();
		}

		if(currentChar == '"')
			nextChar();

		tokens.push_back({TokenType::ATTRIBUTE_VALUE,value,row,col});
	}

	changeState(LexerState::LX_ATTRIBUTENAME);
}