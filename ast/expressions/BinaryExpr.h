#pragma once

#include "Expression.h"
#include <memory>
#include <string>

namespace ast {

    class BinaryExpr : public Expression {
    public:
        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;
        std::string op;
        std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> _localTable;
        BinaryExpr(int line, int column, std::shared_ptr<Expression> left, std::string op, std::shared_ptr<Expression> right)
                : Expression(line, column), left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            _localTable = localTable;
            // Just call for left and right expression.
            // If the operand was illegal, it would have been caught by lexer.
            left->BuildSymbolTable(errors, localTable, currentFunction);
            right->BuildSymbolTable(errors, localTable, currentFunction);
        }

        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                             std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                             std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            auto leftType = left->GetType(errors, localTable, currentFunction);
            auto rightType = right->GetType(errors, localTable, currentFunction);

            if (!leftType || !rightType) {
                errors.emplace_back(line, column, "Invalid type in binary operation.", context::CompilerPhase::SEMANTIC);
                return nullptr;
            }

            // Handle logical operators: "&&" and "||"
            if (op == "&&" || op == "||") {
                if (!std::dynamic_pointer_cast<types::BoolTy>(leftType) || !std::dynamic_pointer_cast<types::BoolTy>(rightType)) {
                    errors.emplace_back(line, column, "Operator '" + op + "' requires boolean operands, found '" + leftType->toString() + "' and '" + rightType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    return nullptr;
                }
                return types::BoolTy::getInstance();
            }

            // Handle comparison operators: "<", ">", "<=", ">="
            if (op == "<" || op == ">" || op == "<=" || op == ">=") {
                if (!std::dynamic_pointer_cast<types::IntTy>(leftType) || !std::dynamic_pointer_cast<types::IntTy>(rightType)) {
                    errors.emplace_back(line, column, "Operator '" + op + "' requires numeric operands, found '" + leftType->toString() + "' and '" + rightType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    return nullptr;
                }
                return types::BoolTy::getInstance();
            }

            // Handle equality operators: "==" and "!="
            if (op == "==" || op == "!=") {
                auto leftPointer = std::dynamic_pointer_cast<types::PointerTy>(leftType);
                auto rightPointer = std::dynamic_pointer_cast<types::PointerTy>(rightType);
                auto nilType = types::VoidTy::getInstance();

                if ((leftType == nilType && rightPointer) || (rightType == nilType && leftPointer)) {
                    return types::BoolTy::getInstance();
                }

                if (leftType != rightType) {
                    errors.emplace_back(line, column, "Operator '" + op + "' requires both operands to be of the same type, found '" + leftType->toString() + "' and '" + rightType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    return nullptr;
                }
                return types::BoolTy::getInstance();
            }

            // Handle arithmetic operators: "+", "-", "*", "/"
            if (op == "+" || op == "-" || op == "*" || op == "/") {
                if (!std::dynamic_pointer_cast<types::IntTy>(leftType) || !std::dynamic_pointer_cast<types::IntTy>(rightType)) {
                    errors.emplace_back(line, column, "Operator '" + op + "' requires numeric operands, found '" + leftType->toString() + "' and '" + rightType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    return nullptr;
                }
                return types::IntTy::getInstance();
            }

            errors.emplace_back(line, column, "Unsupported binary operator '" + op + "' found.", context::CompilerPhase::SEMANTIC);
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

            std::shared_ptr<llvm::LLVMOperand> lhsOperand;
            std::shared_ptr<llvm::LLVMOperand> rhsOperand;

            // Translate LHS and RHS into LLVM IR
            left->TranslateToLLVMIR(current, merge, exit, currentFunc, program, lhsOperand);
            right->TranslateToLLVMIR(current, merge, exit, currentFunc, program, rhsOperand);

            if (!lhsOperand || !rhsOperand) {
                return;
            }

            std::string resultReg = "%r" + std::to_string(program->getNextRegister());
            auto lhsType = lhsOperand->getType();
            auto rhsType = rhsOperand->getType();

            // Handle pointer and nil comparison separately
            bool isNilComparison = types::isVoidType(lhsType) || types::isVoidType(rhsType);
            bool isPointerComparison = (types::isPointerType(lhsType) && types::isPointerType(rhsType));

            if ((isPointerComparison || isNilComparison) && (op == "==" || op == "!=")) {
                std::string ptrType = types::isPointerType(lhsType) ?
                                    llvm::LLVMProgram::typeToLLVMType(lhsType) :
                                    llvm::LLVMProgram::typeToLLVMType(rhsType);

                std::unique_ptr<llvm::BinOp> binOp;
                if (isNilComparison) {
                    if (op == "==") {
                        binOp = std::make_unique<llvm::BinOp>(
                            std::make_shared<llvm::LLVMRegister>(resultReg, lhsType),  
                            "icmp eq",
                            lhsType,
                            lhsOperand,
                            std::make_shared<llvm::LLVMVariableOperand>("null", lhsType)
                        );
                    } else if (op == "!=") {
                        binOp = std::make_unique<llvm::BinOp>(
                            std::make_shared<llvm::LLVMRegister>(resultReg, lhsType),  
                            "icmp ne",
                            lhsType,
                            lhsOperand,
                            std::make_shared<llvm::LLVMVariableOperand>("null", lhsType)
                        );
                    }
                } else {
                    if (op == "==") {
                        binOp = std::make_unique<llvm::BinOp>(
                            std::make_shared<llvm::LLVMRegister>(resultReg, lhsType),  
                            "icmp eq",
                            lhsType,
                            lhsOperand,
                            rhsOperand
                        );
                    } else if (op == "!=") {
                        binOp = std::make_unique<llvm::BinOp>(
                            std::make_shared<llvm::LLVMRegister>(resultReg, lhsType), 
                            "icmp ne",
                            lhsType,
                            lhsOperand,
                            rhsOperand
                        );
                    }
                }
                current->addInstruction(std::move(binOp));
            } else {
                std::string binOpType;
                if (op == "+") binOpType = "add";
                else if (op == "-") binOpType = "sub";
                else if (op == "*") binOpType = "mul";
                else if (op == "/") binOpType = "sdiv";
                else if (op == "&&") binOpType = "and";
                else if (op == "||") binOpType = "or";
                else if (op == "<") binOpType = "icmp slt";
                else if (op == ">") binOpType = "icmp sgt";
                else if (op == "<=") binOpType = "icmp sle";
                else if (op == ">=") binOpType = "icmp sge";
                else if (op == "==") binOpType = "icmp eq";
                else if (op == "!=") binOpType = "icmp ne";
                else return; // Invalid operation

                auto binOp = std::make_unique<llvm::BinOp>(
                    std::make_shared<llvm::LLVMRegister>(resultReg, lhsType),  
                    binOpType,
                    lhsType,
                    lhsOperand,
                    rhsOperand
                );

                current->addInstruction(std::move(binOp));
            }

            std::vector<context::CompilerError> errors;
            resultOperand = std::make_shared<llvm::LLVMVariableOperand>(resultReg, lhsType);
        }





        void print(std::ostream& out, int tab) const override {
            out << "(";
            left->print(out, tab);
            out << " " << op << " ";
            right->print(out, tab);
            out << ")";
        }
    };

} // namespace ast