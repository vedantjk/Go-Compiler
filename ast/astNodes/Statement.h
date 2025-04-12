#pragma once

#include "ASTNode.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <vector>
#include <memory>

namespace ast {

// Abstract base class for all statements
    class Statement : public ASTNode {
    public:
        Statement(int line, int column) : ASTNode(line, column) {}
        virtual ~Statement() = default;

        virtual void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                                      std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                      std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) = 0;
    };

} // namespace ast
