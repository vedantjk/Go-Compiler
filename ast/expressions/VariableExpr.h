#pragma once

#include "Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <string>
#include <memory>

namespace ast {

    class VariableExpr : public Expression {
    public:
        std::string name;
        std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> _localTable;
        VariableExpr(int line, int column, std::string name)
                : Expression(line, column), name(std::move(name)) {}

        [[nodiscard]] std::string getIdentifier() const {
            return name;
        }

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            auto tables = ASTNode::getSymbolTables();
            _localTable = localTable;
            if (!tables) {
                errors.emplace_back(line, column, "Symbol table not initialized.", context::CompilerPhase::SEMANTIC);
                return;
            }

            if (localTable->lookup(name) || tables->globals->lookup(name)) {
                return;
            }

            errors.emplace_back(line, column, "Use of undeclared variable '" + name + "'.", context::CompilerPhase::SEMANTIC);
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override {

            bool isGlobal = false;
            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                return;
            }

            // Look up variable in local and global scope
            auto varEntry = currentFunc->localVariables->lookup(name);

            if (!varEntry) {

                isGlobal = true;
                varEntry = tables->globals->lookup(name);
            }
            if (!varEntry) {
                return;
            }

            std::shared_ptr<types::Type> varType = varEntry->type;
            std::string varTypeLLVM = llvm::LLVMProgram::typeToLLVMType(varType);

            // Properly format the variable address for LLVM IR
            std::string varAddr;
            if (isGlobal) {
                varAddr = "@" + name;
            } else {
                if (currentFunc->parametersLLVM.count(name + "_addr")) {
                    varAddr = "%" + name + "_addr";
                } else {
                    varAddr = "%" + name;
                }
            }

            if (isLvalue) {
                // If used as an lvalue (for assignment), return the address of the variable
                resultOperand = std::make_shared<llvm::LLVMAddressOperand>(varAddr, varType);
            } else {
                // If used as an rvalue (for reading), load the value
                std::string resultReg = "%r" + std::to_string(program->getNextRegister());

                auto loadInstruction = std::make_unique<llvm::Load>(
                    varType,
                    varType,
                    std::make_shared<llvm::LLVMRegister>(resultReg, varType),
                    std::make_shared<llvm::LLVMRegister>(varAddr, varType)
                );

                current->addInstruction(std::move(loadInstruction));

                resultOperand = std::make_shared<llvm::LLVMVariableOperand>(resultReg, varType);
            }
        }


        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                             std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                             std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                errors.emplace_back(line, column, "Symbol table not initialized.", context::CompilerPhase::SEMANTIC);
                return nullptr;
            }

            auto varEntry = localTable->lookup(name);
            if (!varEntry) {
                varEntry = tables->globals->lookup(name);
            }

            if (varEntry) {
                return varEntry->type;
            }

            errors.emplace_back(line, column, "Variable '" + name + "' is not declared.", context::CompilerPhase::SEMANTIC);
            return nullptr;
        }

        void print(std::ostream& out, int tab) const override {
            out << name;
        }
    };

} // namespace ast
