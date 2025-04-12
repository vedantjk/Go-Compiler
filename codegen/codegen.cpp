#include "codegen.h"

namespace codegen{

    void OutOfSSA::setHelper(std::string regName, std::string funcName, int lineNumber) {
        if(variableToIndex[funcName].find(regName) == variableToIndex[funcName].end()){
            funcToLiveInterval[funcName].emplace_back(regName, lineNumber, -1);
            variableToIndex[funcName][regName] = (int)funcToLiveInterval[funcName].size();
        }else {
            int index = variableToIndex[funcName][regName];
            auto& targetTuple = funcToLiveInterval[funcName][index-1]; // Adjust index if necessary
            int currentStartTime = std::get<1>(targetTuple);
            int currentEndTime = std::get<2>(targetTuple);
            std::get<2>(targetTuple) = std::max(currentEndTime, lineNumber);
            if (currentStartTime > std::get<2>(targetTuple)) {
                std::get<1>(targetTuple) = std::get<2>(targetTuple);
                std::get<2>(targetTuple) = currentStartTime;
            }
        }
    }

    void OutOfSSA::setLiveIntervals(const std::map<std::string, std::vector<std::shared_ptr<cfg::Block>>>& funcDefsReg){
        _funcDefsReg = funcDefsReg;
        std::vector<std::string> regsForGlobals = {"x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28"};
        auto globalVars = tables->getGlobals()->getTable();
        int i = 0;
        globalRegAllocations["read_scratch"] = regsForGlobals[i++];
        for(auto& x : globalVars){
            globalRegAllocations["@"+x.first] = regsForGlobals[i++];
        }
        for(const auto& [funcName, blocks] : funcDefsReg){
            int currentLine = 0;
            for(auto& block : blocks){
                currentLine += (int)block->instructions.size();
                block->lastLine = currentLine;
            }
        }

        for(const auto& [funcName, blocks] : funcDefsReg){
            int lineNumber = 0;
            auto funcEntry = tables->functions->lookup(funcName);
            if (funcEntry && !funcEntry->parameters.empty()) {
                for (auto & param : funcEntry->parameters) {
                    std::string paramName = "%" + param->name;
                    funcToLiveInterval[funcName].emplace_back(paramName, 0, -1);
                    variableToIndex[funcName][paramName] = (int)funcToLiveInterval[funcName].size();
                }
            }
            for(auto& block : blocks){
                for(const auto& inst : block->instructions){
                    lineNumber++;
                    if(auto* binInst = dynamic_cast<llvm::BinOp*>(inst.get())){
                        auto operandVec = binInst->returnRegister();
                        auto destReg = std::dynamic_pointer_cast<llvm::LLVMRegister>(operandVec[0]);
                        auto op1 = operandVec[1];
                        auto op2 = operandVec[2];
                        auto op1str = op1->toString();
                        auto op2str = op2->toString();
                        bool processOp1 = (op1str[0] == '%') || (op1str[0] == '@');

                        bool processOp2 = (op2str[0] == '%') || (op2str[0] == '@');

                        setHelper(destReg->toString(), funcName, lineNumber);
                        if(processOp1){
                            setHelper(op1->toString(), funcName, lineNumber);
                        }

                        if(processOp2){
                            setHelper(op2->toString(), funcName, lineNumber);
                        }
                    }
                    if(auto* branchInst = dynamic_cast<llvm::Branch*>(inst.get())){
                        auto operandVec = branchInst->returnRegister();
                        if(operandVec[0] == nullptr){
                            continue;
                        }else{
                            setHelper(operandVec[0]->toString(), funcName, lineNumber);
                        }
                    }
                    if(auto* callInst = dynamic_cast<llvm::Call*>(inst.get())){
                        auto operandVec = callInst->returnRegister();
                        if(operandVec[0] != nullptr){
                            setHelper(operandVec[0]->toString(), funcName, lineNumber);
                        }
                        auto argList = callInst->getArgList();
                        for(const auto& x : argList){
                            if(x.second[0] == '%' || x.second[0] == '@')
                                setHelper(x.second, funcName, lineNumber);
                        }
                    }
                    if(auto* phiInst = dynamic_cast<cfg::PhiInstruction*>(inst.get())){
                        auto destReg = phiInst->returnResult();
                        auto pairs = phiInst->returnPairs();
                        setHelper(destReg, funcName, lineNumber);
                        for(auto& x : pairs){
                            if(x.first == destReg){
                                std::string blockLabel = x.second;
                                blockLabel = blockLabel.substr(1);
                                auto b = labelToBlockMap[blockLabel];
                                auto l = b->lastLine;
                                setHelper(destReg, funcName, l);
                                continue;
                            }

                            if(x.first[0]!='%') continue;
                            setHelper(x.first, funcName, lineNumber);
                        }
                    }
                    if(auto* unaryInst = dynamic_cast<llvm::UnaryOp*>(inst.get())){
                        auto operandVec = unaryInst->returnRegister();
                        auto destReg = operandVec[0];
                        auto opReg = operandVec[1];
                        if(opReg->toString()[0]!='%' || opReg->toString()[0]!='@') continue;
                        setHelper(destReg->toString(), funcName, lineNumber);
                        setHelper(opReg->toString(), funcName, lineNumber);
                    }
                    if(auto* loadInst = dynamic_cast<llvm::Load*>(inst.get())){
                        auto operandVec = loadInst->returnRegister();
                        auto destReg = operandVec[0];
                        setHelper(destReg->toString(), funcName, lineNumber);
                    }
                    if(auto* truncInst = dynamic_cast<llvm::Trunc*>(inst.get())){
                        auto operandVec = truncInst->returnRegister();
                        auto destReg = operandVec[0];
                        auto source = operandVec[1];
                        setHelper(destReg->toString(), funcName, lineNumber);
                        setHelper(source->toString(), funcName, lineNumber);
                    }
                    if(auto* printInst = dynamic_cast<llvm::Print*>(inst.get())){
                        auto operandVec = printInst->returnRegister();
                        for(const auto& x : operandVec){
                            if(x->toString()[0] == '@' || x->toString()[0] == '%')
                                setHelper(x->toString(), funcName, lineNumber);
                        }
                    }
                    if(auto* returnInst = dynamic_cast<llvm::Return*>(inst.get())){
                        auto operandVec = returnInst->returnRegister();
                        if(operandVec[0] != nullptr){
                            std::string opStr = operandVec[0]->toString();
                            if((opStr[0] == '%') || (opStr[0] == '@')){
                                setHelper(operandVec[0]->toString(), funcName, lineNumber);
                            }
                        }
                    }
                }
            }
        }
        linearScanRegisterAllocation();
    }

    void OutOfSSA::printLiveIntervals() {
        if (funcToLiveInterval.empty()) {
            std::cout << "No live intervals to display." << std::endl;
            return;
        }

        std::cout << "=== LIVE INTERVALS ===" << std::endl;

        for (const auto& [functionName, intervals] : funcToLiveInterval) {
            std::cout << "\nFunction: " << functionName << std::endl;
            std::cout << "-----------------------------" << std::endl;
            std::cout << std::left << std::setw(20) << "Variable"
                      << std::setw(10) << "Start"
                      << std::setw(10) << "End" << std::endl;
            std::cout << "-----------------------------" << std::endl;

            for (const auto& interval : intervals) {
                const auto& [variableName, start, end] = interval;
                std::cout << std::left << std::setw(20) << variableName
                          << std::setw(10) << start
                          << std::setw(10) << end << std::endl;
            }
        }

        std::cout << "\n=== END LIVE INTERVALS ===" << std::endl;
    }


    void OutOfSSA::linearScanRegisterAllocation() {
        // ARM64 registers available for allocation
        // Excluding reserved registers: x9 (spill), x16, x17, x18, x29, x30, sp
        std::vector<std::string> physicalRegisters = {
                "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
                "x10", "x11", "x12", "x13", "x14", "x15", "x19",
                "x20", "x21", "x22", "x23", "x24", "x25", "x26",
                "x27", "x28"
        };



        // Process each function separately
        for (const auto& [funcName, intervals] : funcToLiveInterval) {
            std::set<int> regIndex;
            for(int i = 0; i<physicalRegisters.size(); i++){
                regIndex.insert(i);
            }

            regAllocation[funcName] = std::map<std::string, std::string>();
            funcSPVal[funcName] = 0;

            auto funcEntry = tables->getFunctions()->lookup(funcName);
            auto parameters = funcEntry->parameters;
            for(auto& x : parameters){
                regAllocation[funcName]["%" + x->name] = physicalRegisters[*regIndex.begin()];
                if(funcRegAllocations[funcName].find(physicalRegisters[*regIndex.begin()]) == funcRegAllocations[funcName].end())
                    funcRegAllocations[funcName][physicalRegisters[*regIndex.begin()]] = (int)funcRegAllocations[funcName].size();
                regIndex.erase(*regIndex.begin());

            }

            // Convert tuples to a sortable structure with original indices
            std::vector<std::tuple<std::string, int, int, int>> sortableIntervals;
            for (size_t i = 0; i < intervals.size(); i++) {
                auto [varName, start, end] = intervals[i];
                sortableIntervals.emplace_back(varName, start, end, i);
            }

            std::sort(sortableIntervals.begin(), sortableIntervals.end(),
                      [](const auto& a, const auto& b) {
                          return std::get<1>(a) < std::get<1>(b);
                      });

            // Active intervals (variable name, end point, index, assigned register)
            std::vector<std::tuple<std::string, int, int, std::string>> active;

            // Process intervals in order of increasing start point
            for (const auto& [varName, start, end, origIndex] : sortableIntervals) {

                if(regAllocation[funcName].find(varName)!=regAllocation[funcName].end()) continue;
                auto it = active.begin();
                while (it != active.end()) {
                    auto [activeVar, activeEnd, index, activeReg] = *it;
                    if (activeEnd < start) {
                        regIndex.insert(index);
                        it = active.erase(it);
                    } else {
                        ++it;
                    }
                }

                if (!regIndex.empty()) {
                    int regIdx = *regIndex.begin();
                    std::string reg = physicalRegisters[regIdx];
                    regIndex.erase(regIndex.begin());

                    regAllocation[funcName][varName] = reg;

                    // Add to active set
                    active.emplace_back(varName, end, regIdx, reg);
                    if(funcRegAllocations[funcName].find(reg) == funcRegAllocations[funcName].end())
                        funcRegAllocations[funcName][reg] = (int)funcRegAllocations[funcName].size();
                    funcSPVal[funcName] = std::max(funcSPVal[funcName] , (int)active.size());
                } else {
                    // No free registers, need to spill

                    std::string reg = "spill_" + std::to_string(getSpillCounter());
                    regAllocation[funcName][varName] = reg;
                    if(funcRegAllocations[funcName].find(reg) == funcRegAllocations[funcName].end())
                        funcRegAllocations[funcName][reg] = (int)funcRegAllocations[funcName].size();
                }
            }

        }

        for (const auto& [functionName, intervals] : funcToLiveInterval){
            for(const auto& interval : intervals){
                auto [varName, start, end] = interval;
                liveInterval[functionName][varName] = {start, end};
            }
        }

        updateLLVMIR();
    }

    void OutOfSSA::updateLLVMIR() {
        for(auto& [funcName, blocks] : _funcDefsReg){
            for(auto& block : blocks){
                for(auto& inst : block->instructions){
                    if(auto* binInst = dynamic_cast<llvm::BinOp*>(inst.get())){
                        auto operandVec = binInst->returnRegister();

                        for(auto &x : operandVec){
                            if(regAllocation[funcName].find(x->toString()) != regAllocation[funcName].end()){
                                x->setName(regAllocation[funcName][x->toString()]);
                            }
                        }

                    }
                    if(auto* phiInst = dynamic_cast<cfg::PhiInstruction*>(inst.get())){
                        auto result = phiInst->returnResult();
                        auto pairs = phiInst->returnPairs();
                        std::string dest =  regAllocation[funcName][result];
                        if(liveInterval[funcName][result].second == -1) continue;
                        for(auto& x : pairs){
                            std::string source = x.first;

                            if(regAllocation[funcName].find(source)!=regAllocation[funcName].end())
                                source = regAllocation[funcName][x.first];
                            else
                                source.insert(source.begin(), '#');

                            std::string phiBlockLabel = x.second.substr(1);
                            auto phiBlock = labelToBlockMap[phiBlockLabel];
                            auto movOp = std::make_unique<cfg::MovInstruction>(dest, source);
                            phiBlock->instructions.insert(phiBlock->instructions.end() - 1, std::move(movOp));
                        }
                    }
                    if(auto* branchInst = dynamic_cast<llvm::Branch*>(inst.get())){
                        auto operandVec = branchInst->returnRegister();
                        if(operandVec[0] == nullptr){
                            continue;
                        }else{
                            for(auto &x : operandVec){

                                if(regAllocation[funcName].find(x->toString()) != regAllocation[funcName].end()){
                                    x->setName(regAllocation[funcName][x->toString()]);
                                }
                            }
                        }
                    }
                    if(auto* returnInst = dynamic_cast<llvm::Return*>(inst.get())){
                        auto operandVec = returnInst->returnRegister();
                        if(operandVec[0] == nullptr){
                            continue;
                        }else{
                            for(auto &x : operandVec){
                                if(regAllocation[funcName].find(x->toString()) != regAllocation[funcName].end()){
                                    x->setName(regAllocation[funcName][x->toString()]);
                                }
                            }
                        }
                    }
                    if(auto* callInst = dynamic_cast<llvm::Call*>(inst.get())){
                        auto operandVec = callInst->returnRegister();
                        if(operandVec[0] != nullptr){
                            if(regAllocation[funcName].find(operandVec[0]->toString()) != regAllocation[funcName].end()){
                                operandVec[0]->setName(regAllocation[funcName][operandVec[0]->toString()]);
                            }
                        }
                        auto argList = callInst->getArgList();
                        std::vector<std::pair<std::string, std::string>> newArgList;
                        for(const auto& x : argList){
                            std::string newArg = x.second;
                            if(x.second[0] == '%' || x.second[0] == '@'){
                                if(regAllocation[funcName].find(x.second) != regAllocation[funcName].end()){
                                    newArg = regAllocation[funcName][x.second];
                                }
                            }
                            newArgList.emplace_back(x.first, newArg);
                        }
                        callInst->updateArgList(newArgList);
                    }
                    if(auto* unaryInst = dynamic_cast<llvm::UnaryOp*>(inst.get())){
                        auto operandVec = unaryInst->returnRegister();
                        for(auto &x : operandVec){
                            if(regAllocation[funcName].find(x->toString()) != regAllocation[funcName].end()){
                                x->setName(regAllocation[funcName][x->toString()]);
                            }
                        }

                    }
                    if(auto* loadInst = dynamic_cast<llvm::Load*>(inst.get())){
                        auto operandVec = loadInst->returnRegister();
                        auto destReg = operandVec[0];
                        if(regAllocation[funcName].find(destReg->toString()) != regAllocation[funcName].end()){
                            destReg->setName(regAllocation[funcName][destReg->toString()]);
                        }
                    }
                    if(auto* truncInst = dynamic_cast<llvm::Trunc*>(inst.get())){
                        auto operandVec = truncInst->returnRegister();
                        for(auto &x : operandVec){
                            if(regAllocation[funcName].find(x->toString()) != regAllocation[funcName].end()){
                                x->setName(regAllocation[funcName][x->toString()]);
                            }
                        }
                    }
                    if(auto* printInst = dynamic_cast<llvm::Print*>(inst.get())){
                        auto operandVec = printInst->returnRegister();
                        for(auto &x : operandVec){
                            if(regAllocation[funcName].find(x->toString()) != regAllocation[funcName].end()){
                                x->setName(regAllocation[funcName][x->toString()]);
                            }
                        }
                        printInst->buildInstructionString();
                    }
                }
            }
        }
    }

    std::string OutOfSSA::generateARM() {
        int printCounter = 1;
        std::stringstream ss;
        std::stringstream pp;
        ss << "        .arch armv8-a\n";
        ss << "        .comm read_scratch,8,8\n";
        auto table = tables->getGlobals()->getTable();
        for(auto& x : table){
            auto name = x.first;
            ss << "        .comm "<<name<<",8,8\n";
        }


        ss << "        .text\n";
        for(auto& [funcName, blocks] : _funcDefsReg){
            std::unordered_map<std::string, int> activeRegisters;
            auto fE = tables->getFunctions()->lookup(funcName);
            auto ps = fE->parameters;
            int c = 0;
            for(auto& x : ps){
                activeRegisters["x" + std::to_string(c)] = (int)activeRegisters.size();
                c++;
            }
            ss << "        .type "<<funcName<<", %function\n";
            ss << "        .global "<<funcName<<"\n";
            ss << "        .p2align 2\n";
            ss << "\n";
            ss << funcName<<":\n";
            int spVal = ((int)funcRegAllocations[funcName].size())*8 + 16;
            if(spVal%16) spVal += 8;
            ss << "    sub sp, sp, #" << spVal<<"\n";
            ss << "    stp x29, x30, [sp]\n";
            ss << "    mov x29, sp\n";
            bool isFirst = true;
            for(auto& block : blocks){
                if(isFirst){
                    isFirst = false;
                }else{
                    ss<<"."<<block->label<<":\n";
                }
                for(auto& inst : block->instructions){
                    if(auto* scanInst = dynamic_cast<llvm::Scan*>(inst.get())){
                        for(auto& x : funcRegAllocations[funcName]){
                            ss<<"    str "<<x.first<<", [sp, #"<<(x.second+2)*8<<"]\n";
                        }
                        ss<< "    adrp x0, .READ\n"
                        << "    add x0, x0, :lo12:.READ\n"
                        << "    adrp x1, read_scratch\n"
                        << "    add x1, x1, :lo12:read_scratch\n"
                        << "    bl scanf\n";
                        for(auto& x : funcRegAllocations[funcName]){
                            ss<<"    ldr "<<x.first<<", [sp, #"<<(x.second+2)*8<<"]\n";
                        }
                    }
                    if(auto* loadInst = dynamic_cast<llvm::Load*>(inst.get())){

                        auto operandVec = loadInst->returnRegister();
                        auto destReg = operandVec[0];
                        auto opReg = operandVec[1];
                        if(activeRegisters.find(destReg->toString()) == activeRegisters.end()){
                            activeRegisters[destReg->toString()] = (int)activeRegisters.size();
                        }
                        if(opReg->toString() == "@.read_scratch"){
                            ss<< "    adrp "
                              << destReg->toString()<<", read_scratch\n"
                              << "    add "<< destReg->toString()<< ", "
                              << destReg->toString()<<", :lo12:read_scratch\n"
                              << "    ldr "<<destReg->toString()<<", ["<<destReg->toString()<<"]\n";
                        }
                        else if(opReg->toString()[0] == '@'){
                            ss << "    adrp "<<globalRegAllocations[opReg->toString()]<<", "<<opReg->toString().substr(1)<<"\n";
                            ss << "    add "<<globalRegAllocations[opReg->toString()]<<", "<<globalRegAllocations[opReg->toString()]<<", :lo12:"<<opReg->toString().substr(1)<<"\n";
                            ss << "    ldr "<<destReg->toString()<<", ["<<globalRegAllocations[opReg->toString()]<<"]\n";
                        }
                        else if(opReg->toString()!="@.read_scratch"){
                            ss<<"    ldr "
                              << destReg->toString()<<", [sp, #"<<std::to_string((activeRegisters[destReg->toString()]+2)*8)<<"]\n";
                        }

                    }
                    if(auto* binInst = dynamic_cast<llvm::BinOp*>(inst.get())) {
                        auto operandVec = binInst->returnRegister();
                        auto destReg = operandVec[0];
                        if(activeRegisters.find(destReg->toString()) == activeRegisters.end()){
                            activeRegisters[destReg->toString()] = (int)activeRegisters.size();
                        }
                        auto op1 = operandVec[1];
                        auto op2 = operandVec[2];

                        std::string binTy = binInst->returnBinTy();
                        std::string op1Str = op1->toString();
                        std::string op2Str = op2->toString();
                        bool op1IsImm = !std::isalpha(op1Str[0]);
                        bool op2IsImm = !std::isalpha(op2Str[0]);

                        // Handle different binary operations
                        if(binTy == "add" || binTy == "sub") {
                            // For add/sub, immediates can be the second operand
                            if(op1IsImm && !op2IsImm) {
                                // Swap operands to ensure immediate is in the second position
                                std::swap(op1, op2);
                                std::swap(op1Str, op2Str);
                                std::swap(op1IsImm, op2IsImm);

                                // For subtraction, we need to negate the operation when swapping
                                if(binTy == "sub") {
                                    binTy = "rsb"; // Reverse subtract (not directly available in ARM64)
                                    ss << "    // Reverse subtraction: using neg and add\n";
                                    ss << "    neg " << op2Str << ", " << op2Str << "\n";
                                    ss << "    add " << destReg->toString() << ", " << op2Str << ", #" << op1Str << "\n";
                                    continue;
                                }
                            }

                            // Format operands
                            if(!op1IsImm) {
                                if(activeRegisters.find(op1->toString()) == activeRegisters.end()){
                                    activeRegisters[op1->toString()] = (int)activeRegisters.size();
                                }
                            } else {
                                op1Str = "#" + op1Str;
                            }

                            if(!op2IsImm) {
                                if(activeRegisters.find(op2->toString()) == activeRegisters.end()){
                                    activeRegisters[op2->toString()] = (int)activeRegisters.size();
                                }
                            } else {
                                op2Str = "#" + op2Str;
                            }

                            // Both operands are immediates
                            if(op1IsImm && op2IsImm) {
                                ss << "    mov x16, " << op1Str << "\n";
                                ss << "    " << binTy << " " << destReg->toString() << ", x16, " << op2Str << "\n";
                            } else {
                                ss << "    " << binTy << " " << destReg->toString() << ", " << op1Str << ", " << op2Str << "\n";
                            }
                        }
                        else if(binTy == "mul") {
                            // For multiplication, both operands must be registers
                            if(!op1IsImm) {
                                if(activeRegisters.find(op1->toString()) == activeRegisters.end()){
                                    activeRegisters[op1->toString()] = (int)activeRegisters.size();
                                }
                            }

                            if(!op2IsImm) {
                                if(activeRegisters.find(op2->toString()) == activeRegisters.end()){
                                    activeRegisters[op2->toString()] = (int)activeRegisters.size();
                                }
                            }

                            if(op1IsImm && op2IsImm) {
                                // Both are immediates, load both into registers
                                ss << "    mov x16, #" << op1Str << "\n";
                                ss << "    mov x17, #" << op2Str << "\n";
                                ss << "    mul " << destReg->toString() << ", x16, x17\n";
                            }
                            else if(op1IsImm) {
                                // First operand is immediate, load it into a register
                                ss << "    mov x16, #" << op1Str << "\n";
                                ss << "    mul " << destReg->toString() << ", x16, " << op2Str << "\n";
                            }
                            else if(op2IsImm) {
                                // Second operand is immediate, load it into a register
                                ss << "    mov x16, #" << op2Str << "\n";
                                ss << "    mul " << destReg->toString() << ", " << op1Str << ", x16\n";
                            }
                            else {
                                // Both are registers, use directly
                                ss << "    mul " << destReg->toString() << ", " << op1Str << ", " << op2Str << "\n";
                            }
                        }
                        else if(binTy == "sdiv") {

                            if(!op1IsImm) {
                                if(activeRegisters.find(op1->toString()) == activeRegisters.end()){
                                    activeRegisters[op1->toString()] = (int)activeRegisters.size();
                                }
                            }

                            if(!op2IsImm) {
                                if(activeRegisters.find(op2->toString()) == activeRegisters.end()){
                                    activeRegisters[op2->toString()] = (int)activeRegisters.size();
                                }
                            }

                            // Generate the appropriate division code
                            if(op1IsImm && op2IsImm) {
                                // Both are immediates, load both into registers
                                ss << "    mov x16, #" << op1Str << "\n";
                                ss << "    mov x17, #" << op2Str << "\n";
                                ss << "    sdiv " << destReg->toString() << ", x16, x17\n";
                            }
                            else if(op1IsImm) {
                                // First operand is immediate, load it into a register
                                ss << "    mov x16, #" << op1Str << "\n";
                                ss << "    sdiv " << destReg->toString() << ", x16, " << op2Str << "\n";
                            }
                            else if(op2IsImm) {
                                // Second operand is immediate, load it into a register
                                ss << "    mov x16, #" << op2Str << "\n";
                                ss << "    sdiv " << destReg->toString() << ", " << op1Str << ", x16\n";
                            }
                            else {
                                // Both are registers, use directly
                                ss << "    sdiv " << destReg->toString() << ", " << op1Str << ", " << op2Str << "\n";
                            }
                        }
                        else if(binTy.substr(0, 4) == "icmp") {
                            // Extract the comparison type from the binTy string
                            std::string cmpType = binTy.substr(5); // Skip "icmp " to get the comparison type

                            if(!op1IsImm) {
                                if(activeRegisters.find(op1->toString()) == activeRegisters.end()){
                                    activeRegisters[op1->toString()] = (int)activeRegisters.size();
                                }
                            }

                            if(!op2IsImm) {
                                if(activeRegisters.find(op2->toString()) == activeRegisters.end()){
                                    activeRegisters[op2->toString()] = (int)activeRegisters.size();
                                }
                            }

                            // Generate the appropriate comparison code
                            if(op1IsImm && op2IsImm) {
                                // Both are immediates, load both into registers
                                ss << "    mov x16, #" << op1Str << "\n";
                                ss << "    mov x17, #" << op2Str << "\n";
                                ss << "    cmp x16, x17\n";
                            }
                            else if(op1IsImm) {
                                // First operand is immediate, load it into a register
                                ss << "    mov x16, #" << op1Str << "\n";
                                ss << "    cmp x16, " << op2Str << "\n";
                            }
                            else if(op2IsImm) {
                                // Second operand is immediate
                                ss << "    cmp " << op1Str << ", #" << op2Str << "\n";
                            }
                            else {
                                // Both are registers, use directly
                                ss << "    cmp " << op1Str << ", " << op2Str << "\n";
                            }

                            // Handle the specific comparison type
                            if(cmpType == "sgt") {
                                ss << "    cset " << destReg->toString() << ", gt\n";
                            }
                            else if(cmpType == "eq") {
                                ss << "    cset " << destReg->toString() << ", eq\n";
                            }
                            else if(cmpType == "ne") {
                                ss << "    cset " << destReg->toString() << ", ne\n";
                            }
                            else if(cmpType == "slt") {
                                ss << "    cset " << destReg->toString() << ", lt\n";
                            }
                            else if(cmpType == "sle") {
                                ss << "    cset " << destReg->toString() << ", le\n";
                            }
                            else if(cmpType == "sge") {
                                ss << "    cset " << destReg->toString() << ", ge\n";
                            }
                                // Handle unsigned comparisons
                            else if(cmpType == "ugt") {
                                ss << "    cset " << destReg->toString() << ", hi\n";
                            }
                            else if(cmpType == "uge") {
                                ss << "    cset " << destReg->toString() << ", hs\n";
                            }
                            else if(cmpType == "ult") {
                                ss << "    cset " << destReg->toString() << ", lo\n";
                            }
                            else if(cmpType == "ule") {
                                ss << "    cset " << destReg->toString() << ", ls\n";
                            }
                        }
                    }
                    if(auto* printInst = dynamic_cast<llvm::Print*>(inst.get())){
                        for(auto& x : funcRegAllocations[funcName]){
                            ss<<"    str "<<x.first<<", [sp, #"<<(x.second+2)*8<<"]\n";
                        }
                        auto operandVec = printInst->returnRegister();
                        ss<<"    adrp x0, .PRINT_"<<printCounter<<"\n"
                        <<"    add x0, x0, :lo12:.PRINT_"<<printCounter<<"\n";
                        auto prnt = operandVec[0];
                        auto prntStr = (funcRegAllocations[funcName][prnt->toString()] + 2)*8;
                        ss<<"    ldr x1, [sp, #"<<std::to_string(prntStr)<<"]\n";
                        ss<<"    bl printf\n";
                        for(auto& x : funcRegAllocations[funcName]){
                            ss<<"    ldr "<<x.first<<", [sp, #"<<(x.second+2)*8<<"]\n";
                        }
                        auto originalStr = printInst->returnOriginalString();
                        size_t pos = 0;
                        while ((pos = originalStr.find("%d", pos)) != std::string::npos) {
                            originalStr.replace(pos, 2, "%ld");  // Replace "%d" with "%ld"
                            pos += 3;  // Move past the replaced substring
                        }
                        auto formatSize = printInst->returnFormatSize();
                        pp<<".PRINT_"<<printCounter<<":\n"
                        <<"    .asciz "<<originalStr<<"\n"
                        <<"    .size .PRINT_"<<printCounter<<", "<<formatSize<<"\n";
                        printCounter++;
                    }
                    if(auto* branchInst = dynamic_cast<llvm::Branch*>(inst.get())){
                        auto operandVec = branchInst->returnRegister();
                        if(operandVec[0] == nullptr){
                            auto trueLabel = branchInst->returnTrueLabel();
                            std::string armLabel = "." + trueLabel;
                            ss<<"    b "<<armLabel<<'\n';
                        }else {
                            // This is a conditional branch (if-else)
                            auto condReg = operandVec[0];
                            auto trueLabel = branchInst->returnTrueLabel();
                            auto falseLabel = branchInst->returnFalseLabel();

                            std::string armTrueLabel = "." + trueLabel;
                            std::string armFalseLabel = "." + falseLabel;

                            // Get the condition register
                            std::string condRegStr = condReg->toString();
                            if(activeRegisters.find(condRegStr) == activeRegisters.end()){
                                activeRegisters[condRegStr] = (int)activeRegisters.size();
                            }

                            ss << "    cmp " << condRegStr << ", #0\n";

                            // Branch to true label if not equal to 0, otherwise fall through to false path
                            ss << "    bne " << armTrueLabel << "\n";
                            ss << "    b " << armFalseLabel << "\n";
                        }
                    }
                    if(auto* returnInst = dynamic_cast<llvm::Return*>(inst.get())){
                        auto operandVec = returnInst->returnRegister();
                        if(operandVec[0]!= nullptr){
                            std::string reg = operandVec[0]->toString();
                            if(!std::isalpha(reg[0])){
                                reg = '#' + reg;
                            }
                            ss << "    mov x0, "<<reg<<'\n';
                        }
                        ss<< "    ldp x29, x30, [sp]\n"
                        << "    add sp, sp, #"<<spVal<<"\n"
                        << "    ret\n";
                    }
                    if(auto* callInst = dynamic_cast<llvm::Call*>(inst.get())){

                        for(auto& x : funcRegAllocations[funcName]){
                                ss<<"    str "<<x.first<<", [sp, #"<<(x.second+2)*8<<"]\n";
                        }
                        auto operandVec = callInst->returnRegister();

                        if(operandVec[0] != nullptr && activeRegisters.find(operandVec[0]->toString()) == activeRegisters.end()){
                            activeRegisters[operandVec[0]->toString()] = (int)activeRegisters.size();
                        }
                        auto argList = callInst->getArgList();
                        auto functionName = callInst->getFunctionName();
                        auto funcEntry = tables->getFunctions()->lookup(functionName);
                        auto parameters = funcEntry->parameters;
                        std::vector<std::string> llvmParameters;
                        llvmParameters.reserve(parameters.size());
                        for(auto& x : parameters){
                            llvmParameters.emplace_back("%" + x->name);
                        }
                        int j = 0;
                        for(auto& x: llvmParameters){
                            std::string arg = argList[j].second;
                            if(!std::isalpha(arg[0])) arg = '#' + arg;
                            ss<<"    mov "<<regAllocation[functionName][x]<<", "<<arg<<"\n";
                            j++;
                        }
                        ss<<"    bl "<<functionName<<"\n";
                        if(operandVec[0]!= nullptr){
                            ss<<"    mov "<<operandVec[0]->toString()<<", x0\n";
                        }
                        for(auto& x : funcRegAllocations[funcName]){
                            if(operandVec[0]!= nullptr && x.first == operandVec[0]->toString()) continue;
                            ss<<"    ldr "<<x.first<<", [sp, #"<<(x.second+2)*8<<"]\n";
                        }
                    }
                    if(auto* storeInst = dynamic_cast<llvm::Store*>(inst.get())){
                        auto operandVec = storeInst->returnRegister();
                        auto dest = operandVec[0];
                        auto value = operandVec[1];
                        if(auto* imm = dynamic_cast<llvm::LLVMImmediate*>(value.get())){
                            ss << "    adrp "<<globalRegAllocations[dest->toString()]<<", "<<dest->toString().substr(1)<<"\n";
                            ss << "    add "<<globalRegAllocations[dest->toString()]<<", "<<globalRegAllocations[dest->toString()]<<", :lo12:"<<dest->toString().substr(1)<<"\n";
                            ss << "    mov x9, #"<<imm->toString()<<"\n";
                            ss << "    str x9, ["<<globalRegAllocations[dest->toString()]<<"]\n";
                        }else{
                            ss << "    str "<<regAllocation[funcName][value->toString()]<<", ["<<globalRegAllocations[dest->toString()]<<"]\n";
                        }
                    }
                    if(auto* movInst = dynamic_cast<cfg::MovInstruction*>(inst.get())){
                        ss << "    " <<movInst->toString()<<"\n";
                    }
                    if(auto* unaryInst = dynamic_cast<llvm::UnaryOp*>(inst.get())){
                        auto operandVec = unaryInst->returnRegister();
                        auto dest = operandVec[0];
                        auto operand = operandVec[1];

                        if(activeRegisters.find(dest->toString()) == activeRegisters.end()){
                            activeRegisters[dest->toString()] = (int)activeRegisters.size();
                        }

                        std::string operandStr = operand->toString();
                        bool operandIsImm = !std::isalpha(operandStr[0]);

                        if(operandIsImm) {
                            ss << "    mov x19, " << operandStr << "\n";
                            ss << "    eor " << dest->toString() << ", x16, #1\n";
                        } else {
                            if(activeRegisters.find(operand->toString()) == activeRegisters.end()){
                                activeRegisters[operand->toString()] = (int)activeRegisters.size();
                            }
                            ss << "    eor " << dest->toString() << ", " << operand->toString() << ", #1\n";
                        }
                    }
                    if(auto* truncInst = dynamic_cast<llvm::Trunc*>(inst.get())){
                        auto operandVec = truncInst->returnRegister();
                        auto dest = operandVec[0];
                        auto source = operandVec[1];
                        if(activeRegisters.find(dest->toString()) == activeRegisters.end()){
                            activeRegisters[dest->toString()] = (int)activeRegisters.size();
                        }
                        if(activeRegisters.find(source->toString()) == activeRegisters.end()){
                            activeRegisters[source->toString()] = (int)activeRegisters.size();
                        }
                        ss<<"    and "<<dest->toString()<<", "<<source->toString()<<", #1\n";
                    }
                }
            }
            ss << "    .size "<<funcName<<", (. -"<<funcName<<")\n";
        }
        ss<<".READ:\n"
        << "    .asciz \"%ld\"\n"
        << "    .size .READ, 4\n";
        ss<<pp.str();
        return ss.str();
    }

    void OutOfSSA::printUpdatedLLVMIR() {
        std::stringstream ss;

        // Write global declarations
        for (const auto& globalDecl : globalDeclarations) {
            ss << globalDecl << "\n";
        }
        ss << "\n";
        ss<<"@.read_scratch = common global i64 0\n";
        // Write function definitions
        for (auto& [funcName, blocks] : _funcDefsReg) {
            if (blocks.empty()) {
                std::cerr << "[ERROR] Function '" << funcName << "' has no blocks.\n";
                continue;
            }
            auto funcEntry = tables->functions->lookup(funcName);
            auto returnTypeIt = returnValue.find(funcName);
            std::string returnType = (returnTypeIt != returnValue.end()) ? returnTypeIt->second : "void";
            ss << "\ndefine " << returnType << " @" << funcName << "(";

            // Add parameters if they exist
            if (funcEntry && !funcEntry->parameters.empty()) {
                for (size_t i = 0; i < funcEntry->parameters.size(); ++i) {
                    auto& param = funcEntry->parameters[i];
                    std::string paramType = llvm::LLVMProgram::typeToLLVMType(param->type);
                    ss << paramType << " %" << param->name;

                    // Add comma if not the last parameter
                    if (i < funcEntry->parameters.size() - 1) {
                        ss << ", ";
                    }
                }
            }

            // Close parameter list and begin function body
            ss << ") {\n";
            // Print function body (blocks)
            for (const auto& block : blocks) {
                if (!block) {
                    std::cerr << "[ERROR] Null block found in function " << funcName << "\n";
                    continue;
                }

                // Print block label
                ss << block->toString() << "\n";
            }

            ss << "}\n";  // Close function definition
        }
        ss<<"declare i8* @malloc(i32)\n"
            "declare i32 @scanf(i8*, ...)\n"
            "declare i32 @printf(i8*, ...)\n"
            "declare void @free(i8*)\n";

        ss<<R"(@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1)";
        std::cout<<ss.str()<<std::endl;
    }

    void OutOfSSA::printRegisterAllocation() {
        std::cout << "=== Register Allocation ===" << std::endl;

        for(const auto& x : globalRegAllocations){
            std::cout<<x.first<<"    "<<x.second<<std::endl;
        }

        for (const auto& [functionName, intervals] : funcToLiveInterval) {
            std::cout << "\nFunction: " << functionName << std::endl;
            std::cout << "-----------------------------" << std::endl;
            std::cout << std::left << std::setw(20) << "Variable"
                      << std::setw(10) << "Start"
                      << std::setw(10) << "End"
                      << std::setw(10) << "Register Allocation" << std::endl;
            std::cout << "-----------------------------" << std::endl;
            std::vector<std::tuple<std::string, int, int, int>> sortableIntervals;
            for (size_t i = 0; i < intervals.size(); i++) {
                auto [varName, start, end] = intervals[i];
                sortableIntervals.emplace_back(varName, start, end, i);
            }

            // Sort intervals by start point
            std::sort(sortableIntervals.begin(), sortableIntervals.end(),
                      [](const auto& a, const auto& b) {
                          return std::get<1>(a) < std::get<1>(b);
                      });
            for (const auto& interval : sortableIntervals) {
                const auto& [variableName, start, end, index] = interval;
                std::cout << std::left << std::setw(20) << variableName
                          << std::setw(10) << start
                          << std::setw(10) << end << std::setw(10)
                          << regAllocation[functionName][variableName] << std::endl;
            }
        }

        std::cout << "\n=== END Register Allocation ===" << std::endl;
    }
}