#pragma once
#include <memory>
#include <string>
#include <vector>
#include "antlr4-runtime.h"
#include "GoliteLexer.h"
#include "context.h"

namespace lexer {

class Lexer {
public:
    virtual antlr4::CommonTokenStream* GetTokenStream() = 0;
    virtual const std::vector<context::CompilerError*>& GetErrors() = 0;
    virtual void PrintTokens() = 0;
    virtual ~Lexer() = default;
};

class LexerWrapper : public Lexer, public antlr4::BaseErrorListener {
public:
    static std::unique_ptr<LexerWrapper> NewLexer(const std::string& inputSourcePath);
    void PrintTokens() override;
    // From BaseErrorListener
    void syntaxError(antlr4::Recognizer* recognizer, 
                    antlr4::Token* offendingSymbol,
                    size_t line,
                    size_t charPositionInLine,
                    const std::string& msg,
                    std::exception_ptr e) override;

    // From Lexer interface
    antlr4::CommonTokenStream* GetTokenStream() override;
    const std::vector<context::CompilerError*>& GetErrors() override;
    ~LexerWrapper();

private:
    LexerWrapper() = default;
    std::unique_ptr<antlr4::ANTLRInputStream> input;
    std::unique_ptr<GoliteLexer> antlrLexer;
    std::unique_ptr<antlr4::CommonTokenStream> stream;
    std::vector<context::CompilerError*> errors;
};

} // namespace lexer
