#pragma once

#include "../astNodes/Statement.h"
#include "../expressions/Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <vector>
#include <memory>
#include <string>

namespace ast {

    class InvocationStmt : public Statement {
    public:
        std::string functionName;
        std::vector<std::shared_ptr<Expression>> arguments;

        InvocationStmt(int line, int column, std::string functionName, std::vector<std::shared_ptr<Expression>> arguments)
                : Statement(line, column), functionName(std::move(functionName)), arguments(std::move(arguments)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {


            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                errors.emplace_back(line, column, "Symbol tables not initialized.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }

            auto funcEntry = tables->functions->lookup(functionName);
            if (!funcEntry) {
                errors.emplace_back(line, column, "Function '" + functionName + "' is not declared.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }


            if (arguments.size() != funcEntry->parameters.size()) {
                errors.emplace_back(line, column, "Function '" + functionName + "' expects " +
                                                  std::to_string(funcEntry->parameters.size()) + " arguments but got " +
                                                  std::to_string(arguments.size()) + ".",
                                    context::CompilerPhase::SEMANTIC);
            }

            for (const auto& arg : arguments) {
                if (!arg) {
                    continue;
                }
                arg->BuildSymbolTable(errors, localTable, currentFunction);  // Use local table & function context
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


            // Vector to hold argument operands
            std::vector<std::shared_ptr<llvm::LLVMOperand>> argOperands;

            // Translate each argument expression
            for (const auto& arg : arguments) {
                std::shared_ptr<llvm::LLVMOperand> argOperand;
                arg->TranslateToLLVMIR(current, merge, exit, currentFunc, program, argOperand);

                if (!argOperand) {
                    return;
                }

                argOperands.push_back(argOperand);
            }

            auto tables = ASTNode::getSymbolTables();
            auto funcEntry = tables->functions->lookup(functionName);

            if (!funcEntry) {
                return;
            }

            // Build argument list as vector of pairs for the Call constructor
            std::vector<std::pair<std::string, std::string>> argList;
            for (size_t i = 0; i < argOperands.size(); ++i) {
                std::string argTypeStr = llvm::LLVMProgram::typeToLLVMType(argOperands[i]->getType());
                std::string argValueStr = argOperands[i]->toString();
                argList.push_back(std::make_pair(argTypeStr, argValueStr));
            }

            // Handle function return value
            if (funcEntry->returnType && !types::isVoidType(funcEntry->returnType) && !isLvalue) {
                // Function returns a value - use the first constructor
                std::string resultReg = "%r" + std::to_string(program->getNextRegister());

                // Create a LLVMRegister for the destination
                auto destReg = std::make_shared<llvm::LLVMRegister>(resultReg, funcEntry->returnType);

                // Add the call instruction using the first constructor
                current->addInstruction(std::make_unique<llvm::Call>(
                        destReg,                  // destination register
                        functionName,             // function name
                        funcEntry->returnType,    // return type
                        argList                   // argument list as vector of pairs
                ));

                // Set the result operand
                resultOperand = std::make_shared<llvm::LLVMVariableOperand>(resultReg, funcEntry->returnType);
            } else {
                // Void function call - use the second constructor
                current->addInstruction(std::make_unique<llvm::Call>(
                        functionName,             // function name
                        funcEntry->returnType,    // return type (void)
                        argList                   // argument list as vector of pairs
                ));
            }
        }

        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out  << functionName << "(";
            for (size_t i = 0; i < arguments.size(); ++i) {
                arguments[i]->print(out, tab);
                if (i < arguments.size() - 1) out << ", ";
            }
            out << ");";
        }
    };

} // namespace ast
