#pragma once

#include "../astNodes/Statement.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "LLVM.h"
#include "ReturnStmt.h"
#include "IfStmt.h"
#include "ForStmt.h"
#include <vector>
#include <memory>

namespace ast {

    class BlockStmt : public Statement {
    public:
        std::vector<std::shared_ptr<Statement>> statements;

        BlockStmt(int line, int column, std::vector<std::shared_ptr<Statement>> statements)
                : Statement(line, column), statements(std::move(statements)) {}
        bool HasValidReturnPath() {
            for (const auto &stmt : statements) {
                if (!stmt) continue;

                if (std::dynamic_pointer_cast<ReturnStmt>(stmt)) {
                    return true;
                }

                if (auto block = std::dynamic_pointer_cast<BlockStmt>(stmt)) {
                    if (block->HasValidReturnPath()) return true;
                }

                if (auto ifStmt = std::dynamic_pointer_cast<IfStmt>(stmt)) {
                    bool thenReturns = false, elseReturns = false;
                    if (auto thenBlock = std::dynamic_pointer_cast<BlockStmt>(ifStmt->thenBlock)) {
                        thenReturns = thenBlock->HasValidReturnPath();
                    } else {
                        thenReturns = false; // No valid return path if it's not a block
                    }

                    if (auto elseBlock = std::dynamic_pointer_cast<BlockStmt>(ifStmt->elseBlock)) {
                        elseReturns = elseBlock->HasValidReturnPath();
                    } else {
                        elseReturns = false;
                    }


                    if (ifStmt->elseBlock && thenReturns && elseReturns) {
                        return true;
                    }
                }
            }
            return false;
        }

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> parentTable, std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            if (!parentTable) {
                throw std::runtime_error("BlockStmt::BuildSymbolTable() received a nullptr parentTable");
            }

            // Create local scope
            auto localTable = std::make_shared<symboltable::SymbolTable<symboltable::VarEntry>>(parentTable);

            // Process each statement
            for (size_t i = 0; i < statements.size(); i++) {
                if (!statements[i]) {
                    continue;
                }

                try {
                    statements[i]->BuildSymbolTable(errors, localTable, currentFunction);
                } catch (const std::exception& e) {
                    std::cerr << "[ERROR] Exception caught while processing statement " << i << ": " << e.what() << "\n";
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



            for (size_t i = 0; i < statements.size(); ++i) {
                if (!statements[i]) {
                    continue;
                }

                // Special Handling for Control Flow Statements
                if (auto ifStmt = std::dynamic_pointer_cast<IfStmt>(statements[i])) {
                    auto conditionBlock = std::make_shared<cfg::Block>("L" + std::to_string(program->getNextLabel()));
                    auto mergeBlock = std::make_shared<cfg::Block>("L" + std::to_string(program->getNextLabel()));
                    current->addInstruction(std::make_unique<llvm::Branch>(conditionBlock->label));

                    current->addSuccessor(conditionBlock);
                    conditionBlock->addPredecessor(current);
                    program->funcDefs[currentFunc->name].push_back(conditionBlock);

                    ifStmt->TranslateToLLVMIR(conditionBlock, mergeBlock, exit, currentFunc, program, resultOperand);

                    current = mergeBlock;
                    program->funcDefs[currentFunc->name].push_back(mergeBlock);
                    continue;
                }

                else if (auto forStmt = std::dynamic_pointer_cast<ForStmt>(statements[i])) {
                    auto loopCondition = std::make_shared<cfg::Block>("L" + std::to_string(program->getNextLabel()));
                    auto loopExit = std::make_shared<cfg::Block>("L" + std::to_string(program->getNextLabel()));
                    current->addInstruction(std::make_unique<llvm::Branch>(loopCondition->label));

                    current->addSuccessor(loopCondition);
                    loopCondition->addPredecessor(current);

                    program->funcDefs[currentFunc->name].push_back(loopCondition);

                    forStmt->TranslateToLLVMIR(loopCondition, loopExit, exit, currentFunc, program, resultOperand);

                    current = loopExit;
                    program->funcDefs[currentFunc->name].push_back(loopExit);
                    continue;
                }

                else if (auto returnStmt = std::dynamic_pointer_cast<ReturnStmt>(statements[i])) {
                    returnStmt->TranslateToLLVMIR(current, merge, exit, currentFunc, program, resultOperand);
                    break;  // No more execution after return
                }
                else {
                    statements[i]->TranslateToLLVMIR(current, merge, exit, currentFunc, program, resultOperand);

                }
            }

            if(statements.size() > 0) {
                auto lastStatement = statements[statements.size()-1];
                auto returnStmt = std::dynamic_pointer_cast<ReturnStmt>(lastStatement);
                if(returnStmt) {
                    current->addInstruction(std::make_unique<llvm::Branch>(exit->label));

                    current->addSuccessor(exit);
                    exit->addPredecessor(current);
                } else {
                    current->addInstruction(std::make_unique<llvm::Branch>(merge->label));

                    current->addSuccessor(merge);
                    merge->addPredecessor(current);
                }
            } else {
                current->addInstruction(std::make_unique<llvm::Branch>(merge->label));

                current->addSuccessor(merge);
                merge->addPredecessor(current);
            }
        }




        void print(std::ostream& out, int tab) const override {

            for (const auto & statement : statements) {
                for(int j = 0; j<tab;j++){
                    out<<"  ";
                }
                statement->print(out, tab);
                std::cout << std::endl;
            }
        }
    };

} // namespace ast
