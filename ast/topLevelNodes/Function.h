#pragma once

#include "TopLevelNode.h"
#include "VarDecl.h"
#include "../astNodes/Statement.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "../statements/BlockStmt.h"
#include <string>
#include <vector>
#include <memory>

namespace ast {

    class Function : public TopLevelNode {
    public:
        std::string name;
        std::vector<context::Parameter> parameters;
        std::string returnType;  // Empty string if void
        std::vector<std::shared_ptr<VarDecl>> varDecls;
        std::shared_ptr<Statement> body;
        Function(int line, int column, std::string name, std::vector<context::Parameter> parameters,
                 std::string returnType, std::vector<std::shared_ptr<VarDecl>> varDecls,
                 std::shared_ptr<Statement> body)
                : TopLevelNode(line, column), name(std::move(name)), parameters(std::move(parameters)),
                  returnType(std::move(returnType)), varDecls(std::move(varDecls)), body(std::move(body)) {}

        std::string getName() {
            return name;
        }

        std::string getReturnType() {
            return returnType;
        }

        auto getParameters() {
            return parameters;
        }

        void BuildSymbolTable(std::vector<context::CompilerError>& errors, std::shared_ptr<symboltable::SymbolTables> tables) {
            int functionLine = this->line;
            int functionColumn = this->column;

            // Lookup function in the global function table
            auto funcEntry = tables->functions->lookup(name);
            if (!funcEntry) {
                errors.emplace_back(functionLine, functionColumn,
                                    "Function '" + name + "' is not declared in the global scope.",
                                    context::CompilerPhase::SEMANTIC);
                return;
            }

            // Create a new local symbol table for the function
            funcEntry->localVariables = std::make_shared<symboltable::SymbolTable<symboltable::VarEntry>>(
                    nullptr);

            // Insert Parameters into Local Symbol Table
            for (const auto &param: parameters) {
                if (funcEntry->localVariables->contains(param.name)) {
                    errors.emplace_back(param.line, param.column,
                                        "Duplicate parameter name '" + param.name + "' in function '" + name + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    continue;
                }
                auto paramType = types::StringToType(param.type, tables);
                auto paramEntry = std::make_shared<symboltable::VarEntry>(
                        param.name, paramType, symboltable::VarScope::LOCAL,
                        std::make_pair(param.line, param.column)); // Store correct param position

                funcEntry->localVariables->insert(param.name, paramEntry);
                funcEntry->parametersLLVM.insert(param.name + "_addr");
            }

            // Insert Local Variables into Local Symbol Table
            for (const auto &varDecl: varDecls) {
                for (const auto &varName: varDecl->getNames()) {
                    auto existingEntry = funcEntry->localVariables->lookup(varName); // Check if variable exists
                    if (existingEntry) {
                        auto [prevLine, prevCol] = existingEntry->position;  // Get previous declaration position

                        errors.emplace_back(
                                varDecl->getLine(), varDecl->getColumn(),
                                "redeclaration of variable (" + varName + "). Other declaration at (" +
                                std::to_string(prevLine) + "," + std::to_string(prevCol) + ").",
                                context::CompilerPhase::SEMANTIC
                        );

                        continue;
                    }

                    auto varType = types::StringToType(varDecl->getType(), tables);

                    // If the variable is a struct instance, verify it's defined
                    if (std::dynamic_pointer_cast<types::StructTy>(varType)) {
                        if (!tables->types->lookup(varDecl->getType())) {
                            errors.emplace_back(varDecl->getLine(), varDecl->getColumn(),
                                                "Struct type '" + varDecl->getType() + "' is not defined.",
                                                context::CompilerPhase::SEMANTIC);
                            continue;
                        }
                    }

                    auto varEntry = std::make_shared<symboltable::VarEntry>(
                            varName, varType, symboltable::VarScope::LOCAL,
                            std::make_pair(varDecl->getLine(), varDecl->getColumn())  // Store position
                    );

                    funcEntry->localVariables->insert(varName, varEntry);
                }
            }

            // Recursively Build Symbol Table for the Function Body
            if (body) {
                body->BuildSymbolTable(errors, funcEntry->localVariables, funcEntry);
            }
            auto blockBody = std::dynamic_pointer_cast<BlockStmt>(body);
            if (!returnType.empty() && returnType != "void" && (!blockBody || !blockBody->HasValidReturnPath())) {
                errors.emplace_back(functionLine, functionColumn,
                                    "semantic error(" + std::to_string(functionLine) + ":0): " +
                                    "Not all possible control flow paths in \"" + name + "\" return.",
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

            if (!currentFunc) {
                return;
            }


            // Allocate space for local variables
            for (const auto& varDecl : varDecls) {
                for (const auto& varName : varDecl->getNames()) {
                    auto varType = types::StringToType(varDecl->type, symbolTables);
                    std::string varReg = "%" + varName;

                    // Replace raw alloca instruction with Alloc class
                    current->addInstruction(std::make_unique<llvm::Alloc>(
                        varType,
                        std::make_shared<llvm::LLVMRegister>(varReg, varType)
                    ));
                }
            }


            //  Process Function Body Statements
            if (body) {
                body->TranslateToLLVMIR(current, exit, exit, currentFunc, program, resultOperand);
            }
        }


        void print(std::ostream& out, int tab) const override {
            for(int i = 0; i<tab;i++){
                out<<"  ";
            }
            out << "func " << name << "(";
            for (size_t i = 0; i < parameters.size(); ++i) {
                out << parameters[i].name << ": " << parameters[i].type;
                if (i < parameters.size() - 1) out << ", ";
            }
            out << ")";
            if (!returnType.empty()) out << " " << returnType;
            out << " {\n";
            for (const auto& varDecl : varDecls) {
                varDecl->print(out, tab);
                out << ";\n";
            }
            if (body) {
                body->print(out, tab + 1);
            }
            out << "\n}";
        }
    };

} // namespace ast
