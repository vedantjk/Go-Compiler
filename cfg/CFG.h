// CFG.h
#ifndef CFG_H
#define CFG_H

#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <memory>
#include <sstream>
#include <iostream>
#include <unordered_set>
namespace cfg {

// Forward declarations
    class Block;
    class Instruction;
    class Operand;

// Abstract base class for operands
    class Operand {
    public:
        virtual ~Operand() = default;
        virtual std::string toString() const = 0;
    };

// Abstract base class for instructions
    class Instruction {
    public:
        virtual ~Instruction() = default;
        virtual std::string toString() const = 0;
        virtual bool isTerminator() const = 0;
    };

    class RawInstruction : public Instruction{
        std::string name;
    public:
        explicit RawInstruction(std::string  ins) : name(std::move(ins)){}
        [[nodiscard]] std::string toString() const override { return name;}
        bool isTerminator() const override{
            return name.find("br ") == 0 || name.find("ret ") == 0;
        }
    };

    class PhiInstruction : public Instruction {
    public:
        std::string result;
        std::string type;
        std::vector<std::pair<std::string, std::string>> pairs; // {value, label}

        explicit PhiInstruction(std::string result, std::string type) : result(std::move(result)), type(std::move(type)) {}

        void addPair(const std::string& value, const std::string& label) {
            pairs.emplace_back(value, label);
        }

        [[nodiscard]] std::string returnResult(){
            return result;
        }

        std::vector<std::pair<std::string, std::string>> returnPairs(){
            return pairs;
        }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << result << " = phi " << type;

            for (size_t i = 0; i < pairs.size(); i++) {
                ss << " [ " << pairs[i].first << ", " << pairs[i].second << " ]";
                if (i != pairs.size() - 1) {
                    ss << ",";
                }
            }
            return ss.str();
        }

        bool isTerminator() const override {
            return false;
        }
    };

    class MovInstruction : public Instruction{
    public:
        std::string dest, source;
        explicit MovInstruction(std::string dest, std::string source) : dest(dest), source(source) {}
        [[nodiscard]] std::string toString() const override{
            return "mov " + dest + ", " + source;
        }
        bool isTerminator() const override{
            return false;
        }
    };

// Basic block class
    class Block {
    public:
        std::string label;
        std::vector<std::unique_ptr<Instruction>> instructions;
        std::vector<std::shared_ptr<Block>> predecessors;
        std::vector<std::shared_ptr<Block>> successors;
        std::shared_ptr<Block> exit;
        std::unordered_map<std::string, PhiInstruction*> phiInstructions; // def -> phi instruction
        int visited = 0;
        bool isStart = false;
        int lastLine = 0;
        explicit Block(std::string label)
                : label(std::move(label)), exit(nullptr) {}

        // Add instruction to the block
        void addInstruction(std::unique_ptr<Instruction> instr) {
            instructions.push_back(std::move(instr));
        }

        std::string toString() const {
            std::stringstream ss;

            // Print block label if it's not the entry block
            if (label != "entry") {
                ss << "\n" << label << ":\n";
            }

            // Print each instruction with proper indentation
            for (const auto& inst : instructions) {
                ss << "  " << inst->toString() << "\n";
            }

            return ss.str();
        }

        // Add predecessor block
        void addSuccessor(std::shared_ptr<Block> succ) {
            successors.push_back(succ);
        }

        void addPredecessor(std::shared_ptr<Block> pred) {
            predecessors.push_back(pred);
        }

    };


    void printCFG(std::shared_ptr<Block>& entryBlock);
    std::shared_ptr<Block> deepCopyCFG(std::shared_ptr<Block> entryBlock,
                                       std::unordered_map<std::string, std::shared_ptr<Block>>& labelToBlockMap);
    std::vector<std::shared_ptr<Block>> topologicalSort(std::shared_ptr<Block> entryBlock);
} // namespace cfg

#endif // CFG_H