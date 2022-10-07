#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    Void GS_Visitor::SuperNode(LRef<GSNodePtr> node,
                               LRef<Driver::GSContextPtr> context) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return VisitDeclaration(declaration, context);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return VisitStatement(statement, context);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return VisitExpression(expression, context);
        }
    }

    Void GS_Visitor::SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                      LRef<Driver::GSContextPtr> context) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return VisitTranslationUnitDeclaration(translationUnitDeclaration, context);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return VisitFunctionDeclaration(functionDeclaration, context);
            }
        }
    }

    Void GS_Visitor::SuperStatement(LRef<GSStatementPtr> statement,
                                    LRef<Driver::GSContextPtr> context) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return VisitVariableDeclarationStatement(variableDeclarationStatement, context);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return VisitAssignmentStatement(assignmentStatement, context);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return VisitExpressionStatement(expressionStatement, context);
            }
        }
    }

    Void GS_Visitor::SuperExpression(LRef<GSExpressionPtr> expression,
                                     LRef<Driver::GSContextPtr> context) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return VisitConstantExpression(constantExpression, context);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return VisitUnaryExpression(unaryExpression, context);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return VisitBinaryExpression(binaryExpression, context);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return VisitVariableUsingExpression(variableUsingExpression, context);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return VisitFunctionCallingExpression(functionCallingExpression, context);
            }
        }
    }

    Void GS_Visitor::SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                     LRef<Driver::GSContextPtr> context) {
        auto nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            VisitNode(node, context);
        }
    }

    Void GS_Visitor::SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                              LRef<Driver::GSContextPtr> context) {
        auto statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            VisitStatement(statement, context);
        }
    }

    Void GS_Visitor::SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                       LRef<Driver::GSContextPtr> context) {
        auto expression = variableDeclarationStatement->GetExpression();

        VisitExpression(expression, context);
    }

    Void GS_Visitor::SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                              LRef<Driver::GSContextPtr> context) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        VisitExpression(lvalueExpression, context);
        VisitExpression(rvalueExpression, context);
    }

    Void GS_Visitor::SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                              LRef<Driver::GSContextPtr> context) {
        auto expression = expressionStatement->GetExpression();

        VisitExpression(expression, context);
    }

    Void GS_Visitor::SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                             LRef<Driver::GSContextPtr> context) {

    }

    Void GS_Visitor::SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                          LRef<Driver::GSContextPtr> context) {
        auto expression = unaryExpression->GetExpression();

        VisitExpression(expression, context);
    }

    Void GS_Visitor::SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                           LRef<Driver::GSContextPtr> context) {
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        VisitExpression(firstExpression, context);
        VisitExpression(secondExpression, context);
    }

    Void GS_Visitor::SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                  LRef<Driver::GSContextPtr> context) {

    }

    Void GS_Visitor::SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                    LRef<Driver::GSContextPtr> context) {

    }

    Void GS_Visitor::VisitNode(LRef<GSNodePtr> node,
                               LRef<Driver::GSContextPtr> context) {
        SuperNode(node, context);
    }

    Void GS_Visitor::VisitDeclaration(LRef<GSDeclarationPtr> declaration,
                                      LRef<Driver::GSContextPtr> context) {
        SuperDeclaration(declaration, context);
    }

    Void GS_Visitor::VisitStatement(LRef<GSStatementPtr> statement,
                                    LRef<Driver::GSContextPtr> context) {
        SuperStatement(statement, context);
    }

    Void GS_Visitor::VisitExpression(LRef<GSExpressionPtr> expression,
                                     LRef<Driver::GSContextPtr> context) {
        SuperExpression(expression, context);
    }

    Void GS_Visitor::VisitTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                     LRef<Driver::GSContextPtr> context) {
        SuperTranslationUnitDeclaration(translationUnitDeclaration, context);
    }

    Void GS_Visitor::VisitFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                              LRef<Driver::GSContextPtr> context) {
        SuperFunctionDeclaration(functionDeclaration, context);
    }

    Void GS_Visitor::VisitVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                       LRef<Driver::GSContextPtr> context) {
        SuperVariableDeclarationStatement(variableDeclarationStatement, context);
    }

    Void GS_Visitor::VisitAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                              LRef<Driver::GSContextPtr> context) {
        SuperAssignmentStatement(assignmentStatement, context);
    }

    Void GS_Visitor::VisitExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                              LRef<Driver::GSContextPtr> context) {
        SuperExpressionStatement(expressionStatement, context);
    }

    Void GS_Visitor::VisitConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                             LRef<Driver::GSContextPtr> context) {
        SuperConstantExpression(constantExpression, context);
    }

    Void GS_Visitor::VisitUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                          LRef<Driver::GSContextPtr> context) {
        SuperUnaryExpression(unaryExpression, context);
    }

    Void GS_Visitor::VisitBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                           LRef<Driver::GSContextPtr> context) {
        SuperBinaryExpression(binaryExpression, context);
    }

    Void GS_Visitor::VisitVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                  LRef<Driver::GSContextPtr> context) {
        SuperVariableUsingExpression(variableUsingExpression, context);
    }

    Void GS_Visitor::VisitFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                    LRef<Driver::GSContextPtr> context) {
        SuperFunctionCallingExpression(functionCallingExpression, context);
    }

    GSNodePtr GS_Transformer::SuperNode(LRef<GSNodePtr> node,
                                        LRef<Driver::GSContextPtr> context) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return TransformDeclaration(declaration, context);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return TransformStatement(statement, context);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return TransformExpression(expression, context);
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                               LRef<Driver::GSContextPtr> context) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return TransformTranslationUnitDeclaration(translationUnitDeclaration, context);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return TransformFunctionDeclaration(functionDeclaration, context);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperStatement(LRef<GSStatementPtr> statement,
                                             LRef<Driver::GSContextPtr> context) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return TransformVariableDeclarationStatement(variableDeclarationStatement, context);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return TransformAssignmentStatement(assignmentStatement, context);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return TransformExpressionStatement(expressionStatement, context);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperExpression(LRef<GSExpressionPtr> expression,
                                              LRef<Driver::GSContextPtr> context) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return TransformConstantExpression(constantExpression, context);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return TransformUnaryExpression(unaryExpression, context);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return TransformBinaryExpression(binaryExpression, context);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return TransformVariableUsingExpression(variableUsingExpression, context);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return TransformFunctionCallingExpression(functionCallingExpression, context);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                              LRef<Driver::GSContextPtr> context) {
        auto &nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            auto transformedNode = TransformNode(node, context);

            node.swap(transformedNode);
        }

        return translationUnitDeclaration;
    }

    GSNodePtr GS_Transformer::SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                       LRef<Driver::GSContextPtr> context) {
        auto &statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            auto transformedStatement = ToStatement(TransformStatement(statement, context));

            statement.swap(transformedStatement);
        }

        return functionDeclaration;
    }

    GSNodePtr GS_Transformer::SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                                LRef<Driver::GSContextPtr> context) {
        auto &expression = variableDeclarationStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression, context));

        expression.swap(transformedExpression);

        return variableDeclarationStatement;
    }

    GSNodePtr GS_Transformer::SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                       LRef<Driver::GSContextPtr> context) {
        auto &lvalueExpression = assignmentStatement->GetLValueExpression();
        auto &rvalueExpression = assignmentStatement->GetRValueExpression();

        auto transformedLvalueExpression = ToExpression(TransformExpression(lvalueExpression, context));
        auto transformedRvalueExpression = ToExpression(TransformExpression(rvalueExpression, context));

        lvalueExpression.swap(transformedLvalueExpression);
        rvalueExpression.swap(transformedRvalueExpression);

        return assignmentStatement;
    }

    GSNodePtr GS_Transformer::SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                       LRef<Driver::GSContextPtr> context) {
        auto &expression = expressionStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression, context));

        expression.swap(transformedExpression);

        return expressionStatement;
    }

    GSNodePtr GS_Transformer::SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                      LRef<Driver::GSContextPtr> context) {
        return constantExpression;
    }

    GSNodePtr GS_Transformer::SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                                   LRef<Driver::GSContextPtr> context) {
        auto &expression = unaryExpression->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression, context));

        expression.swap(transformedExpression);

        return unaryExpression;
    }

    GSNodePtr GS_Transformer::SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                                    LRef<Driver::GSContextPtr> context) {
        auto &firstExpression = binaryExpression->GetFirstExpression();
        auto &secondExpression = binaryExpression->GetSecondExpression();

        auto transformedFirstExpression = ToExpression(TransformExpression(firstExpression, context));
        auto transformedSecondExpression = ToExpression(TransformExpression(secondExpression, context));

        firstExpression.swap(transformedFirstExpression);
        secondExpression.swap(transformedSecondExpression);

        return binaryExpression;
    }

    GSNodePtr GS_Transformer::SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                           LRef<Driver::GSContextPtr> context) {
        return variableUsingExpression;
    }

    GSNodePtr GS_Transformer::SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                             LRef<Driver::GSContextPtr> context) {
        return functionCallingExpression;
    }

    GSNodePtr GS_Transformer::TransformNode(LRef<GSNodePtr> node,
                                            LRef<Driver::GSContextPtr> context) {
        return SuperNode(node, context);
    }

    GSNodePtr GS_Transformer::TransformDeclaration(LRef<GSDeclarationPtr> declaration,
                                                   LRef<Driver::GSContextPtr> context) {
        return SuperDeclaration(declaration, context);
    }

    GSNodePtr GS_Transformer::TransformStatement(LRef<GSStatementPtr> statement,
                                                 LRef<Driver::GSContextPtr> context) {
        return SuperStatement(statement, context);
    }

    GSNodePtr GS_Transformer::TransformExpression(LRef<GSExpressionPtr> expression,
                                                  LRef<Driver::GSContextPtr> context) {
        return SuperExpression(expression, context);
    }

    GSNodePtr GS_Transformer::TransformTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                                  LRef<Driver::GSContextPtr> context) {
        return SuperTranslationUnitDeclaration(translationUnitDeclaration, context);
    }

    GSNodePtr GS_Transformer::TransformFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                           LRef<Driver::GSContextPtr> context) {
        return SuperFunctionDeclaration(functionDeclaration, context);
    }

    GSNodePtr GS_Transformer::TransformVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                                    LRef<Driver::GSContextPtr> context) {
        return SuperVariableDeclarationStatement(variableDeclarationStatement, context);
    }

    GSNodePtr GS_Transformer::TransformAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                           LRef<Driver::GSContextPtr> context) {
        return SuperAssignmentStatement(assignmentStatement, context);
    }

    GSNodePtr GS_Transformer::TransformExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                           LRef<Driver::GSContextPtr> context) {
        return SuperExpressionStatement(expressionStatement, context);
    }

    GSNodePtr GS_Transformer::TransformConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                          LRef<Driver::GSContextPtr> context) {
        return SuperConstantExpression(constantExpression, context);
    }

    GSNodePtr GS_Transformer::TransformUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                                       LRef<Driver::GSContextPtr> context) {
        return SuperUnaryExpression(unaryExpression, context);
    }

    GSNodePtr GS_Transformer::TransformBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                                        LRef<Driver::GSContextPtr> context) {
        return SuperBinaryExpression(binaryExpression, context);
    }

    GSNodePtr GS_Transformer::TransformVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                               LRef<Driver::GSContextPtr> context) {
        return SuperVariableUsingExpression(variableUsingExpression, context);
    }

    GSNodePtr GS_Transformer::TransformFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                                 LRef<Driver::GSContextPtr> context) {
        return SuperFunctionCallingExpression(functionCallingExpression, context);
    }

}
