// LLVM.h
#ifndef LLVM_H
#define LLVM_H

#include "../cfg/CFG.h"
#include "../types/types.h"
#include "../symboltable/symboltable.h"
#include <string>
#include <map>
#include <memory>
#include <utility>

namespace llvm {

// Base LLVM Operand class that inherits from cfg::Operand
    class LLVMOperand : public cfg::Operand {
    public:
        virtual ~LLVMOperand() = default;
        virtual std::string toString() const override = 0;
        virtual std::shared_ptr<types::Type> getType() const = 0;
        virtual bool isAddress() const {
            return false;
        }
        virtual void setName(std::string newName) = 0;
    };
    class LLVMVariableOperand : public llvm::LLVMOperand {
    private:
        std::string name;
        std::shared_ptr<types::Type> type;

    public:
        LLVMVariableOperand(std::string name, std::shared_ptr<types::Type> type)
                : name(std::move(name)), type(std::move(type)) {}

        std::string toString() const override {
            return name;
        }

        void setName(std::string newName) override{
            name = newName;
        }

        std::shared_ptr<types::Type> getType() const override {
            return type;
        }
        bool isAddress() const override{
            return false;
        }
    };

    class LLVMAddressOperand : public LLVMOperand {
    private:
        std::string address; // The LLVM IR register containing the address
        std::shared_ptr<types::Type> pointeeType; // The type the address points to

    public:
        LLVMAddressOperand(const std::string& address, std::shared_ptr<types::Type> pointeeType)
                : address(address), pointeeType(pointeeType) {}

        std::string toString() const override {
            return address;
        }
        void setName(std::string newName) override{
            address = newName;
        }
        std::shared_ptr<types::Type> getType() const override {
            // Create a pointer type that points to the pointee type
            return types::PointerTy::getPointerType(pointeeType);
        }

        std::shared_ptr<types::Type> getPointeeType() const {
            return pointeeType;
        }

        bool isAddress() const override {
            return true;
        }
    };

    // LLVM Register
    class LLVMRegister : public llvm::LLVMOperand {
    private:
        std::string registerName;  // `%r1`, `%r2`, etc.
        std::shared_ptr<types::Type> type;  // LLVM type

    public:
        LLVMRegister(std::string registerName, std::shared_ptr<types::Type> type)
                : registerName(std::move(registerName)), type(std::move(type)) {}

        void setName(std::string newName) override{
            registerName = newName;
        }
        [[nodiscard]] std::string toString() const override { return registerName; }

        [[nodiscard]] std::shared_ptr<types::Type> getType() const override { return type; }
    };


    // LLVM Immediate Value
    class LLVMImmediate : public LLVMOperand {
    private:
        int value;
        std::shared_ptr<types::Type> type;
    public:
        LLVMImmediate(int value, std::shared_ptr<types::Type> type)
                : value(value), type(std::move(type)) {}
        void setName(std::string newName) override{
            return;
        }
        std::string toString() const override;
        [[nodiscard]] std::shared_ptr<types::Type> getType() const override { return type; }
        [[nodiscard]] int getValue() const { return value; }
    };

    class LLVMBooleanImmediate : public llvm::LLVMOperand {
    private:
        bool value;

    public:
        explicit LLVMBooleanImmediate(bool value) : value(value) {}

        std::string toString() const override {
            return std::to_string(value ? 1 : 0);
        }
        void setName(std::string newName) override{
            return;
        }

        [[nodiscard]] std::shared_ptr<types::Type> getType() const override {
            return types::BoolTy::getInstance();
        }

        [[nodiscard]] bool getValue() const { return value; }
    };

// LLVM Nil Pointer Operand
    class LLVMNilOperand : public LLVMOperand {
    public:
        explicit LLVMNilOperand(std::shared_ptr<types::Type> type) : type(std::move(type)) {}

        std::string toString() const override {
            return "null";
        }
        void setName(std::string newName) override{
            return;
        }
        [[nodiscard]] std::shared_ptr<types::Type> getType() const override {
            return type;
        }

        bool isAddress() const override {
            return true;
        }

    private:
        std::shared_ptr<types::Type> type;  // Type of the nil pointer (should be a pointer type)
    };


// Base LLVM Instruction class
    class LLVMInstruction : public cfg::Instruction {
    public:
        virtual ~LLVMInstruction() = default;
        virtual std::string toString() const override = 0;
        virtual std::vector<std::shared_ptr<LLVMOperand>> returnRegister()  = 0;
    };

// Binary Operation Instruction
    class BinOp : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> dest;
        std::string binTy;  // Operation type (add, sub, mul, etc.)
        std::shared_ptr<types::Type> type;
        std::shared_ptr<LLVMOperand> op1;
        std::shared_ptr<LLVMOperand> op2;

    public:
        BinOp(std::shared_ptr<LLVMRegister> dest,
              std::string  binTy,
              std::shared_ptr<types::Type> type,
              std::shared_ptr<LLVMOperand> op1,
              std::shared_ptr<LLVMOperand> op2)
                : dest(std::move(dest)), binTy(std::move(binTy)), type(std::move(type)), op1(std::move(op1)), op2(std::move(op2)) {}

        std::string toString() const override;
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest, op1, op2};
        }

        std::string returnBinTy(){
            return binTy;
        }

        bool isTerminator() const override{
            return false;
        }
    };

// Load Instruction
    class Load : public LLVMInstruction {
    private:
        std::shared_ptr<types::Type> desTy;
        std::shared_ptr<types::Type> pTy;
        std::shared_ptr<LLVMRegister> dest;
        std::shared_ptr<LLVMRegister> op;

    public:
        Load(std::shared_ptr<types::Type> desTy,
             std::shared_ptr<types::Type> pTy,
             std::shared_ptr<LLVMRegister> dest,
             std::shared_ptr<LLVMRegister> op)
                : desTy(desTy), pTy(pTy), dest(dest), op(op) {}

        std::string toString() const override;
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest, op};
        }
        bool isTerminator() const override{
            return false;
        }
    };

// Allocation Instruction
    class Alloc : public LLVMInstruction {
    private:
        std::shared_ptr<types::Type> type;  // Type of the allocated variable
        std::shared_ptr<LLVMRegister> dest; // Destination register where the allocated pointer is stored

    public:
        Alloc(std::shared_ptr<types::Type> type, std::shared_ptr<LLVMRegister> dest)
            : type(std::move(type)), dest(std::move(dest)) {}

        std::string toString() const override;
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest};
        }
        bool isTerminator() const override {
            return false;
        }
    };

// Store Instruction
    class Store : public LLVMInstruction {
    private:
        std::shared_ptr<types::Type> type; // Type of the value being stored
        std::shared_ptr<LLVMOperand> value; // Value to store
        std::shared_ptr<LLVMRegister> dest; // Destination register (memory location)

    public:
        Store(std::shared_ptr<types::Type> type,
            std::shared_ptr<LLVMOperand> value,
            std::shared_ptr<LLVMRegister> dest)
            : type(std::move(type)), value(std::move(value)), dest(std::move(dest)) {}
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest, value};
        }
        std::string toString() const override;

        bool isTerminator() const override {
            return false;
        }
    };
// Branch Instruction
    class Branch : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMOperand> condition; // Condition (for conditional branch) or nullptr for unconditional
        std::string trueLabel;  // Target label for true (or the only label for an unconditional branch)
        std::string falseLabel; // Target label for false (only for conditional branches)

    public:
        // Constructor for conditional branch
        Branch(std::shared_ptr<LLVMOperand> condition, std::string trueLabel, std::string falseLabel)
            : condition(std::move(condition)), trueLabel(std::move(trueLabel)), falseLabel(std::move(falseLabel)) {}

        // Constructor for unconditional branch
        explicit Branch(std::string targetLabel)
            : condition(nullptr), trueLabel(std::move(targetLabel)), falseLabel("") {}

        std::string toString() const override {
            if (condition) {
                return "br i1 " + condition->toString() + ", label %" + trueLabel + ", label %" + falseLabel;
            } else {
                return "br label %" + trueLabel;
            }
        }
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {condition};
        }

        std::string returnTrueLabel(){
            return trueLabel;
        }
        std::string returnFalseLabel(){
            return falseLabel;
        }

        bool isTerminator() const override {
            return true;
        }
    };
// GetElementPtr (GEP) Instruction
    class GetElementPtr : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> dest; // Destination register for the result
        std::shared_ptr<types::Type> baseType; // The base type (struct or array type)
        std::shared_ptr<LLVMRegister> basePtr; // The pointer operand (source)
        std::vector<int> indices; // List of indices (for struct fields or array access)
        int formatSize;
        std::string formatID;
        std::string printDest;
        bool inbounds;
    public:
        GetElementPtr(std::shared_ptr<LLVMRegister> dest,
                    std::shared_ptr<types::Type> baseType,
                    std::shared_ptr<LLVMRegister> basePtr,
                    std::vector<int> indices,
                    bool inbounds = false)
            : dest(std::move(dest)), baseType(std::move(baseType)), basePtr(std::move(basePtr)), indices(std::move(indices)), inbounds(inbounds) {}
        GetElementPtr(std::string printDest,
                      int formatSize,
                      std::string formatID,
                      bool inbounds = true) : printDest(printDest), formatSize(formatSize), formatID(formatID), inbounds(inbounds){}
        std::string toString() const override;
        bool isTerminator() const override {
            return false;
        }
        std::shared_ptr<LLVMRegister> getDest(){
            return dest;
        }

        std::shared_ptr<LLVMRegister> getBase(){
            return basePtr;
        }

        std::shared_ptr<types::Type> getBaseType(){
            return baseType;
        }

        std::vector<int> getIndices(){
            return indices;
        }


        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest};
        }
    };
// Call Instruction
    class Call : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> dest;  // Destination register (if function returns a value), nullptr if void
        std::string functionName;  // Function name being called
        std::shared_ptr<types::Type> returnType;  // Return type of the function
        std::vector<std::pair<std::string, std::string>> arglist;  // Arguments to the function (type, value pairs)

    public:
        // Constructor for function calls with return values
        Call(std::shared_ptr<LLVMRegister> dest,
             std::string functionName,
             std::shared_ptr<types::Type> returnType,
             std::vector<std::pair<std::string, std::string>> arglist)
                : dest(std::move(dest)), functionName(std::move(functionName)), returnType(std::move(returnType)), arglist(std::move(arglist)) {}

        // Constructor for void function calls (no return value)
        Call(std::string functionName,
             std::shared_ptr<types::Type> returnType,
             std::vector<std::pair<std::string, std::string>> arglist)
                : dest(nullptr), functionName(std::move(functionName)), returnType(std::move(returnType)), arglist(std::move(arglist)) {}

        std::string toString() const override;
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest};
        }
        bool isTerminator() const override {
            return false;
        }

        // Add these methods to your Call class
        std::string getFunctionName() const {
            return functionName;
        }

        const std::vector<std::pair<std::string, std::string>>& getArgList() const {
            return arglist;
        }

        void updateArgList(std::vector<std::pair<std::string, std::string>> newArgList){
            arglist = newArgList;
        }

        std::shared_ptr<types::Type> getReturnType() const {
            return returnType;
        }
    };

// Scan Instruction (for scanf calls)
    class Scan : public LLVMInstruction {
    private:
        std::string varName; // The variable name being scanned

    public:
        explicit Scan(std::string varName) : varName(std::move(varName)) {}

        std::string toString() const override {
            std::stringstream scanInst;
            scanInst << "call i8 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.read, i32 0, i32 0), i64* "
                    << varName << ")";
            return scanInst.str();
        }
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {};
        }
        std::string getVarName() {
            return varName;
        }
        bool isTerminator() const override {
            return false;
        }
    };
// Return Instruction
    class Return : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> returnValue; // The value to return, nullptr if void

    public:
        // Constructor for return instructions with a value
        explicit Return(std::shared_ptr<LLVMRegister> returnValue)
            : returnValue(std::move(returnValue)) {}

        // Constructor for void return
        Return() : returnValue(nullptr) {}

        std::string toString() const override;

        bool isTerminator() const override {
            return true;
        }
        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {returnValue};
        }
    };

// Unary Operation Instruction
    class UnaryOp : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> dest; // Destination register for the result
        std::string opType;  // Operation type (e.g., "xor", "sub")
        std::shared_ptr<types::Type> type; // Type of the operand
        std::shared_ptr<LLVMOperand> operand; // Operand for the unary operation

    public:
        UnaryOp(std::shared_ptr<LLVMRegister> dest,
                std::string opType,
                std::shared_ptr<types::Type> type,
                std::shared_ptr<LLVMOperand> operand)
            : dest(std::move(dest)), opType(std::move(opType)), type(std::move(type)), operand(std::move(operand)) {}

        std::string toString() const override;

        bool isTerminator() const override {
            return false;
        }

        std::string returnOpType(){
            return opType;
        }

        std::shared_ptr<types::Type> returnType(){
            return type;
        }

        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest, operand};
        }
    };
// Truncate (Trunc) Instruction
    class Trunc : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> dest; // Destination register
        std::shared_ptr<LLVMOperand> source; // Source operand
        std::shared_ptr<types::Type> fromType; // Source type
        std::shared_ptr<types::Type> toType; // Target type

    public:
        Trunc(std::shared_ptr<LLVMRegister> dest,
            std::shared_ptr<LLVMOperand> source,
            std::shared_ptr<types::Type> fromType,
            std::shared_ptr<types::Type> toType)
            : dest(std::move(dest)), source(std::move(source)), fromType(std::move(fromType)), toType(std::move(toType)) {}

        std::string toString() const override;

        bool isTerminator() const override {
            return false;
        }

        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest, source};
        }

        std::shared_ptr<types::Type> returnType(){
            return fromType;
        }
    };

// Malloc Instruction (for dynamic memory allocation)
    class Malloc : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> dest;  // Destination register for allocated memory (i8*)
        std::shared_ptr<LLVMRegister> bitcastDest;  // Destination register after bitcast (struct pointer)
        int size;  // Size of the allocated memory
        std::shared_ptr<types::Type> structType;  // The target type after bitcast

    public:
        Malloc(std::shared_ptr<LLVMRegister> dest,
            std::shared_ptr<LLVMRegister> bitcastDest,
            int size,
            std::shared_ptr<types::Type> structType)
            : dest(std::move(dest)), bitcastDest(std::move(bitcastDest)), size(size), structType(std::move(structType)) {}

        std::string toString() const override;

        bool isTerminator() const override {
            return false;
        }

        std::shared_ptr<LLVMRegister> getDest(){
            return dest;
        }

        std::shared_ptr<LLVMRegister> getBitCastDest(){
            return bitcastDest;
        }

        int getSize(){
            return size;
        }

        std::shared_ptr<types::Type> getStructType(){
            return structType;
        }

        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {dest, bitcastDest};
        }
    };
// Free Instruction (for memory deallocation)
    class Free : public LLVMInstruction {
    private:
        std::shared_ptr<LLVMRegister> bitcastDest; // Destination register for bitcast (i8*)
        std::shared_ptr<LLVMOperand> source; // Source operand (struct pointer)

    public:
        Free(std::shared_ptr<LLVMRegister> bitcastDest,
            std::shared_ptr<LLVMOperand> source)
            : bitcastDest(std::move(bitcastDest)), source(std::move(source)) {}

        std::string toString() const override;

        std::shared_ptr<LLVMRegister> getBitCastDest(){
            return bitcastDest;
        }

        std::shared_ptr<LLVMOperand> getSource(){
            return source;
        }

        bool isTerminator() const override {
            return false;
        }



        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override{
            return {bitcastDest};
        }
    };

    class Print : public LLVMInstruction {
    private:
        std::string formatID;
        int formatSize;
        std::string originalString;
        std::vector<std::shared_ptr<LLVMOperand>> argOperands;
        std::string fullInstruction; // Stores the complete instruction for toString()

    public:
        Print(std::string formatID, int formatSize,
              std::vector<std::shared_ptr<LLVMOperand>> argOperands, std::string originalString)
                : formatID(std::move(formatID)),
                  formatSize(formatSize),
                  argOperands(std::move(argOperands)), originalString(originalString) {

            // Build the instruction string when the object is created
            buildInstructionString();
        }

        void buildInstructionString();

        std::string toString() const override {
            return fullInstruction;
        }

        std::string returnOriginalString(){
            return originalString;
        }

        int returnFormatSize(){
            return formatSize;
        }

        std::string returnFormatID(){
            return formatID;
        }

        std::vector<std::shared_ptr<LLVMOperand>> returnRegister() override  {
            return argOperands;
        }

        bool isTerminator() const override {
            return false;
        }
    };

// LLVM Program class
    class LLVMProgram {
    private:
        bool hasScanStatement = false;

        std::string sourceName;
        std::string targetTriple;
        std::shared_ptr<symboltable::SymbolTables> tables;
        int labelCounter = 0;
        static int registerCounter;
        static int variableCounter;
    public:
        void sstatement(){ hasScanStatement = true;}
        int getNextLabel(){
            return labelCounter++;
        }

        static int getNextRegister(){
            return registerCounter++;
        }

        static int getVariableCounter(){
            return variableCounter;
        }
        static void updateVariableCounter(){
            variableCounter++;
        }
        std::vector<std::string> globalDeclarations; // Stores global declarations
        static std::map<std::string, std::vector<std::shared_ptr<cfg::Block>>> funcDefs;
        static std::map<std::string, std::vector<std::shared_ptr<cfg::Block>>> funcDefsReg;
        static std::map<std::string, std::shared_ptr<cfg::Block>> cfg_structure;
        static std::unordered_map<std::string, std::shared_ptr<cfg::Block>> labelToBlockMap;
        std::unordered_map<std::string, std::string> returnValue;

        void SetTargetTriple(std::string& s){
            targetTriple = s;
        }

        LLVMProgram(const std::string& source,
                    std::shared_ptr<symboltable::SymbolTables> symTables)
                : sourceName(source),
                  tables(symTables) {}

        void addGlobalDeclaration(const std::string& declaration) {
            globalDeclarations.push_back(declaration);
        }
        int getTypeSize(const std::string& llvmType);
        std::string toString() const;
        std::string toStringReg() const;
        void toRegister();
        auto getTables(){return tables;}
        static std::string typeToLLVMType(const std::shared_ptr<types::Type>& ty);
    };

} // namespace llvm

#endif // LLVM_H