#pragma once

#include "../types/types.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>  // For std::pair

namespace symboltable {

// Scope Enum
    enum class VarScope {
        GLOBAL,
        LOCAL
    };

// Generic Symbol Table (For Variables, Functions, and Types)
    template <typename T>
    class SymbolTable {
    private:
        std::unordered_map<std::string, std::shared_ptr<T>> table;
        std::shared_ptr<SymbolTable<T>> parent; // Parent scope (for nested scopes)

    public:
        explicit SymbolTable(std::shared_ptr<SymbolTable<T>> parent = nullptr) : parent(std::move(parent)) {}

        void insert(const std::string& id, std::shared_ptr<T> entry) {
            table[id] = std::move(entry);
        }

        std::shared_ptr<T> lookup(const std::string& id) {
            if (table.find(id) != table.end()) {
                return table[id];
            }
            if (parent) {
                return parent->lookup(id); // Look in parent scope
            }
            return nullptr;
        }

        bool contains(const std::string& id) {
            return table.find(id) != table.end();
        }

        std::shared_ptr<SymbolTable<T>> getParent() const {
            return parent;
        }
        void print() const {
            for (const auto& pair : table) {
                std::cout << " - " << pair.first << std::endl;
            }
        }
        const std::unordered_map<std::string, std::shared_ptr<T>>& getTable() const {
            return table;
        }
    };

// Variable Entry (Symbol for a Variable)
    class VarEntry {
    public:
        std::pair<int, int> position;  // (line, column)
        std::string name;
        std::shared_ptr<types::Type> type;
        VarScope scope;

        VarEntry(std::string name, std::shared_ptr<types::Type> type, VarScope scope, std::pair<int, int> position)
                : name(std::move(name)), type(std::move(type)), scope(scope), position(position) {}

        std::string toString() const {
            return name + " : " + type->toString() + " [" + (scope == VarScope::GLOBAL ? "GLOBAL" : "LOCAL") + "]"
                   + " at (" + std::to_string(position.first) + "," + std::to_string(position.second) + ")";
        }
    };

// Function Entry (Symbol for a Function)
    class FuncEntry {
    public:
        std::pair<int, int> position;  // (line, column)
        std::string name;
        std::shared_ptr<types::Type> returnType;
        std::vector<std::shared_ptr<VarEntry>> parameters;
        std::shared_ptr<SymbolTable<VarEntry>> localVariables; // Local scope for function
        std::unordered_set<std::string> parametersLLVM;
        FuncEntry(std::string name, std::shared_ptr<types::Type> returnType,
                  std::vector<std::shared_ptr<VarEntry>> parameters, std::pair<int, int> position)
                : name(std::move(name)), returnType(std::move(returnType)), parameters(std::move(parameters)), position(position) {
            localVariables = std::make_shared<SymbolTable<VarEntry>>(); // Fixed
        }

        std::string toString() const {
            std::string paramStr = "(";
            for (const auto& param : parameters) {
                paramStr += param->toString() + ", ";
            }
            if (!parameters.empty()) {
                paramStr.pop_back();
                paramStr.pop_back();
            }
            paramStr += ")";
            return "func " + name + paramStr + " -> " + returnType->toString() +
                   " at (" + std::to_string(position.first) + "," + std::to_string(position.second) + ")";
        }
    };

// Global Symbol Tables (Stores Global Variables, Functions, and Types)
    class SymbolTables {
    public:
        std::shared_ptr<SymbolTable<VarEntry>> globals;  // Stores global variables
        std::shared_ptr<SymbolTable<FuncEntry>> functions; // Stores function definitions
        std::shared_ptr<SymbolTable<types::Type>> types;

        SymbolTables() {
            globals = std::make_shared<SymbolTable<VarEntry>>();
            functions = std::make_shared<SymbolTable<FuncEntry>>();
            types = std::make_shared<SymbolTable<types::Type>>();
        }

        // Debuggin symbol tables
        void PrintSymbolTables() {
            std::cout << "\n=== SYMBOL TABLES ===\n";

            try {
                // Print Global Variables
                std::cout << "\n[Global Variables]\n";
                if (!globals) {
                    std::cout << "(None)\n";
                } else {
                    globals->print();
                }
                // Print Struct Types
                std::cout << "\n[Struct Types]\n";
                if (!types || types->getTable().empty()) {
                    std::cout << "(None)\n";
                } else {
                    types->print();
                }

                std::cout << "=====================\n";
                // Print Functions and Their Local Variables
                std::cout << "\n[Function Declarations]\n";
                if (!functions || functions->getTable().empty()) {
                    std::cout << "(None)\n";
                } else {
                    for (const auto& pair : functions->getTable()) {
                        auto funcEntry = pair.second;
                        if (!funcEntry) {
                            std::cerr << "[ERROR] Encountered null function entry.\n";
                            continue; // Skip invalid entries
                        }

                        std::cout << " - " << funcEntry->name << " (return type: "
                                  << (funcEntry->returnType ? funcEntry->returnType->toString() : "<unknown>") << ")\n";

                        // === Print Function Parameters ===
                        if (funcEntry->parameters.empty()) {
                            std::cout << "   [Parameters] (None)\n";
                        } else {
                            std::cout << "   [Parameters]\n";
                            for (auto& param : funcEntry->parameters) {
                                if (!param) {
                                    std::cerr << "[ERROR] Null parameter found in function: " << funcEntry->name << "\n";
                                    continue; // Skip null parameters
                                }
                                std::string paramTypeStr = "<unknown>";
                                if (param->type) {
                                    paramTypeStr = param->type->toString();
                                    // Additional check: Ensure the type exists in `tables->types`
                                    if (std::dynamic_pointer_cast<types::StructTy>(param->type)) {
                                        if (!types->lookup(param->type->toString())) {
                                            std::cerr << "[ERROR] Struct type '" << param->type->toString()
                                                      << "' is not defined for parameter '" << param->name << "' in function '"
                                                      << funcEntry->name << "'.\n";
                                            paramTypeStr = "<undefined struct>";
                                        }
                                    }
                                } else {
                                    std::cerr << "[ERROR] Parameter '" << param->name << "' has no valid type in function: "
                                              << funcEntry->name << "\n";
                                }

                                std::cout << "     - " << param->name << " : " << paramTypeStr << "\n";
                            }
                        }

                        // === Print Local Variables ===
                        if (!funcEntry->localVariables || funcEntry->localVariables->getTable().empty()) {
                            std::cout << "   [Local Variables] (None)\n";
                        } else {
                            std::cout << "   [Local Variables]\n";
                            funcEntry->localVariables->print();
                        }
                    }

                }



            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Exception while printing symbol tables: " << e.what() << "\n";
            } catch (...) {
                std::cerr << "[ERROR] Unknown error occurred while printing symbol tables.\n";
            }
        }

        auto getTypes(){ return types;}
        auto getGlobals(){ return globals;}
        auto getFunctions() { return functions;}
    };

} // namespace symboltable
