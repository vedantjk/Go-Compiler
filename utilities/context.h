#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <sstream>

namespace context {

    // Token type names
    inline const std::vector<std::string> typeNames{
            "TYPE", "STRUCT", "VAR", "FUNC", "IF", "ELSE", "FOR", "RETURN", "SCAN",
            "PRINTF", "DELETE", "NEW", "TRUE", "FALSE", "NIL", "INT", "BOOL",
            "L_PAREN", "R_PAREN", "L_CURLY", "R_CURLY", "L_BRACKET", "R_BRACKET",
            "ASSIGN", "COMMA", "SEMI", "COLON", "DOT", "PLUS", "MINUS", "STAR",
            "DIV", "MOD", "EXCLAMATION", "LOGICAL_OR", "LOGICAL_AND", "EQUALS",
            "NOT_EQUALS", "LESS", "LESS_OR_EQUALS", "GREATER", "GREATER_OR_EQUALS",
            "PERCENT_D", "ID", "NUMBER", "STRING", "WS", "COMMENT", "EOF"
    };

// Enum to represent compiler phases
enum class CompilerPhase {
    LEXER,
    PARSER,
    SEMANTIC
};

    struct Parameter {
        std::string name;
        std::string type;
        int line;
        int column;

        Parameter(std::string name, std::string type, int line, int column)
                : name(std::move(name)), type(std::move(type)), line(line), column(column) {}
    };
// Structure to store compiler errors
struct CompilerError {
    int line;
    int column;
    std::string msg;
    CompilerPhase phase;

    CompilerError(int line, int column, std::string  msg, CompilerPhase phase)
        : line(line), column(column), msg(std::move(msg)), phase(phase) {}

    [[nodiscard]] std::string toString() const {
        std::ostringstream out;
        if (phase == CompilerPhase::LEXER) {
            out << "lexer error(" << line << ":" << column << "): " << msg;
        } else if (phase == CompilerPhase::PARSER) {
            out << "syntax error(" << line << "," << column << "): " << msg;
        } else if(phase == CompilerPhase::SEMANTIC){
            out<< "semantic error(" << line << ":" << column << "): "<< msg;
        }

        else {
            throw std::runtime_error("Invalid phase found");
        }
        return out.str();
    }
};

// Function to check and print errors
inline bool hasErrors(const std::vector<CompilerError*>& errors) {
    if (!errors.empty()) {
        for (const auto& e : errors) {
            std::cout << e->toString() << std::endl;
        }
        return true;
    }
    return false;
}

} // namespace context

#endif // CONTEXT_H
