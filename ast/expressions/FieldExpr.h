#pragma once

#include "Expression.h"
#include "../symboltable/symboltable.h"
#include "../utilities/context.h"
#include <string>
#include <memory>
#include "VariableExpr.h"

namespace ast {

    class FieldExpr : public Expression {
    public:
        std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> _localTable;
        std::shared_ptr<types::Type> rightMostType;
        std::shared_ptr<Expression> base;
        std::string field;
        bool errorReported;

        FieldExpr(int line, int column, std::shared_ptr<Expression> base, std::string field)
                : Expression(line, column), base(std::move(base)), field(std::move(field)), errorReported(false) {}

                // This function recursively gets the type of the right most field.
                // ex -> math.simp.bar -> gets the type of bar.
        std::shared_ptr<types::Type> resolveFieldType(
                std::vector<context::CompilerError>& errors,
                std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                std::shared_ptr<symboltable::FuncEntry> currentFunction) {

            std::shared_ptr<types::Type> baseType = nullptr;

            if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(base)) {
                std::string varName = varExpr->getIdentifier();
                auto tables = ASTNode::getSymbolTables();
                auto varEntry = localTable->lookup(varName);
                if (!varEntry) varEntry = tables->globals->lookup(varName);

                if (!varEntry) {
                    if (!errorReported) {
                        errors.emplace_back(line, column, "Variable '" + varName + "' not declared.",
                                            context::CompilerPhase::SEMANTIC);
                        errorReported = true;
                    }
                    return nullptr;
                }

                baseType = varEntry->type;
            }
            else if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpr>(base)) {
                baseType = fieldExpr->resolveFieldType(errors, localTable, currentFunction);
            }
            else {
                baseType = base->GetType(errors, localTable, currentFunction);
            }

            if (!baseType) return nullptr;

            while (auto ptrType = std::dynamic_pointer_cast<types::PointerTy>(baseType)) {
                baseType = ptrType->getBaseType();
            }

            auto structType = std::dynamic_pointer_cast<types::StructTy>(baseType);
            if (!structType) {
                if (!errorReported) {
                    errors.emplace_back(line, column,
                                        "Base expression must be a struct type, got '" + baseType->toString() + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    errorReported = true;
                }
                return nullptr;
            }

            if (!structType->hasField(field)) {
                if (!errorReported) {
                    errors.emplace_back(line, column,
                                        "Struct '" + structType->toString() + "' has no field named '" + field + "'.",
                                        context::CompilerPhase::SEMANTIC);
                    errorReported = true;
                }
                return nullptr;
            }

            return structType->getFieldType(field);
        }

        void BuildSymbolTable(std::vector<context::CompilerError>& errors,
                              std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                              std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            _localTable = localTable;
            base->BuildSymbolTable(errors, localTable, currentFunction);
            rightMostType  =  resolveFieldType(errors, localTable, currentFunction);
        }

        std::shared_ptr<types::Type> GetType(std::vector<context::CompilerError>& errors,
                                             std::shared_ptr<symboltable::SymbolTable<symboltable::VarEntry>> localTable,
                                             std::shared_ptr<symboltable::FuncEntry> currentFunction = nullptr) override {
            return resolveFieldType(errors, localTable, currentFunction);
        }

        void TranslateToLLVMIR(
                std::shared_ptr<cfg::Block>& current,
                std::shared_ptr<cfg::Block>& merge,
                std::shared_ptr<cfg::Block>& exit,
                std::shared_ptr<symboltable::FuncEntry> currentFunc,
                std::shared_ptr<llvm::LLVMProgram> program,
                std::shared_ptr<llvm::LLVMOperand>& resultOperand,
                bool isLvalue = false) override {

            auto tables = ASTNode::getSymbolTables();
            if (!tables) {
                return;
            }

            std::vector<context::CompilerError> errors;
            // Get the base type and handle pointer types
            auto baseType = base->GetType(errors, _localTable, currentFunc);
            auto originalBaseType = baseType;

            // If it's a pointer, we need to dereference it
            bool isPointer = false;
            if (auto ptrType = std::dynamic_pointer_cast<types::PointerTy>(baseType)) {
                isPointer = true;
                baseType = ptrType->getBaseType();
            }

            auto structType = std::dynamic_pointer_cast<types::StructTy>(baseType);
            if (!structType) {
                return;
            }

            // Find field index
            int fieldIndex = -1;
            int index = 0;
            for (const auto& [name, type] : structType->getFields()) {
                if (name == field) {
                    fieldIndex = index;
                    break;
                }
                index++;
            }

            if (fieldIndex == -1) {
                return;
            }

            // Resolve base pointer
            std::shared_ptr<llvm::LLVMOperand> baseOperand = nullptr;
            base->TranslateToLLVMIR(current, merge, exit, currentFunc, program, baseOperand);

            if (!baseOperand) {
                return;
            }

            // If the base is already a pointer, we can use it directly
            // Otherwise, if it's a struct value, we need to get its address first
            std::string baseStr = baseOperand->toString();
           if (!isPointer) {
                std::string addrReg = "%r" + std::to_string(program->getNextRegister());
                auto baseLLVMType = baseType;

                // Replace raw alloca instruction with Alloc class
                current->addInstruction(std::make_unique<llvm::Alloc>(
                    baseLLVMType,
                    std::make_shared<llvm::LLVMRegister>(addrReg, baseLLVMType)
                ));

                // Replace raw store instruction with Store class
                current->addInstruction(std::make_unique<llvm::Store>(
                    baseLLVMType,
                    std::make_shared<llvm::LLVMVariableOperand>(baseStr, baseLLVMType),  // Value to store
                    std::make_shared<llvm::LLVMRegister>(addrReg, baseLLVMType)  // Destination (allocated memory)
                ));

                baseStr = addrReg;
            }



            // Generate GEP instruction to get field address
            std::string gepReg = "%r" + std::to_string(program->getNextRegister());

            current->addInstruction(std::make_unique<llvm::GetElementPtr>(
            std::make_shared<llvm::LLVMRegister>(gepReg, structType),  // Destination register
            structType,  // Base type (struct type)
            std::make_shared<llvm::LLVMRegister>(baseStr, structType),  // Base pointer operand
            std::vector<int>{0, fieldIndex}  // Indices (struct offset calculation)
            ));

            // Get the field type
            auto fieldType = structType->getFieldType(field);
            std::string fieldTypeLLVM = llvm::LLVMProgram::typeToLLVMType(fieldType);

            if (isLvalue) {
                // If used as an lvalue (for assignment), return the pointer to the field
                resultOperand = std::make_shared<llvm::LLVMAddressOperand>(gepReg, fieldType);
            } else {
                // Generate a new register for the load instruction
                std::string loadReg = "%r" + std::to_string(program->getNextRegister());

                // Create an LLVM load instruction using the Load class
                auto loadInstruction = std::make_unique<llvm::Load>(
                    fieldType,   // Destination Type
                    fieldType,  // Pointer Type
                    std::make_shared<llvm::LLVMRegister>(loadReg, fieldType),  // Destination Register
                    std::make_shared<llvm::LLVMRegister>(gepReg, fieldType) // Source Operand (Pointer)
                );

                // Add the load instruction to the current block
                current->addInstruction(std::move(loadInstruction));

                // Set the result operand to the loaded value
                resultOperand = std::make_shared<llvm::LLVMVariableOperand>(loadReg, fieldType);
                
            }
        }


        void print(std::ostream& out, int tab) const override {
            base->print(out, tab);
            out << "." << field;
        }
    };

} // namespace ast