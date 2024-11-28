#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <unistd.h>
#include <unordered_map>

#include "utils.h"

struct TrieNode
{
    std::unordered_map<char, TrieNode*> children;
    bool isKeyword = false;
};

struct KeywordLexer
{
    TrieNode* root = new TrieNode();

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

    void clearTrie(TrieNode* node)
    {
        for(auto& child : node->children) {
            clearTrie(child.second);
        }
        delete node;
    }

    KeywordLexer()
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
    }
    ~KeywordLexer() { clearTrie(root); }

    bool isKeyword(const std::string& token)
    {
        TrieNode* node = root;
        for(char c : token) {
            if(node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isKeyword;
    }

    void processToken(std::string& token, std::vector<std::string>& tokens)
    {
        if(isKeyword(token)) {
            tokens.push_back(token);
        }
        std::cout << "found unknown token: " << token;
    }

    std::vector<std::string> lex(const std::string& fileName)
    {
        std::ifstream file(fileName);
        if(!file.is_open()) {
            errorAndExit("open");
        }
        
        std::vector<std::string> tokens;
        std::string currentToken;
        char byte;
        while(file.get(byte)) {
            if(std::isspace(static_cast<unsigned char>(byte))) {
                if(currentToken.empty()) {
                    continue;
                }
                processToken(currentToken, tokens);
                currentToken.clear();
            }
            currentToken += byte;            
        }
        return tokens;
    }
};

int main(int argc, char* argv[])
{
    KeywordLexer lexer;
    std::vector<std::string> tokens = lexer.lex(argv[1]);
    for(std::string& s : tokens) {
        std::cout << s << std::endl;
    }
}