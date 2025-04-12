#pragma once

#include "../astNodes/ASTNode.h"
#include "../astNodes/Statement.h"
#include "../expressions/Expression.h"
#include "../expressions/VariableExpr.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "LLVM.h"
#include <memory>

namespace ast {

    class ScanStmt : public Statement {
    public:
        std::shared_ptr<Expression> variable;
        std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> _localTable;
        ScanStmt(int line, int column, std::shared_ptr<Expression> variable)
                : Statement(line, column), variable(std::move(variable)) {}

        void BuildSymbolTable(std::vector<context::CompilerError>& errors, std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable, std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {

            _localTable = localTable;
            //Ensure `variable` is a valid identifier
            auto varExpr = std::dynamic_pointer_cast<VariableExpr>(variable);
            if (!varExpr) {
                errors.emplace_back(line, column, "Scan statement must read into a variable.", context::CompilerPhase::SEMANTIC);
                return;
            }

            std::string varName = varExpr->getIdentifier();
            auto varEntry = localTable->lookup(varName);
            if (!varEntry) {
                auto tables = ASTNode::getSymbolTables();
                auto globalEntry = tables->getGlobals()->lookup(varName);
                if(!globalEntry) errors.emplace_back(line, column, "Scan statement refers to undeclared variable '" + varName + "'.", context::CompilerPhase::SEMANTIC);
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


            // Ensure that the variable being scanned is a valid identifier
            auto varExpr = std::dynamic_pointer_cast<VariableExpr>(variable);
            if (!varExpr) {
                return;
            }

            // Retrieve the variable name and check if it's local or global
            std::string varName = varExpr->getIdentifier();
            bool isGlobal = false;

            auto varEntry = _localTable->lookup(varName);

            if (!varEntry) {
                varEntry = ASTNode::getSymbolTables()->getGlobals()->lookup(varName);
                if (varEntry) {
                    isGlobal = true;
                } else {
                    return;
                }
            }

            program->sstatement();

            // Generate the scan instruction with the appropriate prefix (% for local, @ for global)
            if (isGlobal) {
                current->addInstruction(std::make_unique<llvm::Scan>(
                    "@" + varName
                ));
            } else {
                if(currentFunc->parametersLLVM.count(varName+"_addr"))
                    current->addInstruction(std::make_unique<llvm::Scan>(
                        "%" + varName + "_addr"
                    ));
                else
                    current->addInstruction(std::make_unique<llvm::Scan>(
                        "%" + varName
                    ));
            }

        }


        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "scan ";
            variable->print(out, tab);
            out << ";";
        }
    };

} // namespace ast
