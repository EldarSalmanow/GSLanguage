#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    Void GS_Visitor::SuperNode(LRef<GSNodePtr> node,
                               LRef<Driver::GS_Session> session) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return VisitDeclaration(declaration, session);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return VisitStatement(statement, session);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return VisitExpression(expression, session);
        }
    }

    Void GS_Visitor::SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                      LRef<Driver::GS_Session> session) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return VisitTranslationUnitDeclaration(translationUnitDeclaration, session);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return VisitFunctionDeclaration(functionDeclaration, session);
            }
        }
    }

    Void GS_Visitor::SuperStatement(LRef<GSStatementPtr> statement,
                                    LRef<Driver::GS_Session> session) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return VisitVariableDeclarationStatement(variableDeclarationStatement, session);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return VisitAssignmentStatement(assignmentStatement, session);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return VisitExpressionStatement(expressionStatement, session);
            }
        }
    }

    Void GS_Visitor::SuperExpression(LRef<GSExpressionPtr> expression,
                                     LRef<Driver::GS_Session> session) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return VisitConstantExpression(constantExpression, session);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return VisitUnaryExpression(unaryExpression, session);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return VisitBinaryExpression(binaryExpression, session);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return VisitVariableUsingExpression(variableUsingExpression, session);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return VisitFunctionCallingExpression(functionCallingExpression, session);
            }
        }
    }

    Void GS_Visitor::SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                     LRef<Driver::GS_Session> session) {
        auto nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            VisitNode(node, session);
        }
    }

    Void GS_Visitor::SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                              LRef<Driver::GS_Session> session) {
        auto statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            VisitStatement(statement, session);
        }
    }

    Void GS_Visitor::SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                       LRef<Driver::GS_Session> session) {
        auto expression = variableDeclarationStatement->GetExpression();

        VisitExpression(expression, session);
    }

    Void GS_Visitor::SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                              LRef<Driver::GS_Session> session) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        VisitExpression(lvalueExpression, session);
        VisitExpression(rvalueExpression, session);
    }

    Void GS_Visitor::SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                              LRef<Driver::GS_Session> session) {
        auto expression = expressionStatement->GetExpression();

        VisitExpression(expression, session);
    }

    Void GS_Visitor::SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                             LRef<Driver::GS_Session> session) {

    }

    Void GS_Visitor::SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                          LRef<Driver::GS_Session> session) {
        auto expression = unaryExpression->GetExpression();

        VisitExpression(expression, session);
    }

    Void GS_Visitor::SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                           LRef<Driver::GS_Session> session) {
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        VisitExpression(firstExpression, session);
        VisitExpression(secondExpression, session);
    }

    Void GS_Visitor::SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                  LRef<Driver::GS_Session> session) {

    }

    Void GS_Visitor::SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                    LRef<Driver::GS_Session> session) {

    }

    Void GS_Visitor::VisitNode(LRef<GSNodePtr> node,
                               LRef<Driver::GS_Session> session) {
        SuperNode(node, session);
    }

    Void GS_Visitor::VisitDeclaration(LRef<GSDeclarationPtr> declaration,
                                      LRef<Driver::GS_Session> session) {
        SuperDeclaration(declaration, session);
    }

    Void GS_Visitor::VisitStatement(LRef<GSStatementPtr> statement,
                                    LRef<Driver::GS_Session> session) {
        SuperStatement(statement, session);
    }

    Void GS_Visitor::VisitExpression(LRef<GSExpressionPtr> expression,
                                     LRef<Driver::GS_Session> session) {
        SuperExpression(expression, session);
    }

    Void GS_Visitor::VisitTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                     LRef<Driver::GS_Session> session) {
        SuperTranslationUnitDeclaration(translationUnitDeclaration, session);
    }

    Void GS_Visitor::VisitFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                              LRef<Driver::GS_Session> session) {
        SuperFunctionDeclaration(functionDeclaration, session);
    }

    Void GS_Visitor::VisitVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                       LRef<Driver::GS_Session> session) {
        SuperVariableDeclarationStatement(variableDeclarationStatement, session);
    }

    Void GS_Visitor::VisitAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                              LRef<Driver::GS_Session> session) {
        SuperAssignmentStatement(assignmentStatement, session);
    }

    Void GS_Visitor::VisitExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                              LRef<Driver::GS_Session> session) {
        SuperExpressionStatement(expressionStatement, session);
    }

    Void GS_Visitor::VisitConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                             LRef<Driver::GS_Session> session) {
        SuperConstantExpression(constantExpression, session);
    }

    Void GS_Visitor::VisitUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                          LRef<Driver::GS_Session> session) {
        SuperUnaryExpression(unaryExpression, session);
    }

    Void GS_Visitor::VisitBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                           LRef<Driver::GS_Session> session) {
        SuperBinaryExpression(binaryExpression, session);
    }

    Void GS_Visitor::VisitVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                  LRef<Driver::GS_Session> session) {
        SuperVariableUsingExpression(variableUsingExpression, session);
    }

    Void GS_Visitor::VisitFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                    LRef<Driver::GS_Session> session) {
        SuperFunctionCallingExpression(functionCallingExpression, session);
    }

    GSNodePtr GS_Transformer::SuperNode(LRef<GSNodePtr> node,
                                        LRef<Driver::GS_Session> session) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return TransformDeclaration(declaration, session);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return TransformStatement(statement, session);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return TransformExpression(expression, session);
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                               LRef<Driver::GS_Session> session) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return TransformTranslationUnitDeclaration(translationUnitDeclaration, session);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return TransformFunctionDeclaration(functionDeclaration, session);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperStatement(LRef<GSStatementPtr> statement,
                                             LRef<Driver::GS_Session> session) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return TransformVariableDeclarationStatement(variableDeclarationStatement, session);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return TransformAssignmentStatement(assignmentStatement, session);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return TransformExpressionStatement(expressionStatement, session);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperExpression(LRef<GSExpressionPtr> expression,
                                              LRef<Driver::GS_Session> session) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return TransformConstantExpression(constantExpression, session);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return TransformUnaryExpression(unaryExpression, session);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return TransformBinaryExpression(binaryExpression, session);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return TransformVariableUsingExpression(variableUsingExpression, session);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return TransformFunctionCallingExpression(functionCallingExpression, session);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                              LRef<Driver::GS_Session> session) {
        auto &nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            auto transformedNode = TransformNode(node, session);

            node.swap(transformedNode);
        }

        return translationUnitDeclaration;
    }

    GSNodePtr GS_Transformer::SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                       LRef<Driver::GS_Session> session) {
        auto &statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            auto transformedStatement = ToStatement(TransformStatement(statement, session));

            statement.swap(transformedStatement);
        }

        return functionDeclaration;
    }

    GSNodePtr GS_Transformer::SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                                LRef<Driver::GS_Session> session) {
        auto &expression = variableDeclarationStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression, session));

        expression.swap(transformedExpression);

        return variableDeclarationStatement;
    }

    GSNodePtr GS_Transformer::SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                       LRef<Driver::GS_Session> session) {
        auto &lvalueExpression = assignmentStatement->GetLValueExpression();
        auto &rvalueExpression = assignmentStatement->GetRValueExpression();

        auto transformedLvalueExpression = ToExpression(TransformExpression(lvalueExpression, session));
        auto transformedRvalueExpression = ToExpression(TransformExpression(rvalueExpression, session));

        lvalueExpression.swap(transformedLvalueExpression);
        rvalueExpression.swap(transformedRvalueExpression);

        return assignmentStatement;
    }

    GSNodePtr GS_Transformer::SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                       LRef<Driver::GS_Session> session) {
        auto &expression = expressionStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression, session));

        expression.swap(transformedExpression);

        return expressionStatement;
    }

    GSNodePtr GS_Transformer::SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                      LRef<Driver::GS_Session> session) {
        return constantExpression;
    }

    GSNodePtr GS_Transformer::SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                                   LRef<Driver::GS_Session> session) {
        auto &expression = unaryExpression->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression, session));

        expression.swap(transformedExpression);

        return unaryExpression;
    }

    GSNodePtr GS_Transformer::SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                                    LRef<Driver::GS_Session> session) {
        auto &firstExpression = binaryExpression->GetFirstExpression();
        auto &secondExpression = binaryExpression->GetSecondExpression();

        auto transformedFirstExpression = ToExpression(TransformExpression(firstExpression, session));
        auto transformedSecondExpression = ToExpression(TransformExpression(secondExpression, session));

        firstExpression.swap(transformedFirstExpression);
        secondExpression.swap(transformedSecondExpression);

        return binaryExpression;
    }

    GSNodePtr GS_Transformer::SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                           LRef<Driver::GS_Session> session) {
        return variableUsingExpression;
    }

    GSNodePtr GS_Transformer::SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                             LRef<Driver::GS_Session> session) {
        return functionCallingExpression;
    }

    GSNodePtr GS_Transformer::TransformNode(LRef<GSNodePtr> node,
                                            LRef<Driver::GS_Session> session) {
        return SuperNode(node, session);
    }

    GSNodePtr GS_Transformer::TransformDeclaration(LRef<GSDeclarationPtr> declaration,
                                                   LRef<Driver::GS_Session> session) {
        return SuperDeclaration(declaration, session);
    }

    GSNodePtr GS_Transformer::TransformStatement(LRef<GSStatementPtr> statement,
                                                 LRef<Driver::GS_Session> session) {
        return SuperStatement(statement, session);
    }

    GSNodePtr GS_Transformer::TransformExpression(LRef<GSExpressionPtr> expression,
                                                  LRef<Driver::GS_Session> session) {
        return SuperExpression(expression, session);
    }

    GSNodePtr GS_Transformer::TransformTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                                  LRef<Driver::GS_Session> session) {
        return SuperTranslationUnitDeclaration(translationUnitDeclaration, session);
    }

    GSNodePtr GS_Transformer::TransformFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                           LRef<Driver::GS_Session> session) {
        return SuperFunctionDeclaration(functionDeclaration, session);
    }

    GSNodePtr GS_Transformer::TransformVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                                    LRef<Driver::GS_Session> session) {
        return SuperVariableDeclarationStatement(variableDeclarationStatement, session);
    }

    GSNodePtr GS_Transformer::TransformAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                           LRef<Driver::GS_Session> session) {
        return SuperAssignmentStatement(assignmentStatement, session);
    }

    GSNodePtr GS_Transformer::TransformExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                           LRef<Driver::GS_Session> session) {
        return SuperExpressionStatement(expressionStatement, session);
    }

    GSNodePtr GS_Transformer::TransformConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                          LRef<Driver::GS_Session> session) {
        return SuperConstantExpression(constantExpression, session);
    }

    GSNodePtr GS_Transformer::TransformUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                                       LRef<Driver::GS_Session> session) {
        return SuperUnaryExpression(unaryExpression, session);
    }

    GSNodePtr GS_Transformer::TransformBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                                        LRef<Driver::GS_Session> session) {
        return SuperBinaryExpression(binaryExpression, session);
    }

    GSNodePtr GS_Transformer::TransformVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                               LRef<Driver::GS_Session> session) {
        return SuperVariableUsingExpression(variableUsingExpression, session);
    }

    GSNodePtr GS_Transformer::TransformFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                                 LRef<Driver::GS_Session> session) {
        return SuperFunctionCallingExpression(functionCallingExpression, session);
    }

}
