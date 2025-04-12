#pragma once

#include "../astNodes/Statement.h"
#include "../expressions/Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <memory>

namespace ast {

    class IfStmt : public Statement {
    public:
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Statement> thenBlock;
        std::shared_ptr<Statement> elseBlock; // Optional

        IfStmt(int line, int column, std::shared_ptr<Expression> condition,
               std::shared_ptr<Statement> thenBlock, std::shared_ptr<Statement> elseBlock = nullptr)
                : Statement(line, column), condition(std::move(condition)),
                  thenBlock(std::move(thenBlock)), elseBlock(std::move(elseBlock)) {}

        bool hasElse(){
            return elseBlock!= nullptr;
        }

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> parentTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            if (condition) {
                condition->BuildSymbolTable(errors, parentTable, currentFunction);

                std::shared_ptr<types::Type> conditionType = condition->GetType(errors, parentTable, currentFunction);

                if (!conditionType) {
                    errors.emplace_back(line, column, "If-condition type resolution failed.",
                                        context::CompilerPhase::SEMANTIC);
                }
                else if (!std::dynamic_pointer_cast<types::BoolTy>(conditionType)) {
                    errors.emplace_back(line, column,
                                        "Semantic error(" + std::to_string(line) + ":" + std::to_string(column) + "): "
                                                                                                                  "if conditional expression expects bool type but found '" + conditionType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                }
            }

            // Create new local scope for the then-block
            auto thenTable = std::make_shared<symboltable::SymbolTable<symboltable::VarEntry>>(parentTable);

            if (thenBlock) {
                thenBlock->BuildSymbolTable(errors, thenTable, currentFunction);
            }

            auto elseTable = std::make_shared<symboltable::SymbolTable<symboltable::VarEntry>>(parentTable);

            if (elseBlock) {
                elseBlock->BuildSymbolTable(errors, elseTable, currentFunction);
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

            // Create blocks for then and merge
            auto thenBlockCFG = std::make_shared<cfg::Block>("L" + std::to_string(program->getNextLabel()));
            current->addSuccessor(thenBlockCFG);
            thenBlockCFG->addPredecessor(current);
            std::shared_ptr<cfg::Block> elseBlockCFG = nullptr;
            if (hasElse()) {
                elseBlockCFG = std::make_shared<cfg::Block>("L" + std::to_string(program->getNextLabel()));
                current->addSuccessor(elseBlockCFG);
                elseBlockCFG->addPredecessor(current);
            }else{
                current->addSuccessor(merge);
                merge->addPredecessor(current);
            }

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
            if (hasElse()) {
                current->addInstruction(std::make_unique<llvm::Branch>(
                    condResult,  // Condition
                    thenBlockCFG->label,  // True branch label
                    elseBlockCFG->label   // False branch label
                ));
            } else {
                current->addInstruction(std::make_unique<llvm::Branch>(
                    condResult,  // Condition
                    thenBlockCFG->label,  // True branch label
                    merge->label  // False branch label
                ));
            }


            program->funcDefs[currentFunc->name].push_back(thenBlockCFG);
            if (hasElse()) {
                program->funcDefs[currentFunc->name].push_back(elseBlockCFG);
            }

            if (thenBlock) {
                thenBlock->TranslateToLLVMIR(thenBlockCFG, merge, exit, currentFunc, program, resultOperand);
            }

            if (elseBlock) {
                elseBlock->TranslateToLLVMIR(elseBlockCFG, merge, exit, currentFunc, program, resultOperand);
            }
        }

        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "if(";
            condition->print(out, tab);
            out<<"){\n";
            thenBlock->print(out, tab+1);
            for(int i = 0; i<tab;i++){
                out<<"    ";
            }
            out<<"}\n";
            if (elseBlock) {
                for(int i = 0; i<tab;i++){
                    out<<"    ";
                }
                out << "else{\n";
                elseBlock->print(out, tab+1);
                for(int i = 0; i<tab;i++){
                    out<<"    ";
                }
                out << "}\n";
            }

        }
    };

} // namespace ast
