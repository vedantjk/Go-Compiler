#pragma once

#include "../astNodes/Statement.h"
#include "../expressions/Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <memory>

namespace ast {

    class ForStmt : public Statement {
    public:
        std::shared_ptr<Expression> condition;  // Condition expression
        std::shared_ptr<Statement> body;        // Loop body

        ForStmt(int line, int column, std::shared_ptr<Expression> condition, std::shared_ptr<Statement> body)
                : Statement(line, column), condition(std::move(condition)), body(std::move(body)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> parentTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            if (condition) {
                condition->BuildSymbolTable(errors, parentTable, currentFunction);

                std::shared_ptr<types::Type> conditionType = condition->GetType(errors, parentTable, currentFunction);

                if (!conditionType) {
                    errors.emplace_back(line, column, "Loop condition type resolution failed.",
                                        context::CompilerPhase::SEMANTIC);
                }
                else if (!std::dynamic_pointer_cast<types::BoolTy>(conditionType)) {
                    errors.emplace_back(line, column,
                                        "Semantic error(" + std::to_string(line) + ":" + std::to_string(column) + "): "
                                                                                                                  "loop condition must be of type 'bool', found '" + conditionType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                }
            }

            auto localTable = std::make_shared<symboltable::SymbolTable<symboltable::VarEntry>>(parentTable);

            if (body) {
                body->BuildSymbolTable(errors, localTable, currentFunction);
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

            auto loopBodyBlock = std::make_shared<cfg::Block>("L" + std::to_string(program->getNextLabel()));
            current->addSuccessor(loopBodyBlock);
            loopBodyBlock->addPredecessor(current);
            current->addSuccessor(merge);
            merge->addPredecessor(current);
            std::shared_ptr<llvm::LLVMOperand> condResult;
            condition->TranslateToLLVMIR(current, merge, exit, currentFunc, program, condResult);

            if (condResult && condResult->toString().find("%r") == 0) {
                auto condType = condResult->getType();
                if (types::isBoolTy(condType) ||
                    std::dynamic_pointer_cast<types::BoolTy>(condType)) {
                        std::string boolReg = "%r" + std::to_string(program->getNextRegister());
                        auto destReg = std::make_shared<llvm::LLVMRegister>(boolReg, types::BoolTy::getInstance());

                        current->addInstruction(std::make_unique<llvm::Trunc>(
                        destReg,  // Destination register
                        condResult,  // Source operand
                        types::IntTy::getInstance(),  // Source type (i64)
                        types::BoolTy::getInstance()  // Target type (i1)
                        ));

                        condResult = destReg;
                }
            }

            current->addInstruction(std::make_unique<llvm::Branch>(
                condResult,  // Condition
                loopBodyBlock->label,  // True branch label (loop body)
                merge->label  // False branch label (exit block)
            ));

            program->funcDefs[currentFunc->name].push_back(loopBodyBlock);
            body->TranslateToLLVMIR(loopBodyBlock, current, exit, currentFunc, program, condResult);
        }

        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "for(";
            if (condition) {
                condition->print(out, tab);
            } else {
                out << "null";
            }
            out << "){";
            out<<"\n";
            if (body) {
                body->print(out, tab+1);
            } else {
                out << "null";
            }
            for(int i = 0; i<tab;i++){
                out<<"    ";
            }
            out<<"}";
        }
    };

} // namespace ast
