#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include "parse.h"
#include <fstream>

class CodeGenerator
{
private:
    Parser parser; //fixme maybe can remove?
    std::ofstream output;
    ProgramNode* ast;

public:
    CodeGenerator(const std::string& file);
    void gen();
};

#endif //__CODEGEN_H__