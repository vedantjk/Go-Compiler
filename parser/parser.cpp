#include "parser.h"

namespace parser {

    ParserWrapper::ParserWrapper(std::unique_ptr<lexer::LexerWrapper> lexer)
            : lexer(std::move(lexer)), antlrParser(nullptr), parseTree(nullptr), ast(nullptr) {
        auto tokenStream = this->lexer->GetTokenStream();
        antlrParser = std::make_unique<GoliteParser>(tokenStream);
        antlrParser->removeErrorListeners();
        antlrParser->addErrorListener(this);
    }

    std::unique_ptr<ParserWrapper> ParserWrapper::NewParser(std::unique_ptr<lexer::LexerWrapper> lexer) {
        return std::unique_ptr<ParserWrapper>(new ParserWrapper(std::move(lexer)));
    }

    std::shared_ptr<ast::Program> ParserWrapper::Parse() {
        parseTree = antlrParser->program();
        if (context::hasErrors(errors)) {
            return nullptr;
        }

        // Use AST Visitor to construct AST
        ast::ASTBuilderVisitor visitor;
        auto any_result = visitor.visit(parseTree);

        try {
            ast = std::any_cast<std::shared_ptr<ast::Program>>(std::move(any_result));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "AST Visitor returned unexpected type: " << any_result.type().name() << std::endl;
            throw;
        }

        if (!ast) {
            std::cerr << "AST construction failed.\n";
            return nullptr;
        }
        // Create the SymbolTables instance
        auto symbolTables = std::make_shared<symboltable::SymbolTables>();

        // Call BuildSymbolTable on the AST
        std::vector<context::CompilerError> symbolErrors;
        try {
            ast->BuildSymbolTable(symbolErrors, symbolTables);
        } catch (const std::exception &e) {
            std::cerr << "Error at parser.cpp: " << e.what() << std::endl;
            return nullptr;
        }


        // Check for semantic errors
        if (!symbolErrors.empty()) {
            std::cerr << "Semantic analysis found errors:\n";
            for (const auto& error : symbolErrors) {
                std::cerr << error.toString() << std::endl;
            }
            return nullptr;
        }

        return ast;
    }





    const std::vector<context::CompilerError*>& ParserWrapper::GetErrors() {
        return errors;
    }

    void ParserWrapper::PrintAST() {
        if (!lexer->GetErrors().empty() || !errors.empty()) {
            std::cerr << "Skipping AST construction due to errors.\n";
            return;
        }

        ast = Parse();

        if (!ast) {
            std::cerr << "AST construction failed due to syntax or semantic errors.\n";
            return;
        }

        std::cout << "Abstract Syntax Tree:\n";
        ast->print(std::cout, 0);
        std::cout << std::endl;
    }


    void ParserWrapper::syntaxError(antlr4::Recognizer* recognizer,
                                    antlr4::Token* offendingSymbol,
                                    size_t line,
                                    size_t charPositionInLine,
                                    const std::string& msg,
                                    std::exception_ptr e) {
        auto error = new context::CompilerError{
                static_cast<int>(line),
                static_cast<int>(charPositionInLine),
                msg,
                context::CompilerPhase::PARSER
        };
        errors.push_back(error);
    }

    ParserWrapper::~ParserWrapper() {
        for (auto error : errors) {
            delete error;
        }
    }

} // namespace parser
