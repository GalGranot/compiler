#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <unistd.h>
#include <unordered_map>

#include "utils.h"

/*
tasks:
    1. add smart pointers
*/

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
        std::cout << "checking if token with " << token << std::endl;
        TrieNode* node = root;
        for(char c : token) {
            if(node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        if(node->isKeyword) {
            std::cout << token << " is token!" << std::endl;
            return true;
        }
        return false;
    }

    void processToken(std::string& token, std::vector<std::string>& tokens)
    {
        std::cout << "processing token " << token << std::endl;
        if(!isKeyword(token)) {
            //handle non keywords FIXME
            //return;
        }
        tokens.push_back(token);
        token.clear();
    }

public:
    std::vector<std::string> lex(const std::string& fileName)
    {
        std::ifstream file(fileName);
        if(!file.is_open()) {
            errorAndExit("ifstream");
        }
        std::vector<std::string> tokens;
        std::string currentToken;
        char byte;

        while(file.get(byte)) {
            std::cout << "byte = " << byte << ", current token = " << currentToken << std::endl;
            if(std::isspace(static_cast<unsigned char>(byte))) {
                if(currentToken.empty()) { //token buffer already tokenzied
                    continue;
                }
                processToken(currentToken, tokens);
                continue;
            }
            if(isKeyword(currentToken)) {
                processToken(currentToken, tokens);
            }
            currentToken += byte;
        }
        std::cout << "last token! " << currentToken << std::endl;
        processToken(currentToken, tokens);
        return tokens;
    }

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
    }

    ~Lexer()
    {
        clearTrie(root);
    }
};

int main()
{
    Lexer lexer;
    for(std::string s : lexer.lex("return2.c"))
        std::cout << s << std::endl;
}