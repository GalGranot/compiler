#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector>
#include <variant>

#include "lex.h"
#include "utils.h"

struct ReturnStatement
{
    int value;
    ReturnStatement(int value) : value(value) {}
};

using StatementNode = std::variant<ReturnStatement>;
struct FunctionNode
{
    const std::string name;
    const std::string type;
    std::vector<StatementNode> statements;

    FunctionNode(const std::string& name, const std::string& type) 
        : name(name), type(type) {}
};

struct ProgramNode
{
    const std::string name;
    std::vector<FunctionNode*> functions;

    ProgramNode(const std::string& name = "") : name(name) {}
};

class Parser
{
    using TT = TokenType;
    using StatementNode = std::variant<ReturnStatement>;
public:
    std::vector<Token> tokens;
    size_t i = 0;
    
    Token top();
    Token pop();

    ProgramNode* parse_program();
    void parse_function(ProgramNode* prog_node);
    void parse_expression(FunctionNode* func_node);

public:
    Parser(const std::string& file);
    ProgramNode* parse();
};

#endif //__PARSER_H__