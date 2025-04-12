
// Generated from GoliteParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "GoliteParserVisitor.h"


namespace parser {

/**
 * This class provides an empty implementation of GoliteParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  GoliteParserBaseVisitor : public GoliteParserVisitor {
public:

  virtual std::any visitProgram(GoliteParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypes(GoliteParser::TypesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDeclaration(GoliteParser::TypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFields(GoliteParser::FieldsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(GoliteParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(GoliteParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarations(GoliteParser::DeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(GoliteParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIds(GoliteParser::IdsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctions(GoliteParser::FunctionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction(GoliteParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameters(GoliteParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnType(GoliteParser::ReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatements(GoliteParser::StatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(GoliteParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvocation(GoliteParser::InvocationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(GoliteParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(GoliteParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrint(GoliteParser::PrintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScan(GoliteParser::ScanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDelete(GoliteParser::DeleteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditional(GoliteParser::ConditionalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoop(GoliteParser::LoopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturn(GoliteParser::ReturnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(GoliteParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolExpression(GoliteParser::BoolExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolTerm(GoliteParser::BoolTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualTerm(GoliteParser::EqualTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationTerm(GoliteParser::RelationTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArithmeticExpression(GoliteParser::ArithmeticExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleTerm(GoliteParser::SimpleTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerm(GoliteParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryTerm(GoliteParser::UnaryTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectorTerm(GoliteParser::SelectorTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactor(GoliteParser::FactorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(GoliteParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLvalue(GoliteParser::LvalueContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace parser
