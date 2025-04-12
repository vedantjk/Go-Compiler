#pragma once

#include "../astNodes/Statement.h"
#include "../expressions/Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "LLVM.h"
#include <memory>

namespace ast {

    class ReturnStmt : public Statement {
    public:
        std::shared_ptr<Expression> returnValue; // Can be null for void returns

        ReturnStmt(int line, int column, std::shared_ptr<Expression> returnValue = nullptr)
                : Statement(line, column), returnValue(std::move(returnValue)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction) override {

            // Ensure that returnValue is valid (if present)
            if (returnValue) {
                returnValue->BuildSymbolTable(errors, localTable);
            }

            // Ensure function return type matches return statement
            if (!currentFunction) {
                errors.emplace_back(line, column, "Return statement found outside of a function.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }

            auto expectedReturnType = currentFunction->returnType;
            bool isVoidFunction = std::dynamic_pointer_cast<types::VoidTy>(expectedReturnType) != nullptr;

            if (isVoidFunction && returnValue) {
                errors.emplace_back(line, column, "Void function should not return a value.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }

            if (!isVoidFunction && !returnValue) {
                errors.emplace_back(line, column, "Function '" + currentFunction->name +
                                                  "' must return a value of type '" + expectedReturnType->toString() + "'.",
                                    context::CompilerPhase::SEMANTIC);

                return;
            }

            // Check if return type matches expected function return type
            if (returnValue) {
                std::shared_ptr<types::Type> actualReturnType = returnValue->GetType(errors, localTable, currentFunction);

                if (!actualReturnType) {
                    errors.emplace_back(line, column, "Return statement has an unresolved type.",
                                        context::CompilerPhase::SEMANTIC);
                    return;
                }

                if (actualReturnType != expectedReturnType) {
                    errors.emplace_back(line, column,
                                        "Return statement returns value of type \"" + actualReturnType->toString() +
                                        "\" but function returns type: \"" + expectedReturnType->toString() + "\"",
                                        context::CompilerPhase::SEMANTIC);
                }
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

            if (!currentFunc) {
                return;
            }


            // Get the function's expected return type
            std::string returnType = llvm::LLVMProgram::typeToLLVMType(currentFunc->returnType);
            bool isVoidFunction = (returnType == "void");

            // If returning a value, evaluate the expression
            if (returnValue) {
                if (isVoidFunction) {
                    return;
                }

                std::shared_ptr<llvm::LLVMOperand> returnOperand;
                returnValue->TranslateToLLVMIR(current, merge, exit, currentFunc, program, returnOperand);

                if (!returnOperand) {
                    return;
                }

                current->addInstruction(std::make_unique<llvm::Store>(
                    currentFunc->returnType,  // Type
                    returnOperand,  // Value to store
                    std::make_shared<llvm::LLVMRegister>("%_ret_val", currentFunc->returnType)  // Destination
                ));

            }

        }



        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "return ";
            if (returnValue) returnValue->print(out, tab);
            out<<";";
        }
    };

} // namespace ast
