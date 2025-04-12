#include <iostream>
#include <string>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "../cfg/CFG.h"
#include "../llvm/LLVM.h"
#include "../codegen/codegen.h"
using namespace antlr4;
using namespace lexer;
using namespace parser;

int main(int argc, const char **argv) {
    if (argc < 2 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " [-l] [-ast] [-llvm] [-target=STRING] <path_to_file>\n";
        return 1;
    }

    bool lexOnly = false;
    bool printAST = false;
    bool generateLLVM = false;
    bool generateStack = false;
    bool generateARM = false;
    std::string targetTriple = "x86_64-linux-gnu";  // Default target triple x86_64-linux-gnu
    std::string filePath;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-l") {
            lexOnly = true;
        } else if (arg == "-ast") {
            printAST = true;
        } else if (arg == "-llvm-ir=stack" || arg == "-llvm-ir=reg" || arg == "-S") {
            generateLLVM = true;
            generateStack = (arg == "-llvm-ir=stack");
            generateARM = (arg == "-S");
        } else if (arg.rfind("-target=", 0) == 0) {
            if (!generateLLVM) {
                std::cerr << "Error: `-target=STRING` must be used with `-llvm-ir=[stack|reg]` or `-S`.\n";
                return 1;
            }
            targetTriple = arg.substr(8);
        } else {
            filePath = arg;
        }
    }

    if (printAST && (lexOnly || generateLLVM)) {
        std::cerr << "Error: `-ast` cannot be used with `-l` or `-llvm`.\n";
        return 1;
    }

    if (filePath.empty()) {
        std::cerr << "Error: No input file provided.\n";
        return 1;
    }

    try {
        std::cout << "Attempting to read file: " << filePath << std::endl;

        auto lexer = lexer::LexerWrapper::NewLexer(filePath);

        if (lexOnly) {
            lexer->PrintTokens();
            return 0;
        }

        auto parser = parser::ParserWrapper::NewParser(std::move(lexer));

        if (printAST) {
            parser->PrintAST();
            return 0;
        }




        auto ast = parser->Parse();
        auto tables = ast->getSymbolTables();
        if (ast == nullptr) return 0;

        auto llvmProgram = std::make_shared<llvm::LLVMProgram>(filePath, tables);
        llvmProgram->SetTargetTriple(targetTriple);  // Set the target triple
        std::shared_ptr<llvm::LLVMOperand> resultOperand = nullptr;
        auto dummy1 = std::make_shared<cfg::Block>("dummy 1");
        auto dummy2 = std::make_shared<cfg::Block>("dummy 1");
        auto dummy3 = std::make_shared<cfg::Block>("dummy 1");

        ast->TranslateToLLVMIR(dummy1, dummy2, dummy3, nullptr, llvmProgram, resultOperand);

        std::string outputFile;

        if (generateStack) {
            outputFile = filePath.substr(0, filePath.find_last_of('.')) + "_stack.ll";

            std::ofstream outFile(outputFile);
            if (!outFile) {
                std::cerr << "Error: Could not open output file " << outputFile << std::endl;
                return 1;
            }
            outFile << llvmProgram->toString();
            outFile.close();

            std::cout << "LLVM IR successfully written to " << outputFile << std::endl;
            return 0; // Exit after writing the _stack.ll file
        }
        llvmProgram->toRegister();
        if (generateLLVM) {
            outputFile = filePath.substr(0, filePath.find_last_of('.')) + ".ll";
            std::ofstream out(outputFile);
            if (!out) {
                std::cerr << "Error: Could not open output file " << outputFile << std::endl;
                return 1;
            }
            out << llvmProgram->toStringReg();
            out.close();

            std::cout << "LLVM IR successfully written to " << outputFile << std::endl;
            return 0;
        }

        auto codegen = std::make_shared<codegen::OutOfSSA>(tables, llvmProgram->labelToBlockMap, llvmProgram->globalDeclarations, llvmProgram->returnValue);
        codegen->setLiveIntervals(llvmProgram->funcDefsReg);
        std::string arm = codegen->generateARM();
        outputFile = filePath.substr(0, filePath.find_last_of('.')) + ".s";
        std::ofstream outFile(outputFile);
        if (!outFile) {
            std::cerr << "Error: Could not open output file " << outputFile << std::endl;
            return 1;
        }
        outFile << arm;
        outFile.close();

        std::cout << "ARM code successfully written to " << outputFile << std::endl;
        return 0;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
