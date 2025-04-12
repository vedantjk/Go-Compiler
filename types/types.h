#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

// Forward declare `symboltable::SymbolTables`
namespace symboltable {
    class SymbolTables;
}

namespace types {

// Forward declarations for all types
    class Type;
    class IntTy;
    class BoolTy;
    class StructTy;
    class PointerTy;
    class VoidTy;

// Base Type class
    class Type {
    public:
        virtual std::string toString() const = 0;
        virtual ~Type() = default;
    };

// Integer Type (Singleton)
    class IntTy : public Type {
    private:
        IntTy() = default;
    public:
        static std::shared_ptr<IntTy> getInstance() {
            static std::shared_ptr<IntTy> instance(new IntTy());
            return instance;
        }
        std::string toString() const override { return "int"; }
    };

// Boolean Type (Singleton)
    class BoolTy : public Type {
    private:
        BoolTy() = default;
    public:
        static std::shared_ptr<BoolTy> getInstance() {
            static std::shared_ptr<BoolTy> instance(new BoolTy());
            return instance;
        }
        std::string toString() const override { return "bool"; }
    };

// Void Type (Singleton)
    class VoidTy : public Type {
    private:
        VoidTy() = default;
    public:
        static std::shared_ptr<VoidTy> getInstance() {
            static std::shared_ptr<VoidTy> instance(new VoidTy());
            return instance;
        }
        std::string toString() const override { return "void"; }
    };

// Forward declare the pointer type's factory function
    class PointerTy : public Type {
    private:
        std::shared_ptr<Type> baseType;
        explicit PointerTy(std::shared_ptr<Type> baseType) : baseType(std::move(baseType)) {}

    public:
        static std::shared_ptr<PointerTy> getPointerType(std::shared_ptr<Type> baseType);
        std::shared_ptr<Type> getBaseType() const { return baseType; }
        std::string toString() const override;
    };

// Struct Type
    class StructTy : public Type {
    private:
        std::string name;
        std::unordered_map<std::string, std::shared_ptr<Type>> fields;  // Fast lookup
        std::vector<std::pair<std::string, std::shared_ptr<Type>>> fieldsVec;  // Preserve order
        bool isBeingConstructed;

        explicit StructTy(std::string name)
                : name(std::move(name)), isBeingConstructed(true) {}

    public:
        static std::shared_ptr<StructTy> createStructType(const std::string& name);
        void finalizeFields(const std::unordered_map<std::string, std::shared_ptr<Type>>& newFields);
        bool hasField(const std::string& fieldName) const;
        std::shared_ptr<Type> getFieldType(const std::string& fieldName) const;
        std::string toString() const override;
        std::string getName() const { return name; }
        bool isIncomplete() const { return isBeingConstructed; }
        const std::unordered_map<std::string, std::shared_ptr<Type>>& getFields() const { return fields; }
        const std::vector<std::pair<std::string, std::shared_ptr<Type>>>& getFieldsOrdered() const { return fieldsVec; }
    };

// Define the implementations of the PointerTy methods
    inline std::shared_ptr<PointerTy> PointerTy::getPointerType(std::shared_ptr<Type> baseType) {
        static std::unordered_map<std::shared_ptr<Type>, std::weak_ptr<PointerTy>> cache;

        // Clean up expired entries
        for (auto it = cache.begin(); it != cache.end();) {
            if (it->second.expired()) {
                it = cache.erase(it);
            } else {
                ++it;
            }
        }

        // Try to find existing pointer type
        auto it = cache.find(baseType);
        if (it != cache.end()) {
            if (auto existing = it->second.lock()) {
                return existing;
            }
        }

        // Create new pointer type
        auto newPtr = std::shared_ptr<PointerTy>(new PointerTy(baseType));
        cache[baseType] = newPtr;
        return newPtr;
    }

    inline std::string PointerTy::toString() const {
        if (!baseType) return "*<unresolved>";

        if (auto structType = std::dynamic_pointer_cast<StructTy>(baseType)) {
            if (structType->isIncomplete()) {
                return "*" + structType->getName();
            }
        }
        return "*" + baseType->toString();
    }

// Define the implementations of the StructTy methods
    inline std::shared_ptr<StructTy> StructTy::createStructType(const std::string& name) {
        static std::unordered_map<std::string, std::shared_ptr<StructTy>> cache;
        auto it = cache.find(name);
        if (it != cache.end()) {
            return it->second;
        }
        auto newStruct = std::shared_ptr<StructTy>(new StructTy(name));
        cache[name] = newStruct;
        return newStruct;
    }

    inline void StructTy::finalizeFields(const std::unordered_map<std::string, std::shared_ptr<Type>>& newFields) {
        fields = newFields;
        fieldsVec.clear();
        for (const auto& field : newFields) {
            fieldsVec.emplace_back(field.first, field.second);  // Maintain insertion order
        }
        isBeingConstructed = false;
    }

    inline bool StructTy::hasField(const std::string& fieldName) const {
        return fields.count(fieldName) > 0;
    }

    inline std::shared_ptr<Type> StructTy::getFieldType(const std::string& fieldName) const {
        auto it = fields.find(fieldName);
        return (it != fields.end()) ? it->second : nullptr;
    }

    inline std::string StructTy::toString() const {
        if (isBeingConstructed) {
            return "struct " + name;
        }
        std::string result = "struct " + name + " { ";
        for (const auto& [fname, ftype] : fieldsVec) {  // Use vector for ordered iteration
            if (auto ptrType = std::dynamic_pointer_cast<PointerTy>(ftype)) {
                if (auto structType = std::dynamic_pointer_cast<StructTy>(ptrType->getBaseType())) {
                    if (structType->getName() == this->name) {
                        result += fname + ": *" + name + ", ";
                        continue;
                    }
                }
            }
            result += fname + ": " + ftype->toString() + ", ";
        }
        if (!fieldsVec.empty()) {
            result.pop_back();
            result.pop_back();
        }
        result += " }";
        return result;
    }

// Function to convert string to Type (Handles built-in and user-defined types)
    std::shared_ptr<Type> StringToType(const std::string& ty, std::shared_ptr<symboltable::SymbolTables> tables);

    bool isPointerType(const std::shared_ptr<types::Type>& type);
    bool isIntType(const std::shared_ptr<types::Type>& type);
    bool isStructType(const std::shared_ptr<types::Type>& type);
    bool isBoolTy(const std::shared_ptr<types::Type>& type);
    bool isVoidType(const std::shared_ptr<types::Type>& type);
} // namespace types