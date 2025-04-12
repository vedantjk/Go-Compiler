#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../symboltable/symboltable.h"  // Ensure access to symbol tables
#include "../../cfg/CFG.h"
#include "../../llvm/LLVM.h"
namespace ast {

    class ASTNode {
    protected:
        int line;   // Line number in source file
        int column; // Column number in source file

        static std::shared_ptr<symboltable::SymbolTables> symbolTables;

    public:
        ASTNode(int line, int column) : line(line), column(column) {}
        virtual ~ASTNode() = default;

        virtual void print(std::ostream& out, int tab) const = 0;



        // Getters for error reporting
        int getLine() const { return line; }
        int getColumn() const { return column; }

        static void setSymbolTables(std::shared_ptr<symboltable::SymbolTables> tables) {
            symbolTables = std::move(tables);
        }

        static std::shared_ptr<symboltable::SymbolTables> getSymbolTables() {
            return symbolTables;
        }

        virtual void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) = 0;
    };

} // namespace ast
