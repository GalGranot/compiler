#include "lex.h"

static const std::vector<std::string> global_tokens = {
    "{",
    "}",
    "(",
    ")",
    ";",
    "int",
    "return",
    //"main" #FIXME remove this?
};

bool is_global_token(const std::string& s) 
{
    for(const std::string& gtoken : global_tokens) {
        if(s == gtoken) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> tokenize_by_whitespace(const std::string filename)
{
    std::ifstream f(filename);
    if(!f) error_exit("ifstream");

    std::vector<std::string> words;
    std::string line;
    while(std::getline(f, line)) {
        std::istringstream stream(line);
        std::string word;
        while(stream >> word) {
            words.push_back(word);
        }
    }
    return words;
}

void lex_word(const std::string& word, std::vector<std::string>& tokens)
{
    if(is_in(global_tokens, word)) {
        tokens.push_back(word);
        return;
    }
    std::string token;
    
    for(size_t i = 0; i < word.length(); i++) {
        std::string charstr(1, word[i]);
        if(is_in(global_tokens, charstr)) {
            if(!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(charstr);
            continue;
        }
        token += word[i];
        if(is_in(global_tokens, token)) {
            tokens.push_back(token);
            token.clear();
        }
    }
    if(!token.empty()) {
        tokens.push_back(token);
    }
}

std::vector<Token> tokenize_lexes(const std::vector<std::string>& lexes)
{
    std::unordered_map<std::string, TokenType> keyword_map = {
        {"int",     TokenType::INT},
        {"return",  TokenType::RETURN},
        {"{",       TokenType::LBRACE},
        {"}",       TokenType::RBRACE},
        {"(",       TokenType::LPAREN},
        {")",       TokenType::RPAREN},
        {";",       TokenType::SEMICOLON},
    };
    
    std::vector<Token> tokens;
    for(const std::string& lex : lexes) {
        if(keyword_map.count(lex)) {
            tokens.emplace_back(keyword_map[lex]);
        }
        else if(std::isdigit(lex[0])) {
            tokens.emplace_back(TokenType::NUMBER, lex);
        }
        else {
            tokens.emplace_back(TokenType::IDENTIFIER, lex);
        }
    }
    return tokens;
}

std::vector<Token> lex(const std::string& filename)
{
    const std::vector<std::string> words = tokenize_by_whitespace(filename);
    std::vector<std::string> tokens;
    for(const std::string& word : words) {
        lex_word(word, tokens);
    }

    return tokenize_lexes(tokens);
}

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

#include <iostream>
void print_lexes(std::vector<Token> tokens)
{
    for(auto& t : tokens) {
        std::cout << enumstostring[t.type] << ": " << t.value << std::endl;
    }
}