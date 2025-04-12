#pragma once

#include "../astNodes/ASTNode.h"

namespace ast {

// Abstract base class for top-level nodes (functions, type declarations, etc.)
    class TopLevelNode : public ASTNode {
    public:
        TopLevelNode(int line, int column) : ASTNode(line, column) {}
        virtual ~TopLevelNode() = default;
    };

} // namespace ast
