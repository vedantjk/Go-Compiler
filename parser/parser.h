#pragma once
#include <memory>
#include <vector>
#include "ASTBuilderVisitor.h"
#include "GoliteParser.h"
#include "antlr4-runtime.h"
#include "GoliteParser.h"
#include "lexer.h"
#include "../ast/astNodes/Program.h"
namespace parser {

    class Parser {
    public:
        virtual std::shared_ptr<ast::Program> Parse() = 0;  // Now returns AST
        virtual const std::vector<context::CompilerError*>& GetErrors() = 0;
        virtual void PrintAST() = 0;
        virtual ~Parser() = default;
    };

    class ParserWrapper : public Parser, public antlr4::BaseErrorListener {
    public:
        static std::unique_ptr<ParserWrapper> NewParser(std::unique_ptr<lexer::LexerWrapper> lexer);

        std::shared_ptr<ast::Program> Parse() override;  // Parses and returns AST
        const std::vector<context::CompilerError*>& GetErrors() override;
        void PrintAST() override;  // Prints AST
        void syntaxError(antlr4::Recognizer* recognizer,
                         antlr4::Token* offendingSymbol,
                         size_t line,
                         size_t charPositionInLine,
                         const std::string& msg,
                         std::exception_ptr e) override;

        ~ParserWrapper();

    private:
        ParserWrapper(std::unique_ptr<lexer::LexerWrapper> lexer);

        std::unique_ptr<lexer::LexerWrapper> lexer;
        std::unique_ptr<GoliteParser> antlrParser;
        antlr4::tree::ParseTree* parseTree;
        std::vector<context::CompilerError*> errors;
        std::shared_ptr<ast::Program> ast;
    };

} // namespace parser

