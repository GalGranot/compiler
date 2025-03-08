#include "codegen.h"
#include <iostream>
CodeGenerator::CodeGenerator(const std::string& file) : parser(file)
{
    std::string suffix = ".c";
    std::string output_name = file.substr(0, file.length() - suffix.length()) + "mine_" + ".s";
    output = std::ofstream(output_name); 
    ast = parser.parse();
}

void CodeGenerator::gen()
{
    output << ".section .text\n";
    for(FunctionNode* fn : ast->functions) {
        output << ".globl " << "" << fn->name << "\n"
               << fn->name << ":\n";
        for(StatementNode sn : fn->statements) {
            ReturnStatement rs = std::get<ReturnStatement>(sn);
            output << "movl $" << rs.value << ", %eax\n"
                   << "ret\n";
        }
    }
}

// int main()
// {
//     CodeGenerator cg("week1/return_2.c");
//     cg.gen();
// }