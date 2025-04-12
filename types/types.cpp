#include "types.h"
#include "../symboltable/symboltable.h"

namespace types {

    std::shared_ptr<Type> StringToType(const std::string& ty, std::shared_ptr<symboltable::SymbolTables> tables) {

        if (ty == "int") return IntTy::getInstance();
        if (ty == "bool") return BoolTy::getInstance();
        if (ty == "void") return VoidTy::getInstance();

        // Handle pointer types (e.g., "*Node")
        if (ty.front() == '*') {
            std::string baseType = ty.substr(1); // Remove '*'
            auto base = StringToType(baseType, tables);
            if (!base) {
                return nullptr;
            }
            return types::PointerTy::getPointerType(base);
        }

        // Lookup struct types in `tables->types`
        auto structType = tables->types->lookup(ty);
        if (!structType) {
            return nullptr;
        }

        return structType;
    }

    bool isPointerType(const std::shared_ptr<types::Type>& type) {
        return std::dynamic_pointer_cast<types::PointerTy>(type) != nullptr;
    }

    bool isIntType(const std::shared_ptr<types::Type>& type){
        return std::dynamic_pointer_cast<types::IntTy>(type)!= nullptr;
    }

    bool isStructType(const std::shared_ptr<types::Type>& type){
        return std::dynamic_pointer_cast<types::StructTy>(type)!= nullptr;
    }

    bool isBoolTy(const std::shared_ptr<types::Type>& type){
        return std::dynamic_pointer_cast<types::BoolTy>(type)!= nullptr;
    }

    bool isVoidType(const std::shared_ptr<types::Type>& type) {
        return std::dynamic_pointer_cast<types::VoidTy>(type) != nullptr;
    }


} // namespace types
