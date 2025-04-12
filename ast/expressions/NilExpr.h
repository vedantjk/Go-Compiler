#pragma once

#include "Expression.h"
#include "../symboltable/symboltable.h"
#include <iostream>

namespace ast {

    class NilExpr : public Expression {
    public:
        NilExpr(int line, int column)
                : Expression(line, column) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors, std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable, std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
        }

         std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                    std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                    std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override{

            return types::VoidTy::getInstance();
        }

        void print(std::ostream& out, int tab) const override {
            out << "nil";
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override {
            resultOperand = std::make_shared<llvm::LLVMImmediate>(0, types::VoidTy::getInstance());
        }

    };

} // namespace ast
