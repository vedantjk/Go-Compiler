#pragma once

#include "../expressions/Expression.h"

namespace ast {

    class IntegerLiteral : public Expression {
    public:
        int value;

        IntegerLiteral(int line, int column, int value)
                : Expression(line, column), value(value) {}
        void BuildSymbolTable(std::vector<context::CompilerError>& errors, std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable, std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
        }
        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                    std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                    std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override{
            return types::IntTy::getInstance();
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue) override {
            // Create an LLVMOperand for the integer literal
            resultOperand = std::make_shared<llvm::LLVMImmediate>(value, types::IntTy::getInstance());
        }



        void print(std::ostream& out, int tab) const override {
            out  << value ;
        }
    };

} // namespace ast
