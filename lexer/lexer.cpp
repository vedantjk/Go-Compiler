#include "lexer.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

namespace lexer
{

    void LexerWrapper::syntaxError(antlr4::Recognizer *recognizer,
                                   antlr4::Token *offendingSymbol,
                                   size_t line,
                                   size_t charPositionInLine,
                                   const std::string &msg,
                                   std::exception_ptr e)
    {
        auto error = new context::CompilerError{
            static_cast<int>(line),
            static_cast<int>(charPositionInLine),
            msg,
            context::CompilerPhase::LEXER};
        errors.push_back(error);
    }

    antlr4::CommonTokenStream *LexerWrapper::GetTokenStream()
    {
        return stream.get();
    }

    const std::vector<context::CompilerError *> &LexerWrapper::GetErrors()
    {
        return errors;
    }

    void LexerWrapper::PrintTokens() {
        auto tokens = stream.get();
        auto allTokens = tokens->getTokens();
        if(context::hasErrors(errors)) return;
        for (auto token : allTokens) {
            unsigned long int idx = (int) token->getType() - 1;
            if (idx >= context::typeNames.size()) idx = context::typeNames.size() - 1;
            std::cout << "Token: " << token->toString()
                      << " (Type: " << context::typeNames[idx]
                      << ", Line: " << token->getLine()
                      << ", Pos: " << token->getCharPositionInLine()
                      << ")" << std::endl;
        }
    }

    LexerWrapper::~LexerWrapper()
    {
        for (auto error : errors)
        {
            delete error;
        }
    }

    std::unique_ptr<LexerWrapper> LexerWrapper::NewLexer(const std::string &inputSourcePath)
    {
        // Open the file
        std::ifstream inputFile(inputSourcePath);
        if (!inputFile.is_open())
        {
            throw std::runtime_error("Failed to open input file: " + inputSourcePath);
        }

        // Read the entire file into a string
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        inputFile.close();

        // Create the input stream from the file contents
        auto input = std::make_unique<antlr4::ANTLRInputStream>(buffer.str());

        auto wrapper = std::unique_ptr<LexerWrapper>(new LexerWrapper());
        wrapper->input = std::move(input);
        wrapper->antlrLexer = std::make_unique<GoliteLexer>(wrapper->input.get());
        wrapper->antlrLexer->removeErrorListeners();
        wrapper->antlrLexer->addErrorListener(wrapper.get());
        wrapper->stream = std::make_unique<antlr4::CommonTokenStream>(wrapper->antlrLexer.get());
        wrapper->stream->fill();
        return wrapper;
    }

} // namespace lexer