#include "parse.h"

Token Parser::top() { return i < tokens.size() ? tokens[i] : Token(TT::END); }
Token Parser::pop() { return i < tokens.size() ? tokens[i++] : Token(TT::END); }

struct StatementNode
{

};

struct ValueNode
{
    int value;
    ValueNode(int value) : value(value) {}
};

struct ReturnStatent : public StatementNode
{
    ValueNode* value;
    ReturnStatent(ValueNode* value) : value(value) {}
};

struct FunctionNode
{
    std::vector<StatementNode*> statements;
    FunctionNode(std::vector<StatementNode*> statements) : statements(statements) {}
};

struct ProgramNode
{
    std::vector<FunctionNode*> functions;
    ProgramNode(std::vector<FunctionNode*> functions) : functions(functions) {}
};

Parser::Parser(const std::string& file) : tokens(lex(file)) {}

ProgramNode* Parser::parse()
{
    return parse_function();
}