#include <Driver/GS_Session.h>

#include <Passes/GS_TypeInferencePass.h>

namespace GSLanguageCompiler::Semantic {

    GSTypePtr InferType(LRef<Driver::GS_Session> session,
                        LRef<AST::GSExpressionPtr> expression) {
        GSTypePtr expressionType = nullptr;

        switch (expression->GetExpressionType()) {
            case AST::ExpressionType::LiteralExpression: {
                auto literalExpression = AST::ToExpression<AST::GS_LiteralExpression>(expression);

                auto value = literalExpression->GetValue();

                expressionType = value->GetType();

                break;
            }
            case AST::ExpressionType::ArrayExpression: {
                auto arrayExpression = AST::ToExpression<AST::GS_ArrayExpression>(expression);

                auto expressions = arrayExpression->GetExpressions();

                Semantic::GSTypePtr arrayElementsType = InferType(session,
                                                                  expressions[0]);

                for (auto &arrayElement : arrayExpression->GetExpressions()) {
                    if (arrayElementsType != InferType(session,
                                                       arrayElement)) {
                        break;
                    }
                }

                expressionType = session.GetASTContext().GetArrayType(arrayElementsType,
                                                                      expressions.size());

                break;
            }
            case AST::ExpressionType::RangeExpression: {
                auto rangeExpression = AST::ToExpression<AST::GS_RangeExpression>(expression);

                auto startExpressionType = InferType(session,
                                                     rangeExpression->GetStartExpression());
                auto endExpressionType = InferType(session,
                                                   rangeExpression->GetEndExpression());

                if (startExpressionType != endExpressionType) {
                    break;
                }

                expressionType = startExpressionType;

                break;
            }
            case AST::ExpressionType::UnaryExpression: {
                auto unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(expression);

                expressionType = InferType(session,
                                           unaryExpression->GetExpression());

                break;
            }
            case AST::ExpressionType::BinaryExpression: {
                auto binaryExpression = AST::ToExpression<AST::GS_BinaryExpression>(expression);

                auto firstExpressionType = InferType(session,
                                                     binaryExpression->GetFirstExpression());
                auto secondExpressionType = InferType(session,
                                                      binaryExpression->GetSecondExpression());

                if (firstExpressionType == secondExpressionType) {
                    expressionType = firstExpressionType;
                }

                break;
            }
            case AST::ExpressionType::IndexExpression: {
                auto indexExpression = AST::ToExpression<AST::GS_IndexExpression>(expression);

                auto indexExpressionType = InferType(session,
                                                     indexExpression->GetExpression());

                if (auto arrayType = ToType<GS_ArrayType>(indexExpressionType)) {
                    expressionType = arrayType->GetElementsType();
                }

                break;
            }
            case AST::ExpressionType::CastExpression: {
                auto castExpression = AST::ToExpression<AST::GS_CastExpression>(expression);

                expressionType = castExpression->GetType();

                break;
            }
            case AST::ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = AST::ToExpression<AST::GS_VariableUsingExpression>(expression);

                auto name = variableUsingExpression->GetName();

                auto variableSymbol = session.GetTableOfSymbols().GetVariable(name);

                expressionType = variableSymbol->GetType();

                break;
            }
            case AST::ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = AST::ToExpression<AST::GS_FunctionCallingExpression>(expression);

                auto name = functionCallingExpression->GetName();

                auto variableSymbol = session.GetTableOfSymbols().GetFunction(name);

                expressionType = variableSymbol->GetSignature().GetReturnType();

                break;
            }
        }

        return expressionType;
    }

    GS_TypeInferenceVisitor::GS_TypeInferenceVisitor() = default;

    Void GS_TypeInferenceVisitor::VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                           AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) {
        GS_Visitor::VisitFunctionDeclaration(session, functionDeclaration);

        auto &signature = functionDeclaration->GetSignature();
        auto body = functionDeclaration->GetBody();

        if (!signature.GetReturnType()) {
            GSTypePtr returnType = nullptr;

            AST::NodePtrArray<AST::GS_ReturnStatement> returns;

            for (auto &statement : body) {
                if (auto returnStatement = AST::ToStatement<AST::GS_ReturnStatement>(statement)) {
                    returns.emplace_back(returnStatement);
                }
            }

            if (returns.empty()) {
                returnType = session.GetASTContext().GetVoidType();
            } else if (returns.size() == 1) {
                returnType = InferType(session,
                                       returns[0]->GetExpression());
            } else {
                auto firstReturnType = InferType(session,
                                                 returns[0]->GetExpression());

                for (auto &returnStatement : returns) {
                    if (firstReturnType != InferType(session,
                                                     returnStatement->GetExpression())) {
                        break;
                    }
                }

                returnType = firstReturnType;
            }

            auto newSignature = AST::GS_FunctionSignature::Create(signature.GetParams(),
                                                                  returnType,
                                                                  signature.GetQualifiers());

            signature = newSignature;
        }
    }

    Void GS_TypeInferenceVisitor::VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                    AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) {
        GS_Visitor::VisitVariableDeclarationStatement(session,
                                                      variableDeclarationStatement);

        auto &type = variableDeclarationStatement->GetType();
        auto expression = variableDeclarationStatement->GetExpression();

        if (!type) {
            auto expressionType = InferType(session,
                                            expression);

            type.swap(expressionType);
        }
    }

}
