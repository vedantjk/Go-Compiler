#pragma once

#include "Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <memory>
#include <string>

namespace ast {

    class UnaryExpr : public Expression {
    public:
        std::string op;  // Unary operator (!, -, *)
        std::shared_ptr<Expression> operand;
        std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> _localTable;
        UnaryExpr(int line, int column, std::string op, std::shared_ptr<Expression> operand)
                : Expression(line, column), op(std::move(op)), operand(std::move(operand)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            _localTable = localTable;
            operand->BuildSymbolTable(errors, localTable, currentFunction);  // Ensure operand is valid
        }

        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                             std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                             std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            auto operandType = operand->GetType(errors, localTable, currentFunction);
            if (!operandType) {
                errors.emplace_back(line, column, "Operand type resolution failed for unary operator '" + op + "'.",
                                    context::CompilerPhase::SEMANTIC);
                return nullptr;
            }

            if (op == "!") {
                if (!std::dynamic_pointer_cast<types::BoolTy>(operandType)) {
                    errors.emplace_back(line, column, "Unary operator '!' requires a boolean operand, but found '" + operandType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    return nullptr;
                }
                return types::BoolTy::getInstance();
            }

            if (op == "-") {
                if (!std::dynamic_pointer_cast<types::IntTy>(operandType)) {
                    errors.emplace_back(line, column, "Unary operator '-' requires an integer operand, but found '" + operandType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    return nullptr;
                }
                return types::IntTy::getInstance();
            }

            if (op == "*") {
                auto pointerType = std::dynamic_pointer_cast<types::PointerTy>(operandType);
                if (!pointerType) {
                    errors.emplace_back(line, column, "Unary operator '*' requires a pointer operand, but found '" + operandType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    return nullptr;
                }

                return pointerType->getBaseType();
            }

            errors.emplace_back(line, column, "Unknown unary operator '" + op + "'.",
                                context::CompilerPhase::SEMANTIC);
            return nullptr;
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override {
            std::vector<context::CompilerError> errors;
            std::shared_ptr<llvm::LLVMOperand> operandResult;
            operand->TranslateToLLVMIR(current, merge, exit, currentFunc, program, operandResult);

            if (!operandResult) {
                return;
            }

            if (op == "!") {
                // Logical NOT: `1` becomes `0`, `0` becomes `1`
                std::string xorReg = "%r" + std::to_string(program->getNextRegister());
                auto destReg = std::make_shared<llvm::LLVMRegister>(xorReg, types::BoolTy::getInstance());

                current->addInstruction(std::make_unique<llvm::UnaryOp>(
                    destReg, "xor", types::BoolTy::getInstance(), operandResult
                ));

                resultOperand = destReg;
            } else if (op == "-") {
                // Negation: `-x`
                std::string reg = "%r" + std::to_string(program->getNextRegister());
                auto destReg = std::make_shared<llvm::LLVMRegister>(reg, types::IntTy::getInstance());

                current->addInstruction(std::make_unique<llvm::UnaryOp>(
                    destReg, "sub", types::IntTy::getInstance(),
                    std::make_shared<llvm::LLVMImmediate>(0, types::IntTy::getInstance())  // `0 - operand`
                ));

                resultOperand = destReg;
            }
            else if (op == "*") {
                auto ptrType = std::dynamic_pointer_cast<types::PointerTy>(operand->GetType(errors, _localTable, currentFunc));
                if (!ptrType) {
                    return;
                }

                std::string reg = "%r" + std::to_string(program->getNextRegister());

                auto loadInstruction = std::make_unique<llvm::Load>(
                    ptrType->getBaseType(),
                    ptrType,
                    std::make_shared<llvm::LLVMRegister>(reg, ptrType->getBaseType()),
                    std::make_shared<llvm::LLVMRegister>(operandResult->toString(), ptrType)
                );

                current->addInstruction(std::move(loadInstruction));
                resultOperand = std::make_shared<llvm::LLVMRegister>(reg, ptrType->getBaseType());
            }

        }


        void print(std::ostream& out, int tab) const override {
            out << "(" << op;
            operand->print(out, tab);
            out << ")";
        }
    };

} // namespace ast
