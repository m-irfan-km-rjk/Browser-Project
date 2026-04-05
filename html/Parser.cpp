#include "Parser.hpp"
#include "Token.hpp"
#include <vector>
#include <sstream>
#include "DOM.hpp"

Parser::Parser(std::vector<Token> &tokens): tokens(tokens),pos(0),currentToken(tokens[0]) {
}

void Parser::nextToken() {
    if (pos + 1 < tokens.size()) {
        pos++;
        currentToken = tokens[pos];
    }
}

Token Parser::peek() {
    if (pos < tokens.size()) {
        return tokens[pos+1];
    }
    return Token();
}

bool Parser::hasNext() {
    return (pos < tokens.size());
}

//stack operations
void Parser::push(DOMNode* t) {
    stack.push_back(t);
}

DOMNode* Parser::pop() {
    if (!stack.empty()) {
        DOMNode* t = stack.back();
        return t;
    }
    return nullptr;
}

std::vector<std::string> Parser::parseClassList(std::string s) {
    std::vector<std::string> result;
    std::istringstream iss(s);
    std::string token;

    while (iss >> token) {  // splits by whitespace automatically
        result.push_back(token);
    }

    return result;
}

DOMNode* Parser::top() {
    if (!stack.empty()) {
        return stack.back();
    }
    return nullptr;
}

Document Parser::parse() {
    Document result = Document();


    while (hasNext()) {
        switch (currentToken.type) {
            case TokenType::TAG_OPEN:
                nextToken();
                if (currentToken.type == TokenType::TAG_SLASH) {
                    nextToken();
                    if (currentNode->tag == currentToken.value) {
                        currentNode = currentNode->parent;
                        pop();
                    }
                    nextToken();
                    nextToken();
                }
                else {
                    DOMNode* newNode = new DOMNode(currentToken.value, currentNode);
                    currentNode->children.push_back(newNode);
                    push(newNode);
                    currentNode = newNode;
                    while (currentToken.type != TokenType::TAG_CLOSE) {
                        if (currentToken.type == TokenType::ATTRIBUTE_NAME) {
                            std::string aname = currentToken.value;

                            nextToken();

                            if (currentToken.type == TokenType::EQUALS) {
                                nextToken();

                                std::string value = currentToken.value;

                                if (aname == "class") {
                                    newNode->classList = parseClassList(value);
                                }

                                newNode->attribs[aname] = value;

                                nextToken();
                            }
                            else {
                                newNode->attribs[aname] = "";
                            }
                        }
                        else {
                            nextToken();
                        }
                    }

                }
        }
    }

    return result;
}