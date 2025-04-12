
// Generated from GoliteParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "GoliteParser.h"


namespace parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by GoliteParser.
 */
class  GoliteParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by GoliteParser.
   */
    virtual std::any visitProgram(GoliteParser::ProgramContext *context) = 0;

    virtual std::any visitTypes(GoliteParser::TypesContext *context) = 0;

    virtual std::any visitTypeDeclaration(GoliteParser::TypeDeclarationContext *context) = 0;

    virtual std::any visitFields(GoliteParser::FieldsContext *context) = 0;

    virtual std::any visitDecl(GoliteParser::DeclContext *context) = 0;

    virtual std::any visitType(GoliteParser::TypeContext *context) = 0;

    virtual std::any visitDeclarations(GoliteParser::DeclarationsContext *context) = 0;

    virtual std::any visitDeclaration(GoliteParser::DeclarationContext *context) = 0;

    virtual std::any visitIds(GoliteParser::IdsContext *context) = 0;

    virtual std::any visitFunctions(GoliteParser::FunctionsContext *context) = 0;

    virtual std::any visitFunction(GoliteParser::FunctionContext *context) = 0;

    virtual std::any visitParameters(GoliteParser::ParametersContext *context) = 0;

    virtual std::any visitReturnType(GoliteParser::ReturnTypeContext *context) = 0;

    virtual std::any visitStatements(GoliteParser::StatementsContext *context) = 0;

    virtual std::any visitStatement(GoliteParser::StatementContext *context) = 0;

    virtual std::any visitInvocation(GoliteParser::InvocationContext *context) = 0;

    virtual std::any visitBlock(GoliteParser::BlockContext *context) = 0;

    virtual std::any visitAssignment(GoliteParser::AssignmentContext *context) = 0;

    virtual std::any visitPrint(GoliteParser::PrintContext *context) = 0;

    virtual std::any visitScan(GoliteParser::ScanContext *context) = 0;

    virtual std::any visitDelete(GoliteParser::DeleteContext *context) = 0;

    virtual std::any visitConditional(GoliteParser::ConditionalContext *context) = 0;

    virtual std::any visitLoop(GoliteParser::LoopContext *context) = 0;

    virtual std::any visitReturn(GoliteParser::ReturnContext *context) = 0;

    virtual std::any visitExpression(GoliteParser::ExpressionContext *context) = 0;

    virtual std::any visitBoolExpression(GoliteParser::BoolExpressionContext *context) = 0;

    virtual std::any visitBoolTerm(GoliteParser::BoolTermContext *context) = 0;

    virtual std::any visitEqualTerm(GoliteParser::EqualTermContext *context) = 0;

    virtual std::any visitRelationTerm(GoliteParser::RelationTermContext *context) = 0;

    virtual std::any visitArithmeticExpression(GoliteParser::ArithmeticExpressionContext *context) = 0;

    virtual std::any visitSimpleTerm(GoliteParser::SimpleTermContext *context) = 0;

    virtual std::any visitTerm(GoliteParser::TermContext *context) = 0;

    virtual std::any visitUnaryTerm(GoliteParser::UnaryTermContext *context) = 0;

    virtual std::any visitSelectorTerm(GoliteParser::SelectorTermContext *context) = 0;

    virtual std::any visitFactor(GoliteParser::FactorContext *context) = 0;

    virtual std::any visitArguments(GoliteParser::ArgumentsContext *context) = 0;

    virtual std::any visitLvalue(GoliteParser::LvalueContext *context) = 0;


};

}  // namespace parser
