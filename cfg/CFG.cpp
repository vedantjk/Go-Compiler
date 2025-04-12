// CFG.cpp
#include "CFG.h"

namespace cfg {

    void printCFG(std::shared_ptr<Block>& entryBlock) {
        if (!entryBlock) {
            std::cout << "Empty CFG (no entry block provided)" << std::endl;
            return;
        }

        std::cout << "Control Flow Graph:" << std::endl;
        std::cout << "===================" << std::endl;

        // Static map to track visited blocks by label
        static std::unordered_map<std::string, bool> visited;

        std::function<void(std::shared_ptr<Block>)> dfs = [&](std::shared_ptr<Block> current) {
            if (!current || visited[current->label]) {
                return;
            }
            visited[current->label] = true;

            // Print block label
            std::cout << "Block: " << current->label << std::endl;

            // Print successors first
            if (!current->successors.empty()) {
                std::cout << "  Successors: ";
                for (size_t i = 0; i < current->successors.size(); ++i) {
                    std::cout << current->successors[i]->label;
                    if (i < current->successors.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }

            // Print predecessors
            if (!current->predecessors.empty()) {
                std::cout << "  Predecessors: ";
                for (size_t i = 0; i < current->predecessors.size(); ++i) {
                    std::cout << current->predecessors[i]->label;
                    if (i < current->predecessors.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }

            // Print exit block if set
            if (current->exit) {
                std::cout << "  Exit: " << current->exit->label << std::endl;
            }

            std::cout << std::endl;

            // Visit successors first
            for (const auto& succ : current->successors) {
                if (!visited[succ->label]) {
                    dfs(succ);
                }
            }

            // Visit exit block
            if (current->exit && !visited[current->exit->label]) {
                dfs(current->exit);
            }
        };

        // Reset visited map before starting DFS
        visited.clear();

        // Start DFS traversal
        dfs(entryBlock);

        // Print total count
        std::cout << "Total blocks: " << visited.size() << std::endl;
    }

    std::shared_ptr<Block> deepCopyCFG(std::shared_ptr<Block> entryBlock,
                                       std::unordered_map<std::string, std::shared_ptr<Block>>& labelToBlockMap) {
        if (!entryBlock) return nullptr;

        std::unordered_map<std::shared_ptr<Block>, std::shared_ptr<Block>> blockMap;

        std::function<std::shared_ptr<Block>(std::shared_ptr<Block>)> copyBlock;
        copyBlock = [&](std::shared_ptr<Block> original) -> std::shared_ptr<Block> {
            if (!original) return nullptr;

            // If block is already copied, return it
            if (blockMap.find(original) != blockMap.end()) {
                return blockMap[original];
            }

            // Create a new block with the same label
            std::shared_ptr<Block> newBlock = std::make_shared<Block>(original->label);
            blockMap[original] = newBlock;
            labelToBlockMap[original->label] = newBlock; // Store in label-based map

            // Copy successors
            for (const auto& succ : original->successors) {
                std::shared_ptr<Block> copiedSucc = copyBlock(succ);
                if (copiedSucc) newBlock->addSuccessor(copiedSucc);
            }

            // Copy predecessors
            for (const auto& pred : original->predecessors) {
                std::shared_ptr<Block> copiedPred = copyBlock(pred);
                if (copiedPred) newBlock->addPredecessor(copiedPred);
            }

            // Copy exit block if present
            if (original->exit) {
                newBlock->exit = copyBlock(original->exit);
            }

            return newBlock;
        };

        return copyBlock(entryBlock);
    }


    std::vector<std::shared_ptr<Block>> topologicalSort(std::shared_ptr<Block> entryBlock) {
        if (!entryBlock) return {};

        std::unordered_set<std::shared_ptr<Block>> visited;
        std::unordered_set<std::shared_ptr<Block>> onStack;
        std::vector<std::shared_ptr<Block>> result;

        // DFS function
        std::function<void(std::shared_ptr<Block>)> dfs = [&](std::shared_ptr<Block> block) {
            if (!block || visited.find(block) != visited.end()) return;

            visited.insert(block);
            onStack.insert(block);

            // Visit successors, but ignore back edges
            for (const auto& succ : block->successors) {
                if (onStack.find(succ) != onStack.end()) {
                    // Ignore this edge (back edge)
                    continue;
                }
                dfs(succ);
            }

            // Visit exit block, ignoring back edges
            if (block->exit && onStack.find(block->exit) == onStack.end()) {
                dfs(block->exit);
            }

            onStack.erase(block);  // Remove from recursion stack
            result.push_back(block);  // Add to topological order
        };

        // Start DFS from the entry block
        dfs(entryBlock);

        // Reverse to get correct topological order
        std::reverse(result.begin(), result.end());

        return result;
    }




} // namespace cfg