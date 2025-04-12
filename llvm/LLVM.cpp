// LLVM.cpp
#include "LLVM.h"
#include <string>

// In LLVM.cpp
std::map<std::string, std::vector<std::shared_ptr<cfg::Block>>> llvm::LLVMProgram::funcDefs;
std::map<std::string, std::vector<std::shared_ptr<cfg::Block>>> llvm::LLVMProgram::funcDefsReg;
int llvm::LLVMProgram::variableCounter = 0;
int llvm::LLVMProgram::registerCounter = 0;
std::map<std::string, std::shared_ptr<cfg::Block>> llvm::LLVMProgram::cfg_structure;
std::unordered_map<std::string, std::shared_ptr<cfg::Block>> llvm::LLVMProgram::labelToBlockMap;
namespace llvm {
// In LLVMProgram.cpp
    std::string LLVMProgram::typeToLLVMType(const std::shared_ptr<types::Type>& ty) {
        if (std::dynamic_pointer_cast<types::IntTy>(ty)) {
            return "i64";
        }
        if (std::dynamic_pointer_cast<types::BoolTy>(ty)) {
            return "i64";
        }
        if (auto ptrTy = std::dynamic_pointer_cast<types::PointerTy>(ty)) {
            return typeToLLVMType(ptrTy->getBaseType()) + "*";
        }
        if (auto structTy = std::dynamic_pointer_cast<types::StructTy>(ty)) {
            // LLVM struct type format: %struct.<name>
            return "%struct." + structTy->getName();
        }
        if (std::dynamic_pointer_cast<types::VoidTy>(ty)) {
            return "void";
        }
        // Default case
        return "void";
    }

    int LLVMProgram::getTypeSize(const std::string& llvmType) {
        // Primitive types
        if (llvmType == "i1" || llvmType == "i8" || llvmType == "i16" || llvmType == "i32" || llvmType == "i64" ||
            llvmType == "float" || llvmType == "double") {
            return 8;
        }

        // Pointer size (assume 64-bit architecture)
        if (llvmType.find("*") != std::string::npos) return 8;

        // Struct type size computation
        if (llvmType.rfind("%struct.", 0) == 0) {  // Struct type
            std::string structName = llvmType.substr(8);  // Remove "%struct."
            auto structType = tables->types->lookup(structName);

            if (!structType) {
                std::cerr << "[ERROR] getTypeSize: Unknown struct type '" << structName << "'\n";
                return 0;
            }

            auto structDef = std::dynamic_pointer_cast<types::StructTy>(structType);
            if (!structDef) {
                std::cerr << "[ERROR] getTypeSize: Failed to resolve struct '" << structName << "'\n";
                return 0;
            }

            int fieldCount = structDef->getFields().size();
            return fieldCount * 8;
        }

        std::cerr << "[ERROR] getTypeSize: Unknown type '" << llvmType << "'\n";
        return 8;
    }


    std::string LLVMImmediate::toString() const {
        // Integer immediate values
        return std::to_string(value);
    }

    std::string BinOp::toString() const {
        std::stringstream ss;
        // Format: <result> = <operation> <type> <op1>, <op2>
        ss << dest->toString() << " = " << binTy << " "
           << LLVMProgram::typeToLLVMType(type) << " "
           << op1->toString() << ", " << op2->toString();
        return ss.str();
    }

    std::string Load::toString() const {
        std::stringstream ss;
        // Format: <result> = load <type>, <type>* <pointer>
        ss << dest->toString() << " = load "
           << LLVMProgram::typeToLLVMType(desTy) << ", "
           << LLVMProgram::typeToLLVMType(pTy) << "* "
           << op->toString();
        return ss.str();
    }

    std::string Alloc::toString() const{
        return dest->toString() + " = alloca " + LLVMProgram::typeToLLVMType(type);
    }

    std::string Store::toString() const{
        return "store " + llvm::LLVMProgram::typeToLLVMType(type) + " " +
               value->toString() + ", " + llvm::LLVMProgram::typeToLLVMType(type) +
               "* " + dest->toString();
    }

    std::string GetElementPtr::toString() const{
        std::string result;
        if(!inbounds){
            result = dest->toString() + " = getelementptr " +
                     llvm::LLVMProgram::typeToLLVMType(baseType) + ", " +
                     llvm::LLVMProgram::typeToLLVMType(baseType) + "* " + basePtr->toString();
            for (int index : indices) {
                result += ", i32 " + std::to_string(index);
            }
        }else{
            result = printDest + " = getelementptr inbounds [" + std::to_string(formatSize) + " x i8], [" +
                     std::to_string(formatSize) + " x i8]* " + formatID + ", i32 0, i32 0";
        }
        return result;
    }

    std::string Call::toString() const{
        std::string result;
        if (dest) {
            result += dest->toString() + " = ";
        }

        // Start with the base of the call instruction
        result += "call " + llvm::LLVMProgram::typeToLLVMType(returnType) + " @" + functionName + "(";

        // Format the argument list from the vector of pairs
        for (size_t i = 0; i < arglist.size(); ++i) {
            if (i > 0) {
                result += ", ";
            }
            result += arglist[i].first + " " + arglist[i].second;
        }

        result += ")";
        return result;
    }

    std::string Return::toString() const {
        if (returnValue) {
            return "ret " + llvm::LLVMProgram::typeToLLVMType(returnValue->getType()) + " " + returnValue->toString();
        } else {
            return "ret void";
        }
    }

    std::string UnaryOp::toString() const{
        return dest->toString() + " = " + opType + " " + llvm::LLVMProgram::typeToLLVMType(type) + " " + operand->toString() + ", 1";
    }

    std::string Trunc::toString() const {
        return dest->toString() + " = trunc " +
               llvm::LLVMProgram::typeToLLVMType(fromType) + " " + source->toString() +
               " to i1";
    }

    std::string Malloc::toString() const {
        std::stringstream ss;
        ss << dest->toString() << " = call i8* @malloc(i32 " << size << ")\n  ";
        ss << bitcastDest->toString() << " = bitcast i8* " << dest->toString()
           << " to " << llvm::LLVMProgram::typeToLLVMType(structType) << "*";
        return ss.str();
    }

    std::string Free::toString() const {
        std::stringstream ss;
        ss << bitcastDest->toString() << " = bitcast "
           << llvm::LLVMProgram::typeToLLVMType(source->getType()) << " "
           << source->toString() << " to i8*\n  ";
        ss << "call void @free(i8* " << bitcastDest->toString() << ")";
        return ss.str();
    }

    void Print::buildInstructionString()  {
        std::stringstream printfSS;
        printfSS << "call i8 (i8*, ...) @printf(i8* getelementptr inbounds ("
                 << "[" << formatSize << " x i8], [" << formatSize << " x i8]* " << formatID
                 << ", i32 0, i32 0)";

        for (const auto& operand : argOperands) {
            printfSS << ", " << LLVMProgram::typeToLLVMType(operand->getType())
                     << " " << operand->toString();
        }

        printfSS << ")";
        fullInstruction = printfSS.str();
    }

    void checkCFG(){
        for(auto [funcName, blocks] : llvm::LLVMProgram::funcDefs){
            auto copy = cfg::deepCopyCFG(blocks[0], llvm::LLVMProgram::labelToBlockMap);
            LLVMProgram::cfg_structure[funcName] = copy;
        }
    }

    std::string LLVMProgram::toString() const {

        std::stringstream ss;

        // Write source filename
        ss << "source_filename = \"" << sourceName << "\"\n";

        // Write target triple
        ss << "target triple = \"" << targetTriple << "\"\n\n";

        // Write global declarations
        for (const auto& globalDecl : globalDeclarations) {
            ss << globalDecl << "\n";
        }
        ss << "\n";

        // Write function definitions
        for (auto& [funcName, blocks] : funcDefs) {
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
        if(hasScanStatement){
            ss<<R"(@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1)";
        }
        return ss.str();
    }

    std::string LLVMProgram::toStringReg() const {
        std::stringstream ss;

        // Write source filename
        ss << "source_filename = \"" << sourceName << "\"\n";

        // Write target triple
        ss << "target triple = \"" << targetTriple << "\"\n\n";

        // Write global declarations
        for (const auto& globalDecl : globalDeclarations) {
            ss << globalDecl << "\n";
        }
        ss << "\n";
        ss<<"@.read_scratch = common global i64 0\n";
        // Write function definitions
        for (auto& [funcName, blocks] : funcDefsReg) {
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
        if(hasScanStatement){
            ss<<R"(@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1)";
        }
        return ss.str();
    }

    void printDefsMap(const std::unordered_map<std::string, std::string>& defs) {
        std::cout << "=== Current definitions map ===" << std::endl;
        if (defs.empty()) {
            std::cout << "  (empty)" << std::endl;
        } else {
            for (const auto& [key, value] : defs) {
                std::cout << "  " << key << " -> " << value << std::endl;
            }
        }
        std::cout << "=============================" << std::endl;
    }

    std::string resolveDefinition(const std::string& reg, const std::unordered_map<std::string, std::string>& defs) {
        if (defs.find(reg) == defs.end()) {
            return reg; // Not in the map, return as is
        }

        std::string value = defs.at(reg);
        if (defs.find(value) == defs.end()) {
            return value; // Direct mapping, no further resolution needed
        }

        // Recursively resolve until we find a value that isn't mapped further
        return resolveDefinition(value, defs);
    }


    void helper(std::unordered_map<std::string, std::string> defs, std::shared_ptr<cfg::Block> cur, std::unordered_map<std::string, std::string> types, std::string prev_label){
        auto newBlock = llvm::LLVMProgram::labelToBlockMap[cur->label];
        if(cur->predecessors.size() > 1) {
            int current_counter = llvm::LLVMProgram::getVariableCounter();
            for (const auto& pair: types) {
                std::string variable = pair.first;
                std::string llvmType = pair.second;
                auto phiIt = newBlock->phiInstructions.find(variable);
                if (phiIt == newBlock->phiInstructions.end()) {
                    // Create a new phi instruction
                    std::string updatedVariable = variable + "_" + std::to_string(current_counter);
                    auto phiInstruction = std::make_unique<cfg::PhiInstruction>(updatedVariable, llvmType);

                    phiInstruction->addPair(resolveDefinition( defs[variable], defs), "%" + prev_label);

                    cfg::PhiInstruction* phiPtr = phiInstruction.get();
                    newBlock->phiInstructions[variable] = phiPtr;

                    newBlock->addInstruction(std::move(phiInstruction));
                    defs[variable] = updatedVariable;
                } else {
                    phiIt->second->addPair(resolveDefinition( defs[variable], defs), "%" + prev_label);
                }
            }
            llvm::LLVMProgram::updateVariableCounter();
        }
        ++newBlock->visited;
        if(newBlock->visited > 1 && !cur->isStart) return;
        for(const auto& inst : cur->instructions){
            if(auto* allocInst = dynamic_cast<Alloc*>(inst.get())){
                auto regVec = allocInst->returnRegister();
                auto destReg = regVec[0];
                auto type = destReg->getType();
                if(types::isIntType(type) || types::isBoolTy(type)){
                    defs[destReg->toString()] = "0";
                }else{
                    defs[destReg->toString()] = "null";
                }
                types[destReg->toString()] = LLVMProgram::typeToLLVMType(type);
            }
            if(auto* storeInst = dynamic_cast<Store*>(inst.get())){

                auto operandVec = storeInst->returnRegister();
                auto destReg = operandVec[0];
                auto value = operandVec[1];

                auto type = destReg->getType();
                if(defs.find(destReg->toString()) != defs.end()) {
                    defs[destReg->toString()] = value->toString();
                } else {
                    auto destRegCast = std::dynamic_pointer_cast<llvm::LLVMRegister>(destReg);

                    // Check if value's string representation exists in defs
                    std::shared_ptr<llvm::LLVMOperand> actualValue = value;
                    if(defs.find(value->toString()) != defs.end()) {
                        std::string newValueStr = defs[value->toString()];
                        if(auto varOp = std::dynamic_pointer_cast<llvm::LLVMVariableOperand>(value)) {
                            actualValue = std::make_shared<llvm::LLVMVariableOperand>(
                                    newValueStr,
                                    value->getType()
                            );
                        }
                        else if(auto addrOp = std::dynamic_pointer_cast<llvm::LLVMAddressOperand>(value)) {
                            auto pointeeType = addrOp->getPointeeType();
                            actualValue = std::make_shared<llvm::LLVMAddressOperand>(
                                    newValueStr,
                                    pointeeType
                            );
                        }
                    }
                    auto newStoreInst = std::make_unique<llvm::Store>(
                            type,
                            actualValue,
                            destRegCast
                    );
                    newBlock->addInstruction(std::move(newStoreInst));
                }
            }
            if(auto* loadInst = dynamic_cast<Load*>(inst.get())){
                auto operandVec = loadInst->returnRegister();
                auto destReg = operandVec[0];
                auto opReg = operandVec[1];

                auto type = destReg->getType();
                if(defs.find(opReg->toString())!=defs.end()){
                    defs[destReg->toString()] = defs[opReg->toString()];
                }else{
                    // Create a proper Load instruction instead of a RawInstruction
                    auto resolvedOp = resolveDefinition(opReg->toString(), defs);
                    auto newOpReg = std::make_shared<LLVMRegister>(resolvedOp, opReg->getType());
                    auto destRegCast = std::dynamic_pointer_cast<llvm::LLVMRegister>(destReg);

                    std::unique_ptr<cfg::Instruction> newLoadInst = std::make_unique<Load>(
                            type,                 // destination type
                            type,     // pointer type
                            destRegCast,              // destination register
                            newOpReg              // source register (resolved)
                    );

                    newBlock->addInstruction(std::move(newLoadInst));
                }
            }
            if(auto* binInst = dynamic_cast<BinOp*>(inst.get())){
                auto operandVec = binInst->returnRegister();
                auto destReg = std::dynamic_pointer_cast<LLVMRegister>(operandVec[0]);
                auto op1 = operandVec[1];
                auto op2 = operandVec[2];

                auto type = destReg->getType();

                // Use the recursive resolution function here
                std::string op1str = defs.find(op1->toString()) == defs.end() ? op1->toString() : defs[op1->toString()];
                std::string op2str = defs.find(op2->toString()) == defs.end() ? op2->toString() : defs[op2->toString()];

                std::string binTy = binInst->returnBinTy();
                std::shared_ptr<LLVMVariableOperand> op1Updated, op2Updated;
                op1Updated = std::make_shared<LLVMVariableOperand>(op1str, type);
                op2Updated = std::make_shared<LLVMVariableOperand>(op2str, type);
                auto binOp = std::make_unique<BinOp>(destReg, binTy, type, op1Updated, op2Updated);
                newBlock->addInstruction(std::move(binOp));
            }
            if(auto* printInst = dynamic_cast<Print*>(inst.get())){
                auto operandVec = printInst->returnRegister();
                int formatSize = printInst->returnFormatSize();
                std::string formatID = printInst->returnFormatID();
                std::string orginalString = printInst->returnOriginalString();
                std::vector<std::shared_ptr<LLVMOperand>> resolvedOperands;

                // Process each operand and resolve its definition if needed
                for (const auto& operand : operandVec) {

                    auto newOperand = std::make_shared<LLVMRegister>(
                    resolveDefinition(operand->toString(), defs),
                            operand->getType()
                    );
                    resolvedOperands.push_back(newOperand);

                }

                // Create a new Print instruction with the resolved operands
                std::unique_ptr<cfg::Instruction> newPrintInst =
                        std::make_unique<Print>(formatID, formatSize, resolvedOperands, orginalString);

                newBlock->addInstruction(std::move(newPrintInst));
            }
            if(auto* returnInst = dynamic_cast<Return*>(inst.get())){
                auto operandVec = returnInst->returnRegister();

                if(operandVec.empty() || operandVec[0] == nullptr){
                    // Create a void return instruction
                    std::unique_ptr<cfg::Instruction> newReturnInst =
                            std::make_unique<Return>();
                    newBlock->addInstruction(std::move(newReturnInst));
                } else {
                    auto destReg = operandVec[0];
                    auto type = destReg->getType();

                    // Resolve the definition for the return value
                    std::string resolvedName = resolveDefinition(destReg->toString(), defs);

                    // If the name was resolved to something different, create a new register
                    std::shared_ptr<LLVMRegister> resolvedReg;
                    if(resolvedName != destReg->toString()) {
                        resolvedReg = std::make_shared<LLVMRegister>(resolvedName, type);
                    } else {
                        resolvedReg = std::dynamic_pointer_cast<LLVMRegister>(destReg);
                    }

                    // Create a return instruction with the resolved register
                    std::unique_ptr<cfg::Instruction> newReturnInst =
                            std::make_unique<Return>(resolvedReg);
                    newBlock->addInstruction(std::move(newReturnInst));
                }
            }
            if(auto* branchInst = dynamic_cast<Branch*>(inst.get())){
                auto operandVec = branchInst->returnRegister();

                if(operandVec[0] == nullptr){
                    // Unconditional branch
                    auto trueLabel = branchInst->returnTrueLabel();

                    // Create a new unconditional branch instruction
                    std::unique_ptr<cfg::Instruction> newBranchInst =
                            std::make_unique<Branch>(trueLabel);

                    newBlock->addInstruction(std::move(newBranchInst));
                } else {
                    // Conditional branch
                    auto trueLabel = branchInst->returnTrueLabel();
                    auto falseLabel = branchInst->returnFalseLabel();
                    auto condition = operandVec[0];

                    // Resolve the condition register if needed
                    std::shared_ptr<LLVMOperand> resolvedCondition;
                    if (defs.find(condition->toString()) != defs.end()) {
                        // Create new condition with resolved name
                        if (auto condReg = std::dynamic_pointer_cast<LLVMRegister>(condition)) {
                            resolvedCondition = std::make_shared<LLVMRegister>(
                                    defs[condition->toString()],
                                    condReg->getType()
                            );
                        } else {
                            resolvedCondition = condition;
                        }
                    } else {
                        resolvedCondition = condition;
                    }

                    // Create a new conditional branch instruction
                    std::unique_ptr<cfg::Instruction> newBranchInst =
                            std::make_unique<Branch>(resolvedCondition, trueLabel, falseLabel);

                    newBlock->addInstruction(std::move(newBranchInst));
                }
            }
            if(auto* callInst = dynamic_cast<Call*>(inst.get())){
                auto operandVec = callInst->returnRegister();
                auto destReg = operandVec[0]; // This might be nullptr for void functions

                // Get the original function info
                std::string functionName = callInst->getFunctionName();
                auto returnType = callInst->getReturnType();

                // Create a new list of resolved arguments
                std::vector<std::pair<std::string, std::string>> resolvedArgList;
                const auto& argList = callInst->getArgList();

                for (const auto& arg : argList) {
                    std::string resolvedArg = resolveDefinition(arg.second, defs);
                    resolvedArgList.emplace_back(arg.first, resolvedArg);
                }

                // Create a new Call instruction
                std::unique_ptr<cfg::Instruction> newCallInst;
                if (destReg) {
                    // For non-void functions with a return value
                    newCallInst = std::make_unique<Call>(
                            std::dynamic_pointer_cast<LLVMRegister>(destReg),
                            functionName,
                            returnType,
                            resolvedArgList
                    );
                } else {
                    // For void functions without a return value
                    newCallInst = std::make_unique<Call>(
                            functionName,
                            returnType,
                            resolvedArgList
                    );
                }

                newBlock->addInstruction(std::move(newCallInst));
            }
            if(auto* scanInst = dynamic_cast<Scan*>(inst.get())){
                std::string varname = scanInst->getVarName();

                // Create a Scan instruction that reads into .read_scratch
                std::unique_ptr<cfg::Instruction> newScanInst =
                        std::make_unique<Scan>("@.read_scratch");
                newBlock->addInstruction(std::move(newScanInst));

                // Get next register number for the load operation
                int reg = llvm::LLVMProgram::getNextRegister();
                std::string destRegName = "%r" + std::to_string(reg);

                // Create destination register for the load
                auto type = types::IntTy::getInstance(); // Assuming i64 type
                auto destReg = std::make_shared<LLVMRegister>(destRegName, type);

                // Create source pointer register for the load
                auto srcPtr = std::make_shared<LLVMRegister>("@.read_scratch", type);

                // Create a Load instruction
                std::unique_ptr<cfg::Instruction> loadInst =
                        std::make_unique<Load>(type, type, destReg, srcPtr);
                newBlock->addInstruction(std::move(loadInst));

                // Update the definitions map
                defs[varname] = destRegName;
            }
            if(auto* truncInst = dynamic_cast<Trunc*>(inst.get())){
                auto operandVec = truncInst->returnRegister();
                auto destReg = std::dynamic_pointer_cast<LLVMRegister>(operandVec[0]);
                auto source = operandVec[1];

                // Get the types from the original instruction
                auto fromType = truncInst->returnType();
                auto toType = types::IntTy::getInstance(); // Based on your code, always truncating to i1

                // Resolve the source operand if needed
                std::shared_ptr<LLVMOperand> resolvedSource;
                if (defs.find(source->toString()) != defs.end()) {
                    if (auto srcReg = std::dynamic_pointer_cast<LLVMRegister>(source)) {
                        // Create a new register with the resolved name
                        resolvedSource = std::make_shared<LLVMRegister>(
                                defs[source->toString()],
                                srcReg->getType()
                        );
                    } else {
                        resolvedSource = source;
                    }
                } else {
                    resolvedSource = source;
                }

                // Create a new Trunc instruction
                std::unique_ptr<cfg::Instruction> newTruncInst =
                        std::make_unique<Trunc>(destReg, resolvedSource, fromType, toType);

                newBlock->addInstruction(std::move(newTruncInst));
            }
            if(auto* unaryInst = dynamic_cast<UnaryOp*>(inst.get())){
                auto operandVec = unaryInst->returnRegister();
                auto destReg = std::dynamic_pointer_cast<LLVMRegister>(operandVec[0]);
                auto operand = operandVec[1];

                // Get the operation type and data type from the original instruction
                std::string opType = unaryInst->returnOpType();
                auto type = unaryInst->returnType();

                // Resolve the operand if needed
                std::shared_ptr<LLVMOperand> resolvedOperand;
                std::string name = resolveDefinition(operand->toString(), defs);
                resolvedOperand = std::make_shared<LLVMRegister>(name, type);

                // Create a new UnaryOp instruction
                std::unique_ptr<cfg::Instruction> newUnaryInst =
                        std::make_unique<UnaryOp>(destReg, opType, type, resolvedOperand);

                newBlock->addInstruction(std::move(newUnaryInst));
            }
            if(auto* mallocInst = dynamic_cast<Malloc*>(inst.get())){
                auto newMallocInst = std::make_unique<Malloc>(
                        mallocInst->getDest(),
                        mallocInst->getBitCastDest(),
                        mallocInst->getSize(),
                        mallocInst->getStructType()
                );
                newBlock->addInstruction(std::move(newMallocInst));
            }
            if(auto* freeInst = dynamic_cast<Free*>(inst.get())){
                auto bitCastDest = freeInst->getBitCastDest();
                auto source = freeInst->getSource();
                std::shared_ptr<LLVMOperand> updatedSource;
                if(defs.find(source->toString())!=defs.end()){
                    auto type = source->getType();
                    std::string name = resolveDefinition(source->toString(), defs);
                    updatedSource = std::make_shared<LLVMVariableOperand>(name, type);
                }else{
                    updatedSource = source;
                }
                auto newFreeInst = std::make_unique<Free>(
                        bitCastDest,
                        updatedSource
                );
                newBlock->addInstruction(std::move(newFreeInst));
            }
            if(auto* gepInst = dynamic_cast<GetElementPtr*>(inst.get())){
                auto dest = gepInst->getDest();
                auto base = gepInst->getBase();
                auto type = gepInst->getBaseType();
                auto indices = gepInst->getIndices();

                std::shared_ptr<LLVMRegister> updatedBase;
                if(defs.find(base->toString())!=defs.end()){
                    auto ty = base->getType();
                    std::string name = resolveDefinition(base->toString(), defs);
                    updatedBase = std::make_shared<LLVMRegister>(name, ty);
                }else{
                    updatedBase = base;
                }
                auto newGEPInst = std::make_unique<GetElementPtr>(
                        dest,
                        type,
                        updatedBase,
                        indices
                );
                newBlock->addInstruction(std::move(newGEPInst));
            }
        }
        for(const auto& nextBlock : cur->successors){
            helper(defs, nextBlock, types, cur->label);
        }
    }

    void LLVMProgram::toRegister() {
        checkCFG();

        for(auto& [funcName, blocks] : funcDefs){

            std::unordered_map<std::string, std::string> defs;
            std::unordered_map<std::string, std::string> types;
            auto topSort = cfg::topologicalSort(cfg_structure[funcName]);
            llvm::LLVMProgram::funcDefsReg[funcName] = topSort;
            blocks[0]->isStart = true;
            helper(defs, blocks[0], types, "");
        }
    }


} // namespace llvm