#pragma once

#include "../expressions/Expression.h"

namespace ast {

    class BooleanLiteral : public Expression {
    public:
        bool value;

        BooleanLiteral(int line, int column, bool value)
                : Expression(line, column), value(value) {}
        void BuildSymbolTable(std::vector<context::CompilerError>& errors, std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable, std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
        }
        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                            std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                            std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override{
            return types::BoolTy::getInstance();
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override {
            // Directly create an LLVMOperand for the boolean literal
            resultOperand = std::make_shared<llvm::LLVMBooleanImmediate>(value);
        }



        void print(std::ostream& out, int tab) const override {
            out << (value ? "true" : "false");
        }
    };

} // namespace ast
