#ifndef __PARSER_H__
#define __PARSER_H__

#include <memory>
#include <vector>

#include "lex.h"

class Parser
{
    using TT = TokenType;
private:
    const std::vector<Token> tokens;
    size_t i = 0;

    Token top();
    Token pop();


public:
    ProgramNode* parse();
    Parser(const std::string& file);
};

#endif //__PARSER_H__