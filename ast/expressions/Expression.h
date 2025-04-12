#pragma once

#include "../astNodes/ASTNode.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "../types/types.h"
#include <memory>
#include <vector>

namespace ast {

// Abstract base class for all expressions
    class Expression : public ASTNode {
    public:
        Expression(int line, int column) : ASTNode(line, column) {}
        virtual ~Expression() = default;

        virtual void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                                      std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                      std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) = 0;

        virtual std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                             std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                             std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) = 0;
    };



} // namespace ast
