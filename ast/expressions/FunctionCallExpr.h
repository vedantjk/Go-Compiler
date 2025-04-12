#pragma once

#include "Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "LLVM.h"
#include <vector>
#include <string>
#include <memory>

namespace ast {

    class FunctionCallExpr : public Expression {
    public:
        std::string functionName;
        std::vector<std::shared_ptr<Expression>> arguments;

        FunctionCallExpr(int line, int column, std::string functionName, std::vector<std::shared_ptr<Expression>> arguments)
                : Expression(line, column), functionName(std::move(functionName)), arguments(std::move(arguments)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            for (const auto& arg : arguments) {
                arg->BuildSymbolTable(errors, localTable, currentFunction);
            }
        }

        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                             std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                             std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            auto tables = ASTNode::getSymbolTables();
            auto function = tables->functions->lookup(functionName);

            if (!function) {
                errors.emplace_back(line, column, "Function '" + functionName + "' not declared.",
                                    context::CompilerPhase::SEMANTIC);
                return nullptr;
            }

            return function->returnType;
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue) override {

            auto tables = ASTNode::getSymbolTables();
            auto function = tables->functions->lookup(functionName);

            if (!function) {
                return;
            }

            // Translate arguments and collect their LLVM IR representations
            std::vector<std::shared_ptr<llvm::LLVMOperand>> argOperands;
            // Replace string stream with vector of pairs (type, value)
            std::vector<std::pair<std::string, std::string>> argList;

            for (size_t i = 0; i < arguments.size(); ++i) {
                std::shared_ptr<llvm::LLVMOperand> argOperand = nullptr;
                arguments[i]->TranslateToLLVMIR(current, merge, exit, currentFunc, program, argOperand);

                if (!argOperand) {
                    return;
                }

                // Check if this is an address operand that needs to be loaded
                if (auto addressOp = std::dynamic_pointer_cast<llvm::LLVMAddressOperand>(argOperand)) {
                    std::string loadReg = "%r" + std::to_string(program->getNextRegister());

                    auto loadInstruction = std::make_unique<llvm::Load>(
                            addressOp->getType(),
                            addressOp->getType(),
                            std::make_shared<llvm::LLVMRegister>(loadReg, addressOp->getType()),
                            std::make_shared<llvm::LLVMRegister>(addressOp->toString(), addressOp->getType())
                    );

                    current->addInstruction(std::move(loadInstruction));

                    argOperand = std::make_shared<llvm::LLVMRegister>(loadReg, addressOp->getType());
                }

                // Store the type and value as a pair in the argList
                std::string typeName = llvm::LLVMProgram::typeToLLVMType(argOperand->getType());
                std::string valueStr = argOperand->toString();
                argList.push_back(std::make_pair(typeName, valueStr));

                argOperands.push_back(argOperand);
            }

            // Generate the call instruction
            std::string returnType = llvm::LLVMProgram::typeToLLVMType(function->returnType);

            // Case 1: If function returns a value, store it in a register
            if (returnType != "void") {
                std::string tempVar = "%r" + std::to_string(program->getNextRegister());
                // Create a Call instruction with the vector of pairs
                current->addInstruction(std::make_unique<llvm::Call>(
                        std::make_shared<llvm::LLVMRegister>(tempVar, function->returnType),
                        functionName,
                        function->returnType,
                        argList
                ));
                resultOperand = std::make_shared<llvm::LLVMRegister>(tempVar, function->returnType);
            }
                // Case 2: If function returns void, call without assignment
            else {
                current->addInstruction(std::make_unique<llvm::Call>(
                        functionName,
                        function->returnType,
                        argList
                ));
            }
        }



        void print(std::ostream& out, int tab) const override {
            out << functionName << "(";
            for (size_t i = 0; i < arguments.size(); ++i) {
                arguments[i]->print(out, tab);
                if (i < arguments.size() - 1) out << ", ";
            }
            out << ")";
        }
    };

} // namespace ast
