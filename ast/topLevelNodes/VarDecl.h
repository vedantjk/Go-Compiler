#pragma once

#include "TopLevelNode.h"
#include <string>
#include <vector>

namespace ast {

    class VarDecl : public TopLevelNode {
    public:
        std::vector<std::string> names;  // Variable names
        std::string type;                // Type name (as string)

        VarDecl(int line, int column, std::vector<std::string> names, std::string type)
                : TopLevelNode(line, column), names(std::move(names)), type(std::move(type)) {}

        // Returns all variable names
        std::vector<std::string> getNames() const {
            return names;
        }

        // Returns the declared type as a string
        std::string getType() const {
            return type;
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override{}

        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "var ";
            for (size_t i = 0; i < names.size(); ++i) {
                out << names[i];
                if (i < names.size() - 1) out << ", ";
            }
            out << " " << type;
        }
    };

} // namespace ast
