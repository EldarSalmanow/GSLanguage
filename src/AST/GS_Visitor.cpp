#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    GS_Visitor::~GS_Visitor() = default;

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
            case ExpressionType::ArrayExpression: {
                auto arrayExpression = ToExpression<GS_ArrayExpression>(expression);

                return VisitArrayExpression(session,
                                            arrayExpression);
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

    GS_Transformer::~GS_Transformer() = default;

    GSNodePtr GS_Transformer::SuperNode(LRef<Driver::GS_Session> session,
                                        LRef<GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return TransformDeclaration(session,
                                        declaration);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return TransformStatement(session,
                                      statement);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return TransformExpression(session,
                                       expression);
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperDeclaration(LRef<Driver::GS_Session> session,
                                               LRef<GSDeclarationPtr> declaration) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return TransformTranslationUnitDeclaration(session,
                                                           translationUnitDeclaration);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return TransformFunctionDeclaration(session,
                                                    functionDeclaration);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperStatement(LRef<Driver::GS_Session> session,
                                             LRef<GSStatementPtr> statement) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return TransformVariableDeclarationStatement(session,
                                                             variableDeclarationStatement);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return TransformAssignmentStatement(session,
                                                    assignmentStatement);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return TransformExpressionStatement(session,
                                                    expressionStatement);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperExpression(LRef<Driver::GS_Session> session,
                                              LRef<GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return TransformConstantExpression(session,
                                                   constantExpression);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return TransformUnaryExpression(session,
                                                unaryExpression);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return TransformBinaryExpression(session,
                                                 binaryExpression);
            }
            case ExpressionType::ArrayExpression: {
                auto arrayExpression = ToExpression<GS_ArrayExpression>(expression);

                return TransformArrayExpression(session,
                                                arrayExpression);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return TransformVariableUsingExpression(session,
                                                        variableUsingExpression);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return TransformFunctionCallingExpression(session,
                                                          functionCallingExpression);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                              NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto &nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            auto transformedNode = TransformNode(session,
                                                 node);

            node.swap(transformedNode);
        }

        return translationUnitDeclaration;
    }

    GSNodePtr GS_Transformer::SuperFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        auto &statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            auto transformedStatement = ToStatement(TransformStatement(session,
                                                                       statement));

            statement.swap(transformedStatement);
        }

        return functionDeclaration;
    }

    GSNodePtr GS_Transformer::SuperVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto &expression = variableDeclarationStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return variableDeclarationStatement;
    }

    GSNodePtr GS_Transformer::SuperAssignmentStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        auto &lvalueExpression = assignmentStatement->GetLValueExpression();
        auto &rvalueExpression = assignmentStatement->GetRValueExpression();

        auto transformedLvalueExpression = ToExpression(TransformExpression(session,
                                                                            lvalueExpression));
        auto transformedRvalueExpression = ToExpression(TransformExpression(session,
                                                                            rvalueExpression));

        lvalueExpression.swap(transformedLvalueExpression);
        rvalueExpression.swap(transformedRvalueExpression);

        return assignmentStatement;
    }

    GSNodePtr GS_Transformer::SuperExpressionStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        auto &expression = expressionStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return expressionStatement;
    }

    GSNodePtr GS_Transformer::SuperConstantExpression(LRef<Driver::GS_Session> session,
                                                      NodePtrLRef<GS_ConstantExpression> constantExpression) {
        return constantExpression;
    }

    GSNodePtr GS_Transformer::SuperUnaryExpression(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        auto &expression = unaryExpression->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return unaryExpression;
    }

    GSNodePtr GS_Transformer::SuperBinaryExpression(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        auto &firstExpression = binaryExpression->GetFirstExpression();
        auto &secondExpression = binaryExpression->GetSecondExpression();

        auto transformedFirstExpression = ToExpression(TransformExpression(session,
                                                                           firstExpression));
        auto transformedSecondExpression = ToExpression(TransformExpression(session,
                                                                            secondExpression));

        firstExpression.swap(transformedFirstExpression);
        secondExpression.swap(transformedSecondExpression);

        return binaryExpression;
    }

    GSNodePtr GS_Transformer::SuperArrayExpression(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        auto &expressions = arrayExpression->GetExpressions();

        for (auto &expression : expressions) {
            auto transformedExpression = ToExpression(TransformExpression(session,
                                                                          expression));

            expression.swap(transformedExpression);
        }

        return arrayExpression;
    }

    GSNodePtr GS_Transformer::SuperVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {
        return variableUsingExpression;
    }

    GSNodePtr GS_Transformer::SuperFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                             NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {
        return functionCallingExpression;
    }

    GSNodePtr GS_Transformer::TransformNode(LRef<Driver::GS_Session> session,
                                            LRef<GSNodePtr> node) {
        return SuperNode(session,
                         node);
    }

    GSNodePtr GS_Transformer::TransformDeclaration(LRef<Driver::GS_Session> session,
                                                   LRef<GSDeclarationPtr> declaration) {
        return SuperDeclaration(session,
                                declaration);
    }

    GSNodePtr GS_Transformer::TransformStatement(LRef<Driver::GS_Session> session,
                                                 LRef<GSStatementPtr> statement) {
        return SuperStatement(session,
                              statement);
    }

    GSNodePtr GS_Transformer::TransformExpression(LRef<Driver::GS_Session> session,
                                                  LRef<GSExpressionPtr> expression) {
        return SuperExpression(session,
                               expression);
    }

    GSNodePtr GS_Transformer::TransformTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                                  NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        return SuperTranslationUnitDeclaration(session,
                                               translationUnitDeclaration);
    }

    GSNodePtr GS_Transformer::TransformFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        return SuperFunctionDeclaration(session,
                                        functionDeclaration);
    }

    GSNodePtr GS_Transformer::TransformVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                    NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        return SuperVariableDeclarationStatement(session,
                                                 variableDeclarationStatement);
    }

    GSNodePtr GS_Transformer::TransformAssignmentStatement(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        return SuperAssignmentStatement(session,
                                        assignmentStatement);
    }

    GSNodePtr GS_Transformer::TransformExpressionStatement(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        return SuperExpressionStatement(session,
                                        expressionStatement);
    }

    GSNodePtr GS_Transformer::TransformConstantExpression(LRef<Driver::GS_Session> session,
                                                          NodePtrLRef<GS_ConstantExpression> constantExpression) {
        return SuperConstantExpression(session,
                                       constantExpression);
    }

    GSNodePtr GS_Transformer::TransformUnaryExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        return SuperUnaryExpression(session,
                                    unaryExpression);
    }

    GSNodePtr GS_Transformer::TransformBinaryExpression(LRef<Driver::GS_Session> session,
                                                        NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        return SuperBinaryExpression(session,
                                     binaryExpression);
    }

    GSNodePtr GS_Transformer::TransformArrayExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        return SuperArrayExpression(session,
                                    arrayExpression);
    }

    GSNodePtr GS_Transformer::TransformVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                               NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {
        return SuperVariableUsingExpression(session,
                                            variableUsingExpression);
    }

    GSNodePtr GS_Transformer::TransformFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                                 NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {
        return SuperFunctionCallingExpression(session,
                                              functionCallingExpression);
    }

}
