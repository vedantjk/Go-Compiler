#pragma once

#include "Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <string>
#include <memory>

namespace ast {

    class NewExpr : public Expression {
    public:
        std::string typeName;

        NewExpr(int line, int column, std::string typeName)
                : Expression(line, column), typeName(std::move(typeName)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                errors.emplace_back(line, column, "Symbol tables not initialized.", context::CompilerPhase::SEMANTIC);
                return;
            }

        }
        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override {

            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                return;
            }

            // Lookup the struct type
            auto structType = tables->types->lookup(typeName);
            if (!structType) {
                return;
            }

            std::string structLLVMType = "%struct." + typeName;
            int structSize = program->getTypeSize(structLLVMType);  // Fetch size of struct

            // Generate unique register for malloc result
            std::string mallocReg = "%r" + std::to_string(program->getNextRegister());
            std::string bitcastReg = "%r" + std::to_string(program->getNextRegister());

            current->addInstruction(std::make_unique<llvm::Malloc>(
                std::make_shared<llvm::LLVMRegister>(mallocReg, types::StringToType("i8*", symbolTables)),  // Destination (i8*)
                std::make_shared<llvm::LLVMRegister>(bitcastReg, types::StringToType(structLLVMType + "*", symbolTables)),  // Bitcast destination
                structSize,  // Struct size
                types::StringToType(typeName, symbolTables)  // Struct type
            ));


            resultOperand = std::make_shared<llvm::LLVMRegister>(bitcastReg, types::PointerTy::getPointerType(structType));

        }

        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                             std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                             std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                errors.emplace_back(line, column, "Symbol table not initialized.", context::CompilerPhase::SEMANTIC);
                return nullptr;
            }

            auto structType = tables->types->lookup(typeName);
            if (!structType) {
                errors.emplace_back(line, column, "Type '" + typeName + "' is not defined.", context::CompilerPhase::SEMANTIC);
                return nullptr;
            }

            return types::PointerTy::getPointerType(structType);
        }

        void print(std::ostream& out, int tab) const override {
            out << "new " << typeName;
        }
    };

} // namespace ast
