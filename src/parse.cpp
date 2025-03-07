#include "parse.h"

bool is_type(Token t) { return t.type == TokenType::INT; }

Parser::Parser(const std::string& file) : tokens(lex(file)) {}
Token Parser::top() 
{
    return i < tokens.size() ? tokens[i] : TT::END;
}
Token Parser::pop()
{
    return i < tokens.size() ? tokens[i++] : TT::END;
}

void Parser::parse_expression(FunctionNode* func_node)
{
    if(pop().type != TT::RETURN) error_exit("expected return");
    ReturnStatement ret_statement(std::stoi(pop().value));
    if(pop().type != TT::SEMICOLON) error_exit("expected semicolon");

    func_node->statements.push_back(ret_statement);
}

void Parser::parse_function(ProgramNode* prog_node)
{
    /*
    * function template is <type> <name> (<args>) { <body> },
    * parse it according to these steps
    */
    Token type = pop();
    if(!is_type(type)) error_exit("expected type");
    Token func_name = pop();
    if(func_name.type != TT::IDENTIFIER) error_exit("expected identifier");

    FunctionNode* func_node = new FunctionNode(func_name.value, "int"); //fixme create mapping from token type to...
    if(pop().type != TT::LPAREN) error_exit("expected lparen");
    if(pop().type != TT::RPAREN) error_exit("expected rparen");

    Token lbrace = pop();
    if(lbrace.type != TT::LBRACE) error_exit("expected lbrace");
    while(top().type != TT::RBRACE) {
        parse_expression(func_node);
    }
    if(pop().type != TT::RBRACE) error_exit("expected rbrace");

    prog_node->functions.push_back(func_node);
}

ProgramNode* Parser::parse_program()
{
    ProgramNode* prog_node = new ProgramNode();
    while(top().type != TT::END) {
        parse_function(prog_node);
    }
    return prog_node;
}

ProgramNode* Parser::parse()
{
    return parse_program();
}

#include <iostream>

using StatementNode = std::variant<ReturnStatement>;
void print_statement(StatementNode rs)
{
    ReturnStatement ss = std::get<ReturnStatement>(rs);
    std::cout << "return " << ss.value;
}

void print_function(FunctionNode* fn)
{
    using StatementNode = std::variant<ReturnStatement>;
    std::cout << fn->type << " " << fn->name << "\n";
    for(StatementNode rs : fn->statements) {
        print_statement(rs);
    }
    std::cout << "\n";
}

void print_ast(ProgramNode* pn)
{
    for(FunctionNode* fn : pn->functions) {
        print_function(fn);
    }
}

#include <iostream>
void print_lexes(std::vector<Token> tokens)
{
    std::unordered_map<TokenType, std::string> enumstostring = {
        {TokenType::INT, "int"},
        {TokenType::RETURN, "return"},
        {TokenType::LBRACE, "{"},
        {TokenType::RBRACE, "}"},
        {TokenType::LPAREN, "("},
        {TokenType::RPAREN, ")"},
        {TokenType::SEMICOLON, ";"},
        {TokenType::IDENTIFIER, "identifier"},
        {TokenType::NUMBER, "number"}
    };
    
    for(auto& t : tokens) {
        std::cout << enumstostring.at(t.type) << " " << t.value << std::endl;
    }
    std::cout <<"=======lexes=======" << std::endl;
}

// int main()
// {

//     Parser parser("week1/return_2.c");
//     // print_lexes(parser.tokens);
//     print_ast(parser.parse());
//     return 0;
// }
