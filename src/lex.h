#ifndef __LEXER_H__
#define __LEXER_H__

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#include "utils.h"

enum class TokenType
{
    INT, IDENTIFIER, RETURN, LBRACE, RBRACE, LPAREN, RPAREN, SEMICOLON, NUMBER, END
};

struct Token
{
    TokenType type;
    std::string value;
    
    Token(TokenType type, std::string value = "") : type(type), value(value) {}
};

std::vector<Token> lex(const std::string& file);


#endif //__LEXER_H__