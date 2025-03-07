#include "parse.h"

struct AstNode
{
    virtual ~AstNode() = default;
};

struct StatementNode : public AstNode
{
    virtual ~StatementNode() = default;
};

struct ExpressionNode : public AstNode
{
    virtual ~ExpressionNode() = default;
};

struct FunctionNode : public AstNode
{
    std::string name;
    std::vector<std::unique_ptr<StatementNode>> body;
    FunctionNode(std::string name, std::vector<std::unique_ptr<StatementNode>> body)
        : name(std::move(name)), body(std::move(body)) {}
};

struct ReturnStatement : public StatementNode
{
    std::unique_ptr<ExpressionNode> expression;
    ReturnStatement(std::unique_ptr<ExpressionNode> expression) : expression(std::move(expression)) {}
};

struct IntNode : public ExpressionNode
{
    int value;
    IntNode(int value) : value(value) {}
};

struct ProgramNode : public AstNode
{
    std::vector<std::unique_ptr<FunctionNode>> functions;
    ProgramNode(std::vector<std::unique_ptr<FunctionNode>> functions) 
        : functions(std::move(functions)) {}
};


class Parser
{
    using TT = TokenType;
private:
    std::vector<Token> tokens;
    size_t i = 0;

    Token top()
    {
        return i < tokens.size() ? tokens[i] : Token(TT::END);
    }

    Token pop()
    {
        return i < tokens.size() ? tokens[i++] : Token(TT::END);
    }

    std::unique_ptr<ExpressionNode> parse_expression()
    {
        Token token = pop();
        if(token.type == TT::NUMBER) {
            return std::make_unique<IntNode>(std::stoi(token.value));
        }
        error_exit("expected int value");
    }

    std::unique_ptr<StatementNode> parse_statement()
    {
        if(top().type != TT::RETURN) {
            error_exit("currently only processing return statements");
        }
        pop();
        std::unique_ptr<ExpressionNode> expression = parse_expression();
        if(pop().type != TT::SEMICOLON) {
            error_exit("expected ;");
        }
        return std::make_unique<ReturnStatement>(std::move(expression));
    }

    std::unique_ptr<FunctionNode> parse_function()
    {
        if(pop().type != TT::INT) { //FIXME add more types
            error_exit("expected int as function ret type");
        }
        Token name = pop();
        if(name.type != TT::IDENTIFIER) {
            error_exit("name of function must be identifier");
        }
        if(pop().type != TT::LPAREN) {
            error_exit("expected ( for args");
        }
        if(pop().type != TT::RPAREN) {
            error_exit("expected ) for args");
        }
        if(pop().type != TT::LBRACE) {
            error_exit("expected { for start of func");
        }
        std::unique_ptr<StatementNode> body = parse_statement();
        std::vector<std::unique_ptr<StatementNode>> statements;
        statements.push_back(std::move(body));
        return std::make_unique<FunctionNode>(std::move(name.value), std::move(statements));
    }

public:
    Parser(const std::string& file) : tokens(lex(file)) {}
    
    auto parse()
    {
        return parse_function();
    }
};

auto create_ast(const std::string& file)
{
    Parser parser(file);
    return parser.parse();
}

int main()
{
    auto ast = create_ast("week1/return_2.c");
}