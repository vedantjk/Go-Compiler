#include "ASTBuilderVisitor.h"
#include "expressions/FieldExpr.h"
#include "expressions/FunctionCallExpr.h"
#include "expressions/NilExpr.h"
#include "statements/InvocationStmt.h"
#include "expressions/NewExpr.h"

namespace ast {

// -------------------- Program Node --------------------

    antlrcpp::Any ASTBuilderVisitor::visitProgram(GoliteParser::ProgramContext *ctx) {
        std::vector<std::shared_ptr<TypeDecl>> typeDecls;
        std::vector<std::shared_ptr<VarDecl>> varDecls;
        std::vector<std::shared_ptr<Function>> functions;

        // Process type declarations
        for (auto typeCtx : ctx->types()->typeDeclaration()) {
            typeDecls.push_back(std::any_cast<std::shared_ptr<TypeDecl>>(visit(typeCtx)));
        }

        // Process variable declarations
        for (auto varCtx : ctx->declarations()->declaration()) {
            varDecls.push_back(std::any_cast<std::shared_ptr<VarDecl>>(visit(varCtx)));
        }

        // Process functions
        for (auto funcCtx : ctx->functions()->function()) {
            functions.push_back(std::any_cast<std::shared_ptr<Function>>(visit(funcCtx)));
        }

        auto programNode = std::make_shared<Program>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                std::move(typeDecls), std::move(varDecls), std::move(functions)
        );

        return programNode;
    }


// -------------------- Type Declaration --------------------

    antlrcpp::Any ASTBuilderVisitor::visitTypeDeclaration(GoliteParser::TypeDeclarationContext *ctx) {
        std::string name = ctx->ID()->getText();
        std::vector<Field> fields;

        for (auto fieldCtx : ctx->fields()->decl()) {
            fields.emplace_back(
                                     fieldCtx->ID()->getText(),
                                     fieldCtx->type()->getText(),
                                     static_cast<int>(fieldCtx->ID()->getSymbol()->getLine()),
                                     static_cast<int>(fieldCtx->ID()->getSymbol()->getCharPositionInLine())
                             );
        }

        return std::any(std::make_shared<TypeDecl>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                name, fields
        ));
    }


// -------------------- Variable Declaration --------------------

    antlrcpp::Any ASTBuilderVisitor::visitDeclaration(GoliteParser::DeclarationContext *ctx) {
        std::vector<std::string> names;
        for (auto idCtx : ctx->ids()->ID()) {
            names.push_back(idCtx->getText());
        }

        std::string type = ctx->type()->getText();

        return std::any(std::make_shared<VarDecl>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                names, type
        ));
    }

// -------------------- Function Definition --------------------

    antlrcpp::Any ASTBuilderVisitor::visitFunction(GoliteParser::FunctionContext *ctx) {
        std::string name = ctx->ID()->getText();
        std::vector<context::Parameter> parameters;
        std::vector<std::shared_ptr<VarDecl>> varDecls;
        std::shared_ptr<Statement> body;

        // Process function parameters
        if (ctx->parameters()) {
            for (auto paramCtx : ctx->parameters()->decl()) {
                parameters.emplace_back(
                                     paramCtx->ID()->getText(),              // Parameter name
                                     paramCtx->type()->getText(),            // Parameter type
                                     static_cast<int>(paramCtx->ID()->getSymbol()->getLine()), // Line number
                                     static_cast<int>(paramCtx->ID()->getSymbol()->getCharPositionInLine()) // Column number
                                     );
            }
        }


        std::string returnType = ctx->returnType() ? ctx->returnType()->getText() : "";

        // Process variable declarations
        for (auto varCtx : ctx->declarations()->declaration()) {
            varDecls.push_back(std::any_cast<std::shared_ptr<VarDecl>>(visit(varCtx)));
        }

        // Process function body
        if (ctx->statements()) {
            body = std::any_cast<std::shared_ptr<Statement>>(visit(ctx->statements()));
        }

        auto funcNode = std::make_shared<Function>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                name, parameters, returnType, std::move(varDecls), std::move(body)
        );
        return funcNode;
    }



// -------------------- Statements --------------------

    antlrcpp::Any ASTBuilderVisitor::visitStatements(GoliteParser::StatementsContext *ctx) {
        std::vector<std::shared_ptr<Statement>> statements;

        for (auto stmtCtx : ctx->statement()) {
            auto stmt = std::any_cast<std::shared_ptr<Statement>>(visit(stmtCtx));
            statements.push_back(std::move(stmt));
        }
        return std::static_pointer_cast<Statement>(std::make_shared<BlockStmt>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                std::move(statements)
        ));
    }



    antlrcpp::Any ASTBuilderVisitor::visitStatement(GoliteParser::StatementContext *ctx) {
        if (ctx->assignment()) {
            return visit(ctx->assignment());
        } else if (ctx->print()) {
            return visit(ctx->print());
        } else if (ctx->scan()) {
            return visit(ctx->scan());
        } else if (ctx->delete_()) {
            return visit(ctx->delete_());
        } else if (ctx->conditional()) {
            return visit(ctx->conditional());
        } else if (ctx->loop()) {
            return visit(ctx->loop());
        } else if (ctx->block()) {
            return visit(ctx->block());
        } else if (ctx->return_()) {
            return visit(ctx->return_());
        } else if(ctx->invocation()){
            return visit(ctx->invocation());
        }

        throw std::runtime_error("Unknown statement type");
    }


    antlrcpp::Any ASTBuilderVisitor::visitInvocation(GoliteParser::InvocationContext *ctx) {
        std::string functionName = ctx->ID()->getText();
        std::vector<std::shared_ptr<Expression>> args;

        for (auto exprCtx : ctx->arguments()->expression()) {
            auto any_result = visit(exprCtx);

            try {
                auto expr = std::any_cast<std::shared_ptr<Expression>>(any_result);
                args.push_back(std::move(expr));
            } catch (const std::bad_any_cast& e) {
                std::cerr << "ERROR: Failed to cast function argument in invocation "
                          << functionName << ". Exception: " << e.what() << std::endl;
                throw;
            }
        }

        return std::static_pointer_cast<Statement>(
                std::make_shared<InvocationStmt>(
                        ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                        functionName, std::move(args)
                )
        );
    }


    antlrcpp::Any ASTBuilderVisitor::visitAssignment(GoliteParser::AssignmentContext *ctx) {
        auto lhs_any = visit(ctx->lvalue());
        auto rhs_any = visit(ctx->expression());
        auto lhs = std::any_cast<std::shared_ptr<Expression>>(lhs_any);
        auto rhs = std::any_cast<std::shared_ptr<Expression>>(rhs_any);

        return std::static_pointer_cast<Statement>(std::make_shared<AssignStmt>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                std::move(lhs), std::move(rhs)
        ));
    }


    antlrcpp::Any ASTBuilderVisitor::visitScan(GoliteParser::ScanContext *ctx) {
        auto variable_any = visit(ctx->lvalue());
        auto variable = std::any_cast<std::shared_ptr<Expression>>(variable_any);

        return std::static_pointer_cast<Statement>(std::make_shared<ScanStmt>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                std::move(variable)
        ));
    }


    antlrcpp::Any ASTBuilderVisitor::visitDelete(GoliteParser::DeleteContext *ctx) {
        auto expr_any = visit(ctx->expression());
        auto expr = std::any_cast<std::shared_ptr<Expression>>(expr_any);

        return std::static_pointer_cast<Statement>(std::make_shared<DeleteStmt>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                std::move(expr)
        ));
    }


    antlrcpp::Any ASTBuilderVisitor::visitConditional(GoliteParser::ConditionalContext *ctx) {

        auto condition_any = visit(ctx->expression());
        auto condition = std::any_cast<std::shared_ptr<Expression>>(condition_any);
        auto thenBlock_any = visit(ctx->block(0));
        auto thenBlock = std::static_pointer_cast<Statement>(std::any_cast<std::shared_ptr<BlockStmt>>(thenBlock_any));

        std::shared_ptr<Statement> elseBlock = nullptr;

        if (ctx->block().size() > 1) {
            auto elseBlock_any = visit(ctx->block(1));
            try {
                auto elseBlockCast = std::any_cast<std::shared_ptr<BlockStmt>>(elseBlock_any);
                elseBlock = std::static_pointer_cast<Statement>(elseBlockCast);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "ERROR: Failed to cast else block to Statement. Actual type: " << elseBlock_any.type().name() << std::endl;
                throw;
            }
        }
        return std::static_pointer_cast<Statement>(std::make_shared<IfStmt>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                std::move(condition), std::move(thenBlock),
                elseBlock ? std::move(elseBlock) : nullptr
        ));

    }



    antlrcpp::Any ASTBuilderVisitor::visitLoop(GoliteParser::LoopContext *ctx) {
        auto condition_any = visit(ctx->expression());
        auto condition = std::any_cast<std::shared_ptr<Expression>>(condition_any);

        auto body_any = visit(ctx->block());
        auto body = std::any_cast<std::shared_ptr<BlockStmt>>(body_any);  // First cast to BlockStmt
        auto body_as_stmt = std::static_pointer_cast<Statement>(body);   // Then cast to Statement
        return std::static_pointer_cast<Statement>(
                std::make_shared<ForStmt>(
                        ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                        std::move(condition), std::move(body_as_stmt)  // Use the casted body
                )
        );
    }



    antlrcpp::Any ASTBuilderVisitor::visitBlock(GoliteParser::BlockContext *ctx) {
        std::vector<std::shared_ptr<Statement>> statements;

        for (auto stmtCtx : ctx->statements()->statement()) {
            auto stmt = std::any_cast<std::shared_ptr<Statement>>(visit(stmtCtx));
            statements.push_back(std::move(stmt));
        }

        return std::make_any<std::shared_ptr<BlockStmt>>(std::make_shared<BlockStmt>(
                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                std::move(statements)
        ));
    }


    antlrcpp::Any ASTBuilderVisitor::visitPrint(GoliteParser::PrintContext *ctx) {
        std::string formatString = ctx->STRING()->getText();
        std::vector<std::shared_ptr<Expression>> arguments;

        for (auto exprCtx : ctx->expression()) {
            auto arg_any = visit(exprCtx);
            auto arg = std::any_cast<std::shared_ptr<Expression>>(arg_any);
            arguments.push_back(std::move(arg));
        }
        return std::static_pointer_cast<Statement>(
                std::make_shared<PrintStmt>(
                        ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                        std::move(formatString), std::move(arguments)
                )
        );
    }


    antlrcpp::Any ASTBuilderVisitor::visitReturn(GoliteParser::ReturnContext *ctx) {
        std::shared_ptr<Expression> returnValue = nullptr;

        if (ctx->expression()) {
            auto any_expr = visit(ctx->expression());

            try {
                returnValue = std::any_cast<std::shared_ptr<Expression>>(any_expr);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "ERROR: Failed to cast return expression. Actual type: " << any_expr.type().name() << std::endl;
                return nullptr;
            }
        }
        return std::make_any<std::shared_ptr<Statement>>(
                std::make_shared<ReturnStmt>(
                        ctx->getStart()->getLine(),
                        ctx->getStart()->getCharPositionInLine(),
                        std::move(returnValue)
                )
        );
    }




// -------------------- Expressions --------------------
    antlrcpp::Any ASTBuilderVisitor::visitArithmeticExpression(GoliteParser::ArithmeticExpressionContext *ctx) {
        return visit(ctx->simpleTerm()); // Just forward the visit to simpleTerm
    }

    antlrcpp::Any ASTBuilderVisitor::visitBoolExpression(GoliteParser::BoolExpressionContext *ctx) {
        auto left_any = visit(ctx->boolTerm(0));

        if (!left_any.has_value()) {
            throw std::runtime_error("visitBoolExpression: left_any has no value!");
        }

        auto left = std::any_cast<std::shared_ptr<Expression>>(left_any);
        if (!left) {
            throw std::runtime_error("visitBoolExpression: Failed to retrieve left expression");
        }

        for (size_t i = 0; i < ctx->LOGICAL_OR().size(); i++) {
            auto right_any = visit(ctx->boolTerm(i + 1));

            if (!right_any.has_value()) {
                throw std::runtime_error("visitBoolExpression: right_any has no value!");
            }

            auto right = std::any_cast<std::shared_ptr<Expression>>(right_any);
            if (!right) {
                throw std::runtime_error("visitBoolExpression: Failed to retrieve right expression");
            }

            left = std::make_shared<BinaryExpr>(
                    ctx->getStart()->getLine(),
                    ctx->getStart()->getCharPositionInLine(),
                    left, "||", right
            );
        }

        return std::make_any<std::shared_ptr<Expression>>(left);
    }

    antlrcpp::Any ASTBuilderVisitor::visitLvalue(GoliteParser::LvalueContext *ctx) {
        return visit(ctx->selectorTerm());
    }

    antlrcpp::Any ASTBuilderVisitor::visitBoolTerm(GoliteParser::BoolTermContext *ctx) {
        if (!ctx->LOGICAL_AND().empty()) {
            auto left = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->equalTerm(0)));
            auto right = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->equalTerm(1)));

            return std::static_pointer_cast<Expression>(
                    std::make_shared<BinaryExpr>(
                            ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                            std::move(left), "&&", std::move(right)
                    )
            );
        }
        return visit(ctx->equalTerm(0));
    }

    antlrcpp::Any ASTBuilderVisitor::visitRelationTerm(GoliteParser::RelationTermContext *ctx) {
        if (!ctx->LESS().empty() || !ctx->GREATER().empty() ||
            !ctx->LESS_OR_EQUALS().empty() || !ctx->GREATER_OR_EQUALS().empty()) {

            auto left_any = visit(ctx->arithmeticExpression(0));
            if (!left_any.has_value()) {
                throw std::runtime_error("visitRelationTerm: left_any has no value!");
            }
            auto left = std::any_cast<std::shared_ptr<Expression>>(left_any);

            for (size_t i = 0; i < ctx->arithmeticExpression().size() - 1; i++) {
                auto right_any = visit(ctx->arithmeticExpression(i + 1));
                if (!right_any.has_value()) {
                    throw std::runtime_error("visitRelationTerm: right_any has no value!");
                }
                auto right = std::any_cast<std::shared_ptr<Expression>>(right_any);

                std::string op;
                if (ctx->LESS(i)) op = "<";
                else if (ctx->GREATER(i)) op = ">";
                else if (ctx->LESS_OR_EQUALS(i)) op = "<=";
                else if (ctx->GREATER_OR_EQUALS(i)) op = ">=";

                left = std::make_shared<BinaryExpr>(
                        ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                        left, op, right
                );
            }

            return std::make_any<std::shared_ptr<Expression>>(left);
        }

        return visit(ctx->arithmeticExpression(0));
    }



    antlrcpp::Any ASTBuilderVisitor::visitSimpleTerm(GoliteParser::SimpleTermContext *ctx) {
        auto left_any = visit(ctx->term(0));
        auto left = std::any_cast<std::shared_ptr<Expression>>(left_any);

        for (size_t i = 0; i < ctx->PLUS().size() + ctx->MINUS().size(); ++i) {
            std::string op;
            if (ctx->PLUS(i)) op = "+";
            else if (ctx->MINUS(i)) op = "-";

            auto right_any = visit(ctx->term(i + 1));
            auto right = std::any_cast<std::shared_ptr<Expression>>(right_any);

            left = std::static_pointer_cast<Expression>(std::make_shared<BinaryExpr>(
                    ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                    std::move(left), op, std::move(right)
            ));
        }

        return left;
    }



    antlrcpp::Any ASTBuilderVisitor::visitEqualTerm(GoliteParser::EqualTermContext *ctx) {
        if (!ctx->EQUALS().empty() || !ctx->NOT_EQUALS().empty()) {
            std::string op = !ctx->EQUALS().empty() ? "==" : "!=";

            auto left = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->relationTerm(0)));
            auto right = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->relationTerm(1)));

            return std::static_pointer_cast<Expression>(
                    std::make_shared<BinaryExpr>(
                            ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                            std::move(left), op, std::move(right)
                    )
            );
        }

        return visit(ctx->relationTerm(0));
    }

    antlrcpp::Any ASTBuilderVisitor::visitTerm(GoliteParser::TermContext *ctx) {
        if (!ctx->STAR().empty() || !ctx->DIV().empty()) { // Check for * or /
            std::string op = !ctx->STAR().empty() ? "*" : "/";

            auto left = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->unaryTerm(0)));
            auto right = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->unaryTerm(1)));

            return std::static_pointer_cast<Expression>(
                    std::make_shared<BinaryExpr>(
                            ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                            std::move(left), op, std::move(right)
                    )
            );
        }

        return visit(ctx->unaryTerm(0));
    }



    antlrcpp::Any ASTBuilderVisitor::visitSelectorTerm(GoliteParser::SelectorTermContext *ctx) {
        // Base expression (factor) → e.g., "current" in "current.next"
        auto base = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->factor()));
        if (ctx->DOT().empty()) {
            return base;
        }

        // Process each field access (e.g., `current.next.val`)
        for (size_t i = 0; i < ctx->DOT().size(); i++) {
            base = std::make_shared<FieldExpr>(
                    ctx->DOT(i)->getSymbol()->getLine(),
                    ctx->DOT(i)->getSymbol()->getCharPositionInLine(),
                    base,
                    ctx->ID(i)->getText()
            );
        }

        return base;
    }




    antlrcpp::Any ASTBuilderVisitor::visitExpression(GoliteParser::ExpressionContext *ctx) {
        if (ctx->boolExpression()) {
            return visit(ctx->boolExpression());
        } else if (ctx->arithmeticExpression()) {
            return visit(ctx->arithmeticExpression());
        }

        throw std::runtime_error("visitExpression: Invalid expression structure.");
    }




    antlrcpp::Any ASTBuilderVisitor::visitUnaryTerm(GoliteParser::UnaryTermContext *ctx) {

        if (ctx->EXCLAMATION() || ctx->MINUS()) {
            std::string op = ctx->EXCLAMATION() ? "!" : "-";
            auto operand = std::any_cast<std::shared_ptr<Expression>>(visit(ctx->unaryTerm()));

            return std::static_pointer_cast<Expression>(
                    std::make_shared<UnaryExpr>(
                            ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                            op, std::move(operand)
                    )
            );
        }
        return visit(ctx->selectorTerm());
    }

    antlrcpp::Any ASTBuilderVisitor::visitFactor(GoliteParser::FactorContext *ctx) {

        // Handling 'new' expressions
        if(ctx->NEW() && ctx->ID()){
            std::string typeName = ctx->ID()->getText();
            return std::static_pointer_cast<Expression>(
                    std::make_shared<NewExpr>(ctx->getStart()->getLine(),
                                              ctx->getStart()->getCharPositionInLine(),
                                              typeName));
        }

        // Handling parenthesized expressions (e.g., `(x + 1)`)
        if (ctx->expression()) {
            return visit(ctx->expression());
        }

        // Handling numbers
        if (ctx->NUMBER()) {
            return std::static_pointer_cast<Expression>(
                    std::make_shared<IntegerLiteral>(
                            ctx->getStart()->getLine(),
                            ctx->getStart()->getCharPositionInLine(),
                            std::stoi(ctx->NUMBER()->getText())
                    )
            );
        }

        // Handling identifiers (variable, function call, OR struct field access)
        if (ctx->ID()) {
            std::string name = ctx->ID()->getText();

            // Check if it's a function call (has arguments)
            if (ctx->arguments()) {
                std::vector<std::shared_ptr<Expression>> args;

                for (size_t i = 0; i < ctx->arguments()->expression().size(); i++) {
                    auto argCtx = ctx->arguments()->expression(i);
                    auto any_result = visit(argCtx);

                    try {
                        auto expr = std::any_cast<std::shared_ptr<Expression>>(any_result);
                        args.push_back(std::move(expr));
                    } catch (const std::bad_any_cast& e) {
                        std::cerr << "ERROR: Failed to cast function argument " << i
                                  << ". Actual type: " << any_result.type().name()
                                  << ". Exception: " << e.what() << std::endl;
                        throw;
                    }
                }

                return std::static_pointer_cast<Expression>(
                        std::make_shared<FunctionCallExpr>(
                                ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
                                ctx->ID()->getText(), std::move(args)
                        )
                );
            }

            // Otherwise, it's a variable
            return std::static_pointer_cast<Expression>(
                    std::make_shared<VariableExpr>(
                            ctx->getStart()->getLine(),
                            ctx->getStart()->getCharPositionInLine(),
                            name
                    )
            );
        }

        // Handling boolean literals
        if (ctx->TRUE() || ctx->FALSE()) {
            return std::static_pointer_cast<Expression>(
                    std::make_shared<BooleanLiteral>(
                            ctx->getStart()->getLine(),
                            ctx->getStart()->getCharPositionInLine(),
                            ctx->TRUE() != nullptr
                    )
            );
        }

        if (ctx->NIL()) {
            return std::static_pointer_cast<Expression>(
                    std::make_shared<NilExpr>(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine())
            );
        }

        std::cerr << "Error: Unknown factor type!" << std::endl;
        throw std::runtime_error("visitFactor: Unhandled case in factor parsing");
    }




} // namespace ast
