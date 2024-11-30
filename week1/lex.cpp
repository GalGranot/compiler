#include <string>
#include <unordered_map>
#include <fstream>
#include <variant>

#include "utils.h"

typedef enum
{
    INT = 0,
    RETURN,
    MAIN,
    SEMICOLON,
    L_PARENTHESIS,
    R_PARENTHESIS,
    L_BRACKET,
    R_BRACKET,
    NUMBER_LITERAL,
} TokenType;

const TokenType TokenTypeVector[] = {
    INT,
    RETURN,
    MAIN,
    SEMICOLON,
    L_PARENTHESIS,
    R_PARENTHESIS,
    L_BRACKET,
    R_BRACKET,
    NUMBER_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL
};

using TokenValue = std::variant<void*, char, std::string, int>;
typedef std::pair<TokenType, TokenValue> Token;

struct TrieNode
{
    std::unordered_map<char, TrieNode*> children;
    bool isKeyword = false;
};

void clearTrie(TrieNode* node)
{
    for(auto& child : node->children) {
        clearTrie(child.second);
    }
    delete node;
}

class Lexer
{
private:
    TrieNode* root = new TrieNode();
    std::unordered_map<std::string, TokenType> string2Token;
    
    void addKeyword(const std::string& keyword)
    {
        TrieNode* node = root;
        for(char c : keyword) {
            if(node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isKeyword = true;
    }

    bool isKeyword(const std::string& token)
    {
        TrieNode* node = root;
        for(char c : token) {
            if(node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        if(node->isKeyword) {
            return true;
        }
        return false;
    }

    void processToken(const std::string& buffer, std::vector<Token>& tokens)
    {
        TokenValue value;
        TokenType type;
        if(isKeyword(buffer)) {
            
        } else {
        }
        tokens.push_back(t);
    }

    void initMap()
    {
        for(TokenType t : TokenTypeVector) {
            switch(t) {
            case INT:
                string2Token["int"] = t;
                break;
            case RETURN:
                string2Token["return"] = t;
                break;
            case MAIN:
                string2Token["main"] = t;
                break;
            case SEMICOLON:
                string2Token[";"] = t;
                break;
            case L_PARENTHESIS:
                string2Token[")"] = t;
                break;
            case R_PARENTHESIS:
                string2Token["("] = t;
                break;
            case L_BRACKET:
                string2Token["{"] = t;
                break;
            case R_BRACKET:
                string2Token["}"] = t;
                break;
            }
        }
    }

public:
    Lexer()
    {
        const std::vector<std::string> keywords = {
            "int",
            "return",
            "main",
            ";",
            "(",
            ")",
            "{",
            "}"
        };
        for(const std::string& keyword : keywords) {
            addKeyword(keyword);
        }
        initMap();
    }
    
    ~Lexer()
    {
        clearTrie(root);
    }

    std::vector<Token> lex(const std::string& fileName)
    {
        std::ifstream file(fileName);
        if(!file.is_open()) {
            errorAndExit("ifstream");
        }
        std::vector<Token> tokens;
        std::string buffer;
        char byte;

        while(file.get(byte)) {
            if(std::isspace(static_cast<unsigned char>(byte)) && !buffer.empty()) {
                processToken(buffer, tokens);
            } else {
                buffer += byte;
            }
        }
        processToken(buffer, tokens);
        return tokens;
    }
};
