#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    Void GS_Visitor::SuperNode(LRef<Driver::GS_Session> session,
                               LRef<GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return VisitDeclaration(session,
                                    declaration);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return VisitStatement(session,
                                  statement);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return VisitExpression(session,
                                   expression);
        }
    }

    Void GS_Visitor::SuperDeclaration(LRef<Driver::GS_Session> session,
                                      LRef<GSDeclarationPtr> declaration) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return VisitTranslationUnitDeclaration(session,
                                                       translationUnitDeclaration);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return VisitFunctionDeclaration(session,
                                                functionDeclaration);
            }
        }
    }

    Void GS_Visitor::SuperStatement(LRef<Driver::GS_Session> session,
                                    LRef<GSStatementPtr> statement) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return VisitVariableDeclarationStatement(session,
                                                         variableDeclarationStatement);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return VisitAssignmentStatement(session,
                                                assignmentStatement);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return VisitExpressionStatement(session,
                                                expressionStatement);
            }
        }
    }

    Void GS_Visitor::SuperExpression(LRef<Driver::GS_Session> session,
                                     LRef<GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return VisitConstantExpression(session,
                                               constantExpression);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return VisitUnaryExpression(session,
                                            unaryExpression);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return VisitBinaryExpression(session,
                                             binaryExpression);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return VisitVariableUsingExpression(session,
                                                    variableUsingExpression);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return VisitFunctionCallingExpression(session,
                                                      functionCallingExpression);
            }
        }
    }

    Void GS_Visitor::SuperTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            VisitNode(session,
                      node);
        }
    }

    Void GS_Visitor::SuperFunctionDeclaration(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        auto statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            VisitStatement(session,
                           statement);
        }
    }

    Void GS_Visitor::SuperVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto expression = variableDeclarationStatement->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperAssignmentStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        VisitExpression(session,
                        lvalueExpression);
        VisitExpression(session,
                        rvalueExpression);
    }

    Void GS_Visitor::SuperExpressionStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperConstantExpression(LRef<Driver::GS_Session> session,
                                             NodePtrLRef<GS_ConstantExpression> constantExpression) {

    }

    Void GS_Visitor::SuperUnaryExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperBinaryExpression(LRef<Driver::GS_Session> session,
                                           NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        VisitExpression(session,
                        firstExpression);
        VisitExpression(session,
                        secondExpression);
    }

    Void GS_Visitor::SuperArrayExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        auto expressions = arrayExpression->GetExpressions();

        for (auto &expression : expressions) {
            VisitExpression(session,
                            expression);
        }
    }

    Void GS_Visitor::SuperVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {

    }

    Void GS_Visitor::SuperFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {

    }

    Void GS_Visitor::VisitNode(LRef<Driver::GS_Session> session,
                               LRef<GSNodePtr> node) {
        SuperNode(session,
                  node);
    }

    Void GS_Visitor::VisitDeclaration(LRef<Driver::GS_Session> session,
                                      LRef<GSDeclarationPtr> declaration) {
        SuperDeclaration(session,
                         declaration);
    }

    Void GS_Visitor::VisitStatement(LRef<Driver::GS_Session> session,
                                    LRef<GSStatementPtr> statement) {
        SuperStatement(session,
                       statement);
    }

    Void GS_Visitor::VisitExpression(LRef<Driver::GS_Session> session,
                                     LRef<GSExpressionPtr> expression) {
        SuperExpression(session,
                        expression);
    }

    Void GS_Visitor::VisitTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        SuperTranslationUnitDeclaration(session,
                                        translationUnitDeclaration);
    }

    Void GS_Visitor::VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        SuperFunctionDeclaration(session,
                                 functionDeclaration);
    }

    Void GS_Visitor::VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        SuperVariableDeclarationStatement(session,
                                          variableDeclarationStatement);
    }

    Void GS_Visitor::VisitAssignmentStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        SuperAssignmentStatement(session,
                                 assignmentStatement);
    }

    Void GS_Visitor::VisitExpressionStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        SuperExpressionStatement(session,
                                 expressionStatement);
    }

    Void GS_Visitor::VisitConstantExpression(LRef<Driver::GS_Session> session,
                                             NodePtrLRef<GS_ConstantExpression> constantExpression) {
        SuperConstantExpression(session,
                                constantExpression);
    }

    Void GS_Visitor::VisitUnaryExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        SuperUnaryExpression(session,
                             unaryExpression);
    }

    Void GS_Visitor::VisitBinaryExpression(LRef<Driver::GS_Session> session,
                                           NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        SuperBinaryExpression(session,
                              binaryExpression);
    }

    Void GS_Visitor::VisitArrayExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        SuperArrayExpression(session,
                             arrayExpression);
    }

    Void GS_Visitor::VisitVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {
        SuperVariableUsingExpression(session,
                                     variableUsingExpression);
    }

    Void GS_Visitor::VisitFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {
        SuperFunctionCallingExpression(session,
                                       functionCallingExpression);
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

    GSNodePtr GS_Transformer::SuperArrayExpression(NodePtrLRef<GS_ArrayExpression> arrayExpression,
                                         LRef<Driver::GS_Session> session) {
        auto &expressions = arrayExpression->GetExpressions();

        for (auto &expression : expressions) {
            auto transformedExpression = ToExpression(TransformExpression(expression, session));

            expression.swap(transformedExpression);
        }

        return arrayExpression;
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

    GSNodePtr GS_Transformer::TransformArrayExpression(NodePtrLRef<GS_ArrayExpression> arrayExpression,
                                             LRef<Driver::GS_Session> session) {
        return SuperArrayExpression(arrayExpression, session);
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
