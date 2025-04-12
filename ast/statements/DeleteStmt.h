#pragma once

#include "../astNodes/Statement.h"
#include "../expressions/Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <memory>

namespace ast {

    class DeleteStmt : public Statement {
    public:
        std::shared_ptr<Expression> expr;

        DeleteStmt(int line, int column, std::shared_ptr<Expression> expr)
                : Statement(line, column), expr(std::move(expr)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                errors.emplace_back(line, column, "Symbol tables not initialized.", context::CompilerPhase::SEMANTIC);
                return;
            }

            // Ensure the delete statement has a valid expression
            if (!expr) {
                errors.emplace_back(line, column, "Delete statement is missing an expression.", context::CompilerPhase::SEMANTIC);
                return;
            }

            // Resolve the type of the expression being deleted
            expr->BuildSymbolTable(errors, localTable, currentFunction);
            auto exprType = expr->GetType(errors, localTable, currentFunction);

            if (!exprType) {
                errors.emplace_back(line, column, "Delete statement has an unresolved type.", context::CompilerPhase::SEMANTIC);
                return;
            }


            // Ensure the expression is a pointer type
            auto ptrType = std::dynamic_pointer_cast<types::PointerTy>(exprType);
            if (!ptrType) {
                errors.emplace_back(line, column,
                                    "Delete statement requires expression to be a struct pointer but found '" + exprType->toString() + "' type.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }

            // Ensure the base type of the pointer is a struct
            auto baseType = ptrType->getBaseType();
            auto structType = std::dynamic_pointer_cast<types::StructTy>(baseType);
            if (!structType) {
                errors.emplace_back(line, column,
                                    "Delete statement requires expression to be a struct pointer but found pointer to '" + baseType->toString() + "'.",
                                    context::CompilerPhase::SEMANTIC);
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


          // Ensure expression translates to an LLVM operand
            std::shared_ptr<llvm::LLVMOperand> exprOperand = nullptr;
            expr->TranslateToLLVMIR(current, merge, exit, currentFunc, program, exprOperand);

            if (!exprOperand) {
                std::cerr << "[ERROR] Failed to generate LLVM IR for delete expression.\n";
                return;
            }

            // Convert struct pointer to `i8*` for free function
            std::string castedPtr = "%r" + std::to_string(program->getNextRegister());

            current->addInstruction(std::make_unique<llvm::Free>(
                std::make_shared<llvm::LLVMRegister>(castedPtr, types::StringToType("i8*", symbolTables)),  // Bitcast destination
                exprOperand  // Source operand (struct pointer)
            ));

        }


        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "delete ";
            expr->print(out, tab);
        }
    };

} // namespace ast
