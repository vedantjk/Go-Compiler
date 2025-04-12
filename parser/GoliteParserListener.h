
// Generated from GoliteParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "GoliteParser.h"


namespace parser {

/**
 * This interface defines an abstract listener for a parse tree produced by GoliteParser.
 */
class  GoliteParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(GoliteParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(GoliteParser::ProgramContext *ctx) = 0;

  virtual void enterTypes(GoliteParser::TypesContext *ctx) = 0;
  virtual void exitTypes(GoliteParser::TypesContext *ctx) = 0;

  virtual void enterTypeDeclaration(GoliteParser::TypeDeclarationContext *ctx) = 0;
  virtual void exitTypeDeclaration(GoliteParser::TypeDeclarationContext *ctx) = 0;

  virtual void enterFields(GoliteParser::FieldsContext *ctx) = 0;
  virtual void exitFields(GoliteParser::FieldsContext *ctx) = 0;

  virtual void enterDecl(GoliteParser::DeclContext *ctx) = 0;
  virtual void exitDecl(GoliteParser::DeclContext *ctx) = 0;

  virtual void enterType(GoliteParser::TypeContext *ctx) = 0;
  virtual void exitType(GoliteParser::TypeContext *ctx) = 0;

  virtual void enterDeclarations(GoliteParser::DeclarationsContext *ctx) = 0;
  virtual void exitDeclarations(GoliteParser::DeclarationsContext *ctx) = 0;

  virtual void enterDeclaration(GoliteParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(GoliteParser::DeclarationContext *ctx) = 0;

  virtual void enterIds(GoliteParser::IdsContext *ctx) = 0;
  virtual void exitIds(GoliteParser::IdsContext *ctx) = 0;

  virtual void enterFunctions(GoliteParser::FunctionsContext *ctx) = 0;
  virtual void exitFunctions(GoliteParser::FunctionsContext *ctx) = 0;

  virtual void enterFunction(GoliteParser::FunctionContext *ctx) = 0;
  virtual void exitFunction(GoliteParser::FunctionContext *ctx) = 0;

  virtual void enterParameters(GoliteParser::ParametersContext *ctx) = 0;
  virtual void exitParameters(GoliteParser::ParametersContext *ctx) = 0;

  virtual void enterReturnType(GoliteParser::ReturnTypeContext *ctx) = 0;
  virtual void exitReturnType(GoliteParser::ReturnTypeContext *ctx) = 0;

  virtual void enterStatements(GoliteParser::StatementsContext *ctx) = 0;
  virtual void exitStatements(GoliteParser::StatementsContext *ctx) = 0;

  virtual void enterStatement(GoliteParser::StatementContext *ctx) = 0;
  virtual void exitStatement(GoliteParser::StatementContext *ctx) = 0;

  virtual void enterInvocation(GoliteParser::InvocationContext *ctx) = 0;
  virtual void exitInvocation(GoliteParser::InvocationContext *ctx) = 0;

  virtual void enterBlock(GoliteParser::BlockContext *ctx) = 0;
  virtual void exitBlock(GoliteParser::BlockContext *ctx) = 0;

  virtual void enterAssignment(GoliteParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(GoliteParser::AssignmentContext *ctx) = 0;

  virtual void enterPrint(GoliteParser::PrintContext *ctx) = 0;
  virtual void exitPrint(GoliteParser::PrintContext *ctx) = 0;

  virtual void enterScan(GoliteParser::ScanContext *ctx) = 0;
  virtual void exitScan(GoliteParser::ScanContext *ctx) = 0;

  virtual void enterDelete(GoliteParser::DeleteContext *ctx) = 0;
  virtual void exitDelete(GoliteParser::DeleteContext *ctx) = 0;

  virtual void enterConditional(GoliteParser::ConditionalContext *ctx) = 0;
  virtual void exitConditional(GoliteParser::ConditionalContext *ctx) = 0;

  virtual void enterLoop(GoliteParser::LoopContext *ctx) = 0;
  virtual void exitLoop(GoliteParser::LoopContext *ctx) = 0;

  virtual void enterReturn(GoliteParser::ReturnContext *ctx) = 0;
  virtual void exitReturn(GoliteParser::ReturnContext *ctx) = 0;

  virtual void enterExpression(GoliteParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(GoliteParser::ExpressionContext *ctx) = 0;

  virtual void enterBoolExpression(GoliteParser::BoolExpressionContext *ctx) = 0;
  virtual void exitBoolExpression(GoliteParser::BoolExpressionContext *ctx) = 0;

  virtual void enterBoolTerm(GoliteParser::BoolTermContext *ctx) = 0;
  virtual void exitBoolTerm(GoliteParser::BoolTermContext *ctx) = 0;

  virtual void enterEqualTerm(GoliteParser::EqualTermContext *ctx) = 0;
  virtual void exitEqualTerm(GoliteParser::EqualTermContext *ctx) = 0;

  virtual void enterRelationTerm(GoliteParser::RelationTermContext *ctx) = 0;
  virtual void exitRelationTerm(GoliteParser::RelationTermContext *ctx) = 0;

  virtual void enterArithmeticExpression(GoliteParser::ArithmeticExpressionContext *ctx) = 0;
  virtual void exitArithmeticExpression(GoliteParser::ArithmeticExpressionContext *ctx) = 0;

  virtual void enterSimpleTerm(GoliteParser::SimpleTermContext *ctx) = 0;
  virtual void exitSimpleTerm(GoliteParser::SimpleTermContext *ctx) = 0;

  virtual void enterTerm(GoliteParser::TermContext *ctx) = 0;
  virtual void exitTerm(GoliteParser::TermContext *ctx) = 0;

  virtual void enterUnaryTerm(GoliteParser::UnaryTermContext *ctx) = 0;
  virtual void exitUnaryTerm(GoliteParser::UnaryTermContext *ctx) = 0;

  virtual void enterSelectorTerm(GoliteParser::SelectorTermContext *ctx) = 0;
  virtual void exitSelectorTerm(GoliteParser::SelectorTermContext *ctx) = 0;

  virtual void enterFactor(GoliteParser::FactorContext *ctx) = 0;
  virtual void exitFactor(GoliteParser::FactorContext *ctx) = 0;

  virtual void enterArguments(GoliteParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(GoliteParser::ArgumentsContext *ctx) = 0;

  virtual void enterLvalue(GoliteParser::LvalueContext *ctx) = 0;
  virtual void exitLvalue(GoliteParser::LvalueContext *ctx) = 0;


};

}  // namespace parser
