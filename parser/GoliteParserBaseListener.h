
// Generated from GoliteParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "GoliteParserListener.h"


namespace parser {

/**
 * This class provides an empty implementation of GoliteParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  GoliteParserBaseListener : public GoliteParserListener {
public:

  virtual void enterProgram(GoliteParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(GoliteParser::ProgramContext * /*ctx*/) override { }

  virtual void enterTypes(GoliteParser::TypesContext * /*ctx*/) override { }
  virtual void exitTypes(GoliteParser::TypesContext * /*ctx*/) override { }

  virtual void enterTypeDeclaration(GoliteParser::TypeDeclarationContext * /*ctx*/) override { }
  virtual void exitTypeDeclaration(GoliteParser::TypeDeclarationContext * /*ctx*/) override { }

  virtual void enterFields(GoliteParser::FieldsContext * /*ctx*/) override { }
  virtual void exitFields(GoliteParser::FieldsContext * /*ctx*/) override { }

  virtual void enterDecl(GoliteParser::DeclContext * /*ctx*/) override { }
  virtual void exitDecl(GoliteParser::DeclContext * /*ctx*/) override { }

  virtual void enterType(GoliteParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(GoliteParser::TypeContext * /*ctx*/) override { }

  virtual void enterDeclarations(GoliteParser::DeclarationsContext * /*ctx*/) override { }
  virtual void exitDeclarations(GoliteParser::DeclarationsContext * /*ctx*/) override { }

  virtual void enterDeclaration(GoliteParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(GoliteParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterIds(GoliteParser::IdsContext * /*ctx*/) override { }
  virtual void exitIds(GoliteParser::IdsContext * /*ctx*/) override { }

  virtual void enterFunctions(GoliteParser::FunctionsContext * /*ctx*/) override { }
  virtual void exitFunctions(GoliteParser::FunctionsContext * /*ctx*/) override { }

  virtual void enterFunction(GoliteParser::FunctionContext * /*ctx*/) override { }
  virtual void exitFunction(GoliteParser::FunctionContext * /*ctx*/) override { }

  virtual void enterParameters(GoliteParser::ParametersContext * /*ctx*/) override { }
  virtual void exitParameters(GoliteParser::ParametersContext * /*ctx*/) override { }

  virtual void enterReturnType(GoliteParser::ReturnTypeContext * /*ctx*/) override { }
  virtual void exitReturnType(GoliteParser::ReturnTypeContext * /*ctx*/) override { }

  virtual void enterStatements(GoliteParser::StatementsContext * /*ctx*/) override { }
  virtual void exitStatements(GoliteParser::StatementsContext * /*ctx*/) override { }

  virtual void enterStatement(GoliteParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(GoliteParser::StatementContext * /*ctx*/) override { }

  virtual void enterInvocation(GoliteParser::InvocationContext * /*ctx*/) override { }
  virtual void exitInvocation(GoliteParser::InvocationContext * /*ctx*/) override { }

  virtual void enterBlock(GoliteParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(GoliteParser::BlockContext * /*ctx*/) override { }

  virtual void enterAssignment(GoliteParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(GoliteParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterPrint(GoliteParser::PrintContext * /*ctx*/) override { }
  virtual void exitPrint(GoliteParser::PrintContext * /*ctx*/) override { }

  virtual void enterScan(GoliteParser::ScanContext * /*ctx*/) override { }
  virtual void exitScan(GoliteParser::ScanContext * /*ctx*/) override { }

  virtual void enterDelete(GoliteParser::DeleteContext * /*ctx*/) override { }
  virtual void exitDelete(GoliteParser::DeleteContext * /*ctx*/) override { }

  virtual void enterConditional(GoliteParser::ConditionalContext * /*ctx*/) override { }
  virtual void exitConditional(GoliteParser::ConditionalContext * /*ctx*/) override { }

  virtual void enterLoop(GoliteParser::LoopContext * /*ctx*/) override { }
  virtual void exitLoop(GoliteParser::LoopContext * /*ctx*/) override { }

  virtual void enterReturn(GoliteParser::ReturnContext * /*ctx*/) override { }
  virtual void exitReturn(GoliteParser::ReturnContext * /*ctx*/) override { }

  virtual void enterExpression(GoliteParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(GoliteParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterBoolExpression(GoliteParser::BoolExpressionContext * /*ctx*/) override { }
  virtual void exitBoolExpression(GoliteParser::BoolExpressionContext * /*ctx*/) override { }

  virtual void enterBoolTerm(GoliteParser::BoolTermContext * /*ctx*/) override { }
  virtual void exitBoolTerm(GoliteParser::BoolTermContext * /*ctx*/) override { }

  virtual void enterEqualTerm(GoliteParser::EqualTermContext * /*ctx*/) override { }
  virtual void exitEqualTerm(GoliteParser::EqualTermContext * /*ctx*/) override { }

  virtual void enterRelationTerm(GoliteParser::RelationTermContext * /*ctx*/) override { }
  virtual void exitRelationTerm(GoliteParser::RelationTermContext * /*ctx*/) override { }

  virtual void enterArithmeticExpression(GoliteParser::ArithmeticExpressionContext * /*ctx*/) override { }
  virtual void exitArithmeticExpression(GoliteParser::ArithmeticExpressionContext * /*ctx*/) override { }

  virtual void enterSimpleTerm(GoliteParser::SimpleTermContext * /*ctx*/) override { }
  virtual void exitSimpleTerm(GoliteParser::SimpleTermContext * /*ctx*/) override { }

  virtual void enterTerm(GoliteParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(GoliteParser::TermContext * /*ctx*/) override { }

  virtual void enterUnaryTerm(GoliteParser::UnaryTermContext * /*ctx*/) override { }
  virtual void exitUnaryTerm(GoliteParser::UnaryTermContext * /*ctx*/) override { }

  virtual void enterSelectorTerm(GoliteParser::SelectorTermContext * /*ctx*/) override { }
  virtual void exitSelectorTerm(GoliteParser::SelectorTermContext * /*ctx*/) override { }

  virtual void enterFactor(GoliteParser::FactorContext * /*ctx*/) override { }
  virtual void exitFactor(GoliteParser::FactorContext * /*ctx*/) override { }

  virtual void enterArguments(GoliteParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(GoliteParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterLvalue(GoliteParser::LvalueContext * /*ctx*/) override { }
  virtual void exitLvalue(GoliteParser::LvalueContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace parser
