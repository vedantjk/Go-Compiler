
#ifndef CODEGEN_H
#define CODEGEN_H

#include "../cfg/CFG.h"
#include "../llvm/LLVM.h"
#include "../symboltable/symboltable.h"
#include <map>
#include <string>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <set>
#include <cctype>

namespace codegen{

    class OutOfSSA{
        std::map<std::string, std::vector<std::tuple<std::string, int, int>>> funcToLiveInterval; // funcName -> vector of variableName, start, end
        std::map<std::string, std::unordered_map<std::string, int>> variableToIndex; // funcName -> { variable Name, index in the vector above}
        std::shared_ptr<symboltable::SymbolTables> tables;
        std::unordered_map<std::string, std::shared_ptr<cfg::Block>> labelToBlockMap;
        // Register allocation results (function name -> {variable name, physical register or "spill"})
        std::map<std::string, std::map<std::string, std::string>> regAllocation;
        std::map<std::string, std::map<std::string, std::pair<int, int>>> liveInterval;
        std::map<std::string, std::map<std::string, int>> spillLocations;
        std::map<std::string, int> functionStackSize;
        std::map<std::string, std::string> globalRegAllocations;
        std::unordered_map<std::string, std::map<std::string, int>> funcRegAllocations;
        std::vector<std::string> globalDeclarations;
        std::unordered_map<std::string, std::string> returnValue;
        std::unordered_map<std::string, int> funcSPVal;
        std::map<std::string, std::vector<std::shared_ptr<cfg::Block>>> _funcDefsReg;
        int spill_counter = 0;
    public:
        explicit OutOfSSA(std::shared_ptr<symboltable::SymbolTables> symTables, std::unordered_map<std::string, std::shared_ptr<cfg::Block>> labelToBlockMap,
                          std::vector<std::string> globalDeclaration, std::unordered_map<std::string, std::string> returnValue
        ) : tables(symTables), labelToBlockMap(labelToBlockMap), globalDeclarations(globalDeclaration), returnValue(returnValue){}
        void setLiveIntervals(const std::map<std::string, std::vector<std::shared_ptr<cfg::Block>>>& funcDefsReg);
        void setHelper(std::string regName, std::string funcName, int lineNumber);

        int getSpillCounter(){
            spill_counter++;
            return  spill_counter;
        }

        std::string generateARM();
        void printLiveIntervals();
        void linearScanRegisterAllocation();
        void printRegisterAllocation();
        void updateLLVMIR();
        void printUpdatedLLVMIR();
    };

}

#endif //CODEGEN_H
