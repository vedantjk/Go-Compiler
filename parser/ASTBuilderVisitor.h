#pragma once
#include <memory>
#include "GoliteParserVisitor.h"
#include "astNodes/Program.h"
#include "topLevelNodes/Function.h"
#include "topLevelNodes/VarDecl.h"
#include "topLevelNodes/TypeDecl.h"
#include "astNodes/Statement.h"
#include "expressions/Expression.h"
#include "statements/AssignStmt.h"
#include "statements/ScanStmt.h"
#include "statements/DeleteStmt.h"
#include "statements/IfStmt.h"
#include "statements/ForStmt.h"
#include "statements/BlockStmt.h"
#include "statements/PrintStmt.h"
#include "statements/ReturnStmt.h"
#include "expressions/BinaryExpr.h"
#include "expressions/UnaryExpr.h"
#include "expressions/VariableExpr.h"
#include "expressions/BooleanLiteral.h"
#include "expressions/IntegerLiteral.h"

using namespace parser;
namespace ast {

    class ASTBuilderVisitor : public parser::GoliteParserVisitor {
    public:
        std::unique_ptr<Program> astRoot;

        // Visit program
        antlrcpp::Any visitProgram(GoliteParser::ProgramContext *ctx) override;

        // Visit type declarations
        antlrcpp::Any visitTypeDeclaration(GoliteParser::TypeDeclarationContext *ctx) override;

        // Visit variable declarations
        antlrcpp::Any visitDeclaration(GoliteParser::DeclarationContext *ctx) override;

        // Visit functions
        antlrcpp::Any visitFunction(GoliteParser::FunctionContext *ctx) override;

        // Visit statements
        antlrcpp::Any visitAssignment(GoliteParser::AssignmentContext *ctx) override;
        antlrcpp::Any visitPrint(GoliteParser::PrintContext *ctx) override;
        antlrcpp::Any visitScan(GoliteParser::ScanContext *ctx) override;
        antlrcpp::Any visitDelete(GoliteParser::DeleteContext *ctx) override;
        antlrcpp::Any visitConditional(GoliteParser::ConditionalContext *ctx) override;
        antlrcpp::Any visitLoop(GoliteParser::LoopContext *ctx) override;
        antlrcpp::Any visitReturn(GoliteParser::ReturnContext *ctx) override;
        antlrcpp::Any visitBlock(GoliteParser::BlockContext *ctx) override;
        antlrcpp::Any  visitInvocation(GoliteParser::InvocationContext *ctx) override;
        // Visit expressions
        antlrcpp::Any visitExpression(GoliteParser::ExpressionContext *ctx) override;
        antlrcpp::Any visitBoolExpression(GoliteParser::BoolExpressionContext *ctx) override;
        antlrcpp::Any visitArithmeticExpression(GoliteParser::ArithmeticExpressionContext *ctx) override;
        antlrcpp::Any visitUnaryTerm(GoliteParser::UnaryTermContext *ctx) override;
        antlrcpp::Any visitFactor(GoliteParser::FactorContext *ctx) override;

        antlrcpp::Any visitTypes(GoliteParser::TypesContext *ctx) override { return nullptr; }
        antlrcpp::Any visitFields(GoliteParser::FieldsContext *ctx) override { return nullptr; }
        antlrcpp::Any visitDecl(GoliteParser::DeclContext *ctx) override { return nullptr; }
        antlrcpp::Any visitType(GoliteParser::TypeContext *ctx) override { return nullptr; }
        antlrcpp::Any visitDeclarations(GoliteParser::DeclarationsContext *ctx) override { return nullptr; }
        antlrcpp::Any visitIds(GoliteParser::IdsContext *ctx) override { return nullptr; }
        antlrcpp::Any visitFunctions(GoliteParser::FunctionsContext *ctx) override { return nullptr; }
        antlrcpp::Any visitParameters(GoliteParser::ParametersContext *ctx) override { return nullptr; }
        antlrcpp::Any visitReturnType(GoliteParser::ReturnTypeContext *ctx) override { return nullptr; }
        antlrcpp::Any visitStatements(GoliteParser::StatementsContext *ctx) override;
        antlrcpp::Any visitStatement(GoliteParser::StatementContext *ctx) override;
        antlrcpp::Any visitBoolTerm(GoliteParser::BoolTermContext *ctx) override;
        antlrcpp::Any visitEqualTerm(GoliteParser::EqualTermContext *ctx) override;
        antlrcpp::Any visitRelationTerm(GoliteParser::RelationTermContext *ctx) override;
        antlrcpp::Any visitSimpleTerm(GoliteParser::SimpleTermContext *ctx) override;
        antlrcpp::Any visitTerm(GoliteParser::TermContext *ctx) override;
        antlrcpp::Any visitSelectorTerm(GoliteParser::SelectorTermContext *ctx) override;
        antlrcpp::Any visitArguments(GoliteParser::ArgumentsContext *ctx) override { return nullptr; }
        antlrcpp::Any visitLvalue(GoliteParser::LvalueContext *ctx) override;
    };

} // namespace ast
