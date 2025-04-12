#pragma once

#include "../astNodes/Statement.h"
#include "../expressions/VariableExpr.h"
#include "../expressions/Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "../expressions/FieldExpr.h"
#include "../expressions/NilExpr.h"
#include <memory>

namespace ast {

    class AssignStmt : public Statement {
    public:
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;
        std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> _localTable;
        AssignStmt(int line, int column, std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs)
                : Statement(line, column), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            _localTable = localTable;
            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                errors.emplace_back(line, column, "Symbol tables not initialized.", context::CompilerPhase::SEMANTIC);
                return;
            }

            std::shared_ptr<types::Type> lhsType = nullptr;

            if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(lhs)) {
                std::string lhsName = varExpr->getIdentifier();

                auto varEntry = localTable->lookup(lhsName);
                if (!varEntry) varEntry = tables->globals->lookup(lhsName);

                if (!varEntry) {
                    errors.emplace_back(line, column, "Assignment to undeclared variable '" + lhsName + "'.",
                                        context::CompilerPhase::SEMANTIC);
                }

                lhsType = varEntry->type;
            }
            else if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpr>(lhs)) {

                fieldExpr->BuildSymbolTable(errors, localTable, currentFunction);

                lhsType = fieldExpr->GetType(errors, localTable, currentFunction);
            }
            else {
                errors.emplace_back(line, column, "Left-hand side of assignment must be a variable or struct field.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }

            if (!lhsType) {
                errors.emplace_back(line, column, "Left-hand side type resolution failed.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }

            if (rhs) {
                rhs->BuildSymbolTable(errors, localTable, currentFunction);

                std::shared_ptr<types::Type> rhsType = rhs->GetType(errors, localTable, currentFunction);

                if (!rhsType) {
                    errors.emplace_back(line, column, "Right-hand side type resolution failed.",
                                        context::CompilerPhase::SEMANTIC);
                    return;
                }

                if (lhsType != rhsType) {
                    auto lhsPointer = std::dynamic_pointer_cast<types::PointerTy>(lhsType);
                    auto nilType = types::VoidTy::getInstance(); // Assuming `nil` is treated as `VoidTy`

                    if (!(rhsType == nilType && lhsPointer)) {
                        errors.emplace_back(line, column,
                                            "Semantic error(" + std::to_string(line) + ":" + std::to_string(column) + "): "
                                                                                                                      "left-hand side value of type '" + lhsType->toString() + "' does not match its expression of type '" + rhsType->toString() + "'.",
                                            context::CompilerPhase::SEMANTIC);
                    }
                }
            } else {
                errors.emplace_back(line, column, "Right-hand side of assignment is missing.",
                                    context::CompilerPhase::SEMANTIC);
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


            std::shared_ptr<llvm::LLVMOperand> lhsOperand;
            std::shared_ptr<llvm::LLVMOperand> rhsOperand;

            // Translate RHS (Expression)
            if (rhs) {
                rhs->TranslateToLLVMIR(current, merge, exit, currentFunc, program, rhsOperand);
            } else {
                return;
            }

            // Determine LHS Type
            if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(lhs)) {
                std::string varName = varExpr->getIdentifier();
                std::vector<context::CompilerError> errors;
                lhsOperand = std::make_shared<llvm::LLVMVariableOperand>(varName, varExpr->GetType(errors, _localTable, currentFunc));
            }
            else if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpr>(lhs)) {
                fieldExpr->TranslateToLLVMIR(current, merge, exit, currentFunc, program, lhsOperand, true);
            }
            else {
                return;
            }

            // Generate Store Instruction
            // Handle nil assignment specially
            if (auto nilExpr = std::dynamic_pointer_cast<NilExpr>(rhs)) {
                if (lhsOperand->isAddress()) {
                    auto addressOp = std::dynamic_pointer_cast<llvm::LLVMAddressOperand>(lhsOperand);
                    current->addInstruction(std::make_unique<llvm::Store>(
                        addressOp->getPointeeType(),
                        std::make_shared<llvm::LLVMNilOperand>(addressOp->getPointeeType()),  
                        std::make_shared<llvm::LLVMRegister>(lhsOperand->toString(), addressOp->getPointeeType())  // Destination: pointer
                    ));
                } else {
                    std::string varAddr = lhsOperand->toString();
                    if (currentFunc->parametersLLVM.count(varAddr + "_addr")) {
                        varAddr = "%" + varAddr + "_addr";
                    } else if (varAddr[0] != '%' && varAddr[0] != '@') {
                        bool isGlobal = !!ASTNode::getSymbolTables()->globals->lookup(varAddr);
                        varAddr = (isGlobal ? "@" : "%") + varAddr;
                    }

                    current->addInstruction(std::make_unique<llvm::Store>(
                        lhsOperand->getType(),
                        std::make_shared<llvm::LLVMNilOperand>(lhsOperand->getType()), 
                        std::make_shared<llvm::LLVMRegister>(varAddr, lhsOperand->getType())  // Destination: variable memory
                    ));
                }
            } else {
                // Handle normal assignment
                if (lhsOperand->isAddress()) {
                    auto addressOp = std::dynamic_pointer_cast<llvm::LLVMAddressOperand>(lhsOperand);
                    current->addInstruction(std::make_unique<llvm::Store>(
                        rhsOperand->getType(),
                        rhsOperand,  // Value to store
                        std::make_shared<llvm::LLVMRegister>(lhsOperand->toString(), addressOp->getPointeeType())  // Destination
                    ));
                } else {
                    std::string varAddr = lhsOperand->toString();
                    if (currentFunc->parametersLLVM.count(varAddr + "_addr")) {
                        varAddr = "%" + varAddr + "_addr";
                    } else if (varAddr[0] != '%' && varAddr[0] != '@') {
                        bool isGlobal = !(ASTNode::getSymbolTables()->globals->lookup(varAddr) == nullptr);
                        varAddr = (isGlobal ? "@" : "%") + varAddr;
                    }

                    current->addInstruction(std::make_unique<llvm::Store>(
                        rhsOperand->getType(),
                        rhsOperand,  // Value to store
                        std::make_shared<llvm::LLVMRegister>(varAddr, lhsOperand->getType())  // Destination
                    ));
                }
            }


        }


        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            lhs->print(out, tab);
            out << " = ";
            rhs->print(out, tab);
        }
    };

} // namespace ast