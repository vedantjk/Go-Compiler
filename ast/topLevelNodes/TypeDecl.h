#pragma once

#include "TopLevelNode.h"
#include <string>
#include <vector>

namespace ast {

    struct Field {
        std::string name;
        std::string type;
        int line;
        int column;

        Field(std::string name, std::string type, int line, int column)
                : name(std::move(name)), type(std::move(type)), line(line), column(column) {}
    };

    class TypeDecl : public TopLevelNode {
    public:
        std::string name;
        std::vector<Field> fields;

        TypeDecl(int line, int column, std::string name, std::vector<Field> fields)
                : TopLevelNode(line, column), name(std::move(name)), fields(std::move(fields)) {}

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
            out << "type " << name << " struct {\n";
            for (size_t i = 0; i < fields.size(); ++i) {
                out << "    "<< fields[i].name << " " << fields[i].type<<";\n";
            }
            out << "}";
        }

        [[nodiscard]] std::string getName() const {
            return name;
        }
    };

} // namespace ast
