#pragma once
#include <string>

enum class CSSTokenType {
    IDENTIFIER,
    STRING,
    DOT,
    HASH,
    LBRACE,
    RBRACE,
    COLON,
    SEMICOLON,
    STRING,
    NUMBER,
    UNIT,
    COMMA,
    EOF_TOKEN
};

struct Token {
    CSSTokenType type;
    std::string value;
    int line;
    int col;
};