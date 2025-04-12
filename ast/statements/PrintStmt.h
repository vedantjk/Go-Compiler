#pragma once

#include "../astNodes/Statement.h"
#include "../expressions/Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "LLVM.h"
#include <vector>
#include <memory>
#include <string>
#include <regex>

namespace ast {

    class PrintStmt : public Statement {
    public:
        std::string formatString;
        std::vector<std::shared_ptr<Expression>> arguments;

        PrintStmt(int line, int column, std::string formatString, std::vector<std::shared_ptr<Expression>> arguments)
                : Statement(line, column), formatString(std::move(formatString)), arguments(std::move(arguments)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable, std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            // Ensure all argument expressions are valid
            for (size_t i = 0; i < arguments.size(); ++i) {
                if (!arguments[i]) {
                    errors.emplace_back(line, column, "Printf contains a null argument at index " + std::to_string(i) + ".",
                                        context::CompilerPhase::SEMANTIC);
                    continue;
                }
                arguments[i]->BuildSymbolTable(errors, localTable);
            }


            int formatSpecCount = CountFormatSpecifiers(formatString);

            if (formatSpecCount != arguments.size()) {
                errors.emplace_back(line, column, "Printf format string expects " + std::to_string(formatSpecCount) +
                                                  " arguments but got " + std::to_string(arguments.size()) + ".",
                                    context::CompilerPhase::SEMANTIC);
            }

        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override {


            //Create a unique format string identifier
            static int formatCount = 0;
            std::string formatID = "@.fstr" + std::to_string(formatCount++);

            std::string processedFormat = formatString;

            // Replace %d with %ld
            size_t pos = 0;
            while ((pos = processedFormat.find("%d", pos)) != std::string::npos) {
                processedFormat.replace(pos, 2, "%ld");
                pos += 3;
            }

            // Convert newlines to LLVM representation
            std::string escapedFormat;
            for (size_t i = 0; i < processedFormat.length(); i++) {

                char c = processedFormat[i];
                if(c == '"') continue;
                if (c == '\\') {
                    if(i < processedFormat.length() - 1 && processedFormat[i+1] == 'n'){
                        escapedFormat += R"(\0A)";
                        i++;
                    }
                } else if (c == '\t') {
                    escapedFormat += R"(\09)";
                } else {
                    escapedFormat += c;
                }
            }

            // Calculate correct length
            int formatSize = 0;
            bool inEscapeSequence = false;
            int escapeCount = 0;
            for (size_t i = 0; i < escapedFormat.length(); i++) {
                if (escapedFormat[i] == '\\') {
                    inEscapeSequence = true;
                    escapeCount = 0;
                } else if (inEscapeSequence) {
                    escapeCount++;
                    if (escapeCount == 2) {  // End of escape sequence like \0A
                        formatSize++;
                        inEscapeSequence = false;
                    }
                } else {
                    formatSize++;
                }
            }
            formatSize++; // Add 1 for null terminator

            // Create the format string global declaration
            std::stringstream fmtSS;
            fmtSS << formatID << R"( = private unnamed_addr constant [)"
                  << formatSize << R"( x i8] c")" << escapedFormat << R"(\00", align 1)";

            program->addGlobalDeclaration(fmtSS.str());

            // Translate arguments into LLVM operands
            std::vector<std::shared_ptr<llvm::LLVMOperand>> argOperands;
            for (const auto& arg : arguments) {
                std::shared_ptr<llvm::LLVMOperand> argResult;
                arg->TranslateToLLVMIR(current, merge, exit, currentFunc, program, argResult);
                if (!argResult) {
                    return;
                }
                argOperands.push_back(argResult);
            }

            // Process address operands and create load instructions
            std::vector<std::shared_ptr<llvm::LLVMOperand>> printOperands;
            for (const auto& operand : argOperands) {
                if (operand->isAddress()) {
                    std::string loadReg = "%r" + std::to_string(program->getNextRegister());

                    auto addressOp = std::dynamic_pointer_cast<llvm::LLVMAddressOperand>(operand);
                    if (!addressOp) {
                        continue;
                    }

                    auto pointeeType = addressOp->getPointeeType();
                    std::string llvmType = llvm::LLVMProgram::typeToLLVMType(pointeeType);

                    auto loadInstruction = std::make_unique<llvm::Load>(
                            pointeeType,
                            pointeeType,
                            std::make_shared<llvm::LLVMRegister>(loadReg, pointeeType),
                            std::make_shared<llvm::LLVMRegister>(operand->toString(), pointeeType)
                    );

                    current->addInstruction(std::move(loadInstruction));

                    // Add the loaded register as an operand instead of the address
                    printOperands.push_back(std::make_shared<llvm::LLVMRegister>(loadReg, pointeeType));
                } else {
                    // Add non-address operands directly
                    printOperands.push_back(operand);
                }
            }

// Add the Print instruction to the block
            current->addInstruction(std::make_unique<llvm::Print>(formatID, formatSize, printOperands, formatString));
        }

        // Helper function to escape special characters in the format string
        static std::string EscapeString(const std::string& str) {
            std::string escaped;

            for (size_t i = 0; i < str.length(); i++) {
                char c = str[i];
                switch (c) {
                    case '\n':
                        escaped += "\\0A";  // LLVM newline
                        break;
                    case '\t':
                        escaped += "\\09";  // Tab
                        break;
                    case '\\':
                        escaped += "\\\\";  // Backslash
                        break;
                    case '\"':
                        escaped += "\\22";  // Double quote
                        break;
                    case '%':
                        // Check if this is a `%d` format specifier
                        if (i + 1 < str.length() && str[i + 1] == 'd') {
                            escaped += "%ld";  // Convert `%d` to `%ld` for 64-bit integers
                            i++;  // Skip the 'd' character
                        } else {
                            escaped += c;
                        }
                        break;
                    default:
                        escaped += c;
                }
            }

            return escaped;
        }


        // Function to count format specifiers in the format string
        static int CountFormatSpecifiers(const std::string& format) {
            std::regex formatRegex(R"(%(d))");
            return std::distance(std::sregex_iterator(format.begin(), format.end(), formatRegex),
                                 std::sregex_iterator());
        }

        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "printf(\"" << formatString << "\", [";
            for (size_t i = 0; i < arguments.size(); ++i) {
                arguments[i]->print(out, tab);
                if (i < arguments.size() - 1) out << ", ";
            }
            out << "]);";
        }
    };

} // namespace ast
