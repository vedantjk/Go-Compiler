#pragma once

#include "../topLevelNodes/TypeDecl.h"
#include "../topLevelNodes/VarDecl.h"
#include "../topLevelNodes/Function.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include "../llvm/LLVM.h"
#include "types.h"
#include <vector>
#include <memory>

namespace ast {

    class Program : public ASTNode {
    public:
        std::vector<std::shared_ptr<TypeDecl>> typeDecls;
        std::vector<std::shared_ptr<VarDecl>> varDecls;
        std::vector<std::shared_ptr<Function>> functions;

        Program(int line, int column,
                std::vector<std::shared_ptr<TypeDecl>> typeDecls,
                std::vector<std::shared_ptr<VarDecl>> varDecls,
                std::vector<std::shared_ptr<Function>> functions)
                : ASTNode(line, column),
                  typeDecls(std::move(typeDecls)),
                  varDecls(std::move(varDecls)),
                  functions(std::move(functions)) {}

        void print(std::ostream& out, int tab) const override {
            for (const auto& typeDecl : typeDecls) {
                typeDecl->print(out, tab);
                out << ";\n";
            }
            for (const auto& varDecl : varDecls) {
                varDecl->print(out, tab);
                out << ";\n";
            }
            for (const auto& function : functions) {
                function->print(out, tab);
                out << "\n";
            }
        }

        void BuildSymbolTable(std::vector<context::CompilerError>& errors, std::shared_ptr<symboltable::SymbolTables> tables) {
            ASTNode::setSymbolTables(tables);

            // Insert struct types
            for (const auto& typeDecl : typeDecls) {

                if (tables->types->contains(typeDecl->getName())) {
                    errors.emplace_back(
                            typeDecl->getLine(), typeDecl->getColumn(),
                            "Type '" + typeDecl->getName() + "' is already declared.",
                            context::CompilerPhase::SEMANTIC);
                    continue;
                }

                // Insert empty struct types
                auto structType = types::StructTy::createStructType(typeDecl->getName());
                tables->types->insert(typeDecl->getName(), structType);
            }

            // Populate the struct types.
            // This is done this way so that in case a struct has a pointer to itself, it doesn't
            // error out
            for (const auto& typeDecl : typeDecls) {
                auto structType = std::dynamic_pointer_cast<types::StructTy>(tables->types->lookup(typeDecl->getName()));
                if (!structType) {
                    continue;
                }

                std::unordered_map<std::string, std::pair<int, int>> seenFields;
                std::unordered_map<std::string, std::shared_ptr<types::Type>> fieldMap;

                for (const auto& field : typeDecl->fields) {
                    if (seenFields.find(field.name) != seenFields.end()) {
                        auto [prevLine, prevCol] = seenFields[field.name];
                        errors.emplace_back(
                                field.line, field.column,
                                "Redeclaration of variable '" + field.name +
                                "'. Other declaration at (" + std::to_string(prevLine) + ":" + std::to_string(prevCol) + ").",
                                context::CompilerPhase::SEMANTIC);

                        continue;
                    }

                    seenFields[field.name] = {field.line, field.column};

                    try {
                        auto fieldType = types::StringToType(field.type, tables);

                        // If it's a pointer type, check that the base type exists
                        if (auto ptrType = std::dynamic_pointer_cast<types::PointerTy>(fieldType)) {
                            auto baseType = ptrType->getBaseType();
                            if (!baseType || (!std::dynamic_pointer_cast<types::StructTy>(baseType) && baseType->toString() != field.type)) {
                                errors.emplace_back(
                                        field.line, field.column,
                                        "Field '" + field.name + "' is a pointer to an undefined struct '" + field.type + "'.",
                                        context::CompilerPhase::SEMANTIC
                                );
                                continue;
                            }
                        }

                        fieldMap[field.name] = fieldType;
                    } catch (const std::runtime_error& e) {
                        errors.emplace_back(
                                field.line, field.column,
                                "Invalid field type '" + field.type + "' in struct '" + typeDecl->getName() + "'.",
                                context::CompilerPhase::SEMANTIC
                        );
                        continue;
                    }
                }

                structType->finalizeFields(fieldMap);
            }

            // Push in global variables
            for (const auto& varDecl : varDecls) {
                for (const auto& varName : varDecl->getNames()) {
                    auto prev = tables->globals->lookup(varName);
                    if (prev) {
                        errors.emplace_back(
                                varDecl->getLine(), varDecl->getColumn(),
                                "Global variable '" + varName + "' is already declared at (" +
                                std::to_string(prev->position.first) + "," +
                                std::to_string(prev->position.second) + ").",
                                context::CompilerPhase::SEMANTIC
                        );
                        continue;
                    }

                    auto entry = std::make_shared<symboltable::VarEntry>(
                            varName, types::StringToType(varDecl->getType(), tables), symboltable::VarScope::GLOBAL, std::make_pair(line, column));
                    tables->globals->insert(varName, entry);
                }
            }

            // Push in function declarations
            for (const auto& function : functions) {
                auto prev = tables->functions->lookup(function->getName());
                if (prev) {
                    errors.emplace_back(
                            function->getLine(), function->getColumn(),
                            "function with name \"" + function->getName() + "\" already defined. Previous declaration at " +
                            std::to_string(prev->position.first) + ":" + std::to_string(prev->position.second),
                            context::CompilerPhase::SEMANTIC
                    );

                    continue;
                }

                std::string returnTypeStr = function->getReturnType();
                if (function->getName() == "main") {
                    if (!returnTypeStr.empty()) {
                        errors.emplace_back(line, column, "Function 'main' should not have a return type.", context::CompilerPhase::SEMANTIC);
                        return;
                    }
                    if (!function->getParameters().empty()) {
                        errors.emplace_back(
                                function->getLine(), function->getColumn(),
                                "Function 'main' should not have any parameters.",
                                context::CompilerPhase::SEMANTIC
                        );
                        return;
                    }
                    returnTypeStr = "void";
                }
                if(returnTypeStr.empty()){
                    returnTypeStr = "void";
                }
                auto returnType = types::StringToType(returnTypeStr, tables);  // Convert string to Type
                std::vector<std::shared_ptr<symboltable::VarEntry>> paramEntries;
                for (const auto& param : function->getParameters()) {
                    auto paramType = types::StringToType(param.type, tables);  // Convert parameter type from string

                    // Ensure struct type is correctly resolved
                    if (!paramType) {
                        errors.emplace_back(
                                function->getLine(), function->getColumn(),
                                "Parameter '" + param.name + "' has unknown type '" + param.type + "'.",
                                context::CompilerPhase::SEMANTIC
                        );
                        continue;
                    }

                    // If it's a pointer type, check base type
                    if (auto ptrType = std::dynamic_pointer_cast<types::PointerTy>(paramType)) {
                        auto baseType = ptrType->getBaseType();
                        if (!baseType) {
                            errors.emplace_back(
                                    function->getLine(), function->getColumn(),
                                    "Pointer parameter '" + param.name + "' does not have a valid base type.",
                                    context::CompilerPhase::SEMANTIC
                            );
                            continue;
                        }
                    }
                    auto paramEntry = std::make_shared<symboltable::VarEntry>(
                            param.name, paramType, symboltable::VarScope::LOCAL, std::make_pair(line, column));
                    paramEntries.push_back(paramEntry);
                }

                auto funcEntry = std::make_shared<symboltable::FuncEntry>(
                        function->getName(), returnType, paramEntries, std::make_pair(function->getLine(), function->getColumn()));
                tables->functions->insert(function->getName(), funcEntry);
            }

            // Call build symboltables for functions
            for (const auto& function : functions) {
                function->BuildSymbolTable(errors, tables);
            }
            if(!tables->functions->contains("main")){
                errors.emplace_back(0,0,"No required function named \"main\" defined.", context::CompilerPhase::SEMANTIC);
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

            // Handle struct type declarations
            for (const auto& typeEntry : program->getTables()->getTypes()->getTable()) {
                auto structType = std::dynamic_pointer_cast<types::StructTy>(typeEntry.second);
                if (!structType) continue;

                std::stringstream ss;
                ss << "%struct." << structType->getName() << " = type {";
                bool first = true;

                for (const auto& [fieldName, fieldType] : structType->getFields()) {
                    if (!first) ss << ", ";
                    ss << llvm::LLVMProgram::typeToLLVMType(fieldType);
                    first = false;
                }

                ss << "}";

                program->addGlobalDeclaration(ss.str());
            }

            // Handle variable declarations
            for (const auto& varEntry : program->getTables()->getGlobals()->getTable()) {
                std::stringstream ss;
                auto varType = llvm::LLVMProgram::typeToLLVMType(varEntry.second->type);

                // Make sure its null for struct or pointer types and 0 for i64
                std::string initializer = "0";
                if(types::isPointerType(varEntry.second->type) || types::isStructType(varEntry.second->type)) initializer = "null";

                ss << "@" << varEntry.first << " = common global " << varType << " " << initializer;

                program->addGlobalDeclaration(ss.str());
            }

            // Handle function definitions
            for (const auto& func : functions) {
                std::string funcName = func->getName();
                std::string returnType = llvm::LLVMProgram::typeToLLVMType(types::StringToType(func->returnType, symbolTables));

                // If the function is "main", force return type to i64
                if (func->getName() == "main") {
                    returnType = "i64";
                }
                program->returnValue[funcName] = returnType;
                std::string entryLabel = "L" + std::to_string(program->getNextLabel());
                auto entryBlock = std::make_shared<cfg::Block>(entryLabel);


                // Force main to be i64
                if (func->getName() == "main") {
                    entryBlock->addInstruction(std::make_unique<llvm::Alloc>(
                        types::IntTy::getInstance(), // Destination Type
                        std::make_shared<llvm::LLVMRegister>("%_ret_val", types::StringToType("int", symbolTables))
                    ));
                } else if (returnType != "void") {
                    entryBlock->addInstruction(std::make_unique<llvm::Alloc>(
                        types::StringToType(func->returnType, symbolTables),
                        std::make_shared<llvm::LLVMRegister>("%_ret_val", types::StringToType(func->returnType, symbolTables))
                    ));
                }

                // Allocate function parameters with _addr suffix to avoid conflicts
                for (const auto& param : func->getParameters()) {
                    std::shared_ptr<types::Type> paramLLVMType = types::StringToType(param.type, symbolTables);
                    std::string paramAddr = "%" + param.name + "_addr";

                    entryBlock->addInstruction(std::make_unique<llvm::Alloc>(
                        paramLLVMType,
                        std::make_shared<llvm::LLVMRegister>(paramAddr, paramLLVMType)
                    ));

                    entryBlock->addInstruction(std::make_unique<llvm::Store>(
                        paramLLVMType,
                        std::make_shared<llvm::LLVMRegister>("%" + param.name, paramLLVMType),  // Value to store
                        std::make_shared<llvm::LLVMRegister>(paramAddr, paramLLVMType)  // Destination (allocated memory)
                    ));
                }



                std::string exitLabel = "L" + std::to_string(program->getNextLabel());
                auto exitBlock = std::make_shared<cfg::Block>(exitLabel);

                if (returnType != "void") {
                    if (func->getName() == "main") {
                        exitBlock->addInstruction(std::make_unique<llvm::Store>(
                            types::IntTy::getInstance(),
                            std::make_shared<llvm::LLVMImmediate>(0, types::IntTy::getInstance()),  // Value to store
                            std::make_shared<llvm::LLVMRegister>("%_ret_val", types::IntTy::getInstance())  // Destination (allocated memory)
                        ));
                    }

                    std::string returnRegister ="%r" + std::to_string(program->getNextRegister());

                    if(func->getName() == "main"){
                    exitBlock->addInstruction(std::make_unique<llvm::Load>(
                        types::IntTy::getInstance(),                                // Destination Type
                        types::IntTy::getInstance(), // Pointer Type
                        std::make_shared<llvm::LLVMRegister>(returnRegister, types::IntTy::getInstance()),  // Destination Register
                        std::make_shared<llvm::LLVMRegister>("%_ret_val", types::IntTy::getInstance()) // Source Operand (Pointer)
                    ));}else{
                        exitBlock->addInstruction(std::make_unique<llvm::Load>(
                        types::StringToType(func->returnType, symbolTables),  // Destination Type
                        types::StringToType(func->returnType, symbolTables),  // Pointer Type
                        std::make_shared<llvm::LLVMRegister>(
                            returnRegister, 
                            types::StringToType(func->returnType, symbolTables)  
                        ),  
                        std::make_shared<llvm::LLVMRegister>(
                            "%_ret_val", 
                            types::StringToType(func->returnType, symbolTables) 
                        )  ));
                    }
                    if(func->getName() == "main"){
                        exitBlock->addInstruction(std::make_unique<llvm::Return>(std::make_shared<llvm::LLVMRegister>(
                            returnRegister, types::IntTy::getInstance()
                        )));
                    }else{
                        exitBlock->addInstruction(std::make_unique<llvm::Return>(std::make_shared<llvm::LLVMRegister>(
                            returnRegister, types::StringToType(func->returnType, symbolTables))));
                    }
                }else{
                    exitBlock->addInstruction(std::make_unique<llvm::Return>(
                            nullptr
                    ));
                }
                program->funcDefs[funcName].push_back(entryBlock);
                // Call the function body
                func->TranslateToLLVMIR(entryBlock, merge, exitBlock, symbolTables->functions->lookup(func->getName()), program, resultOperand);
                if(entryBlock->successors.empty()){
                    entryBlock->addSuccessor(exitBlock);
                    exit->addPredecessor(entryBlock);
                }
                // Store the function blocks in the program
                program->funcDefs[funcName].push_back(exitBlock);
            }

        }
    };

} // namespace ast