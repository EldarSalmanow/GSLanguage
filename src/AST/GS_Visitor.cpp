#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    Void GS_Visitor::VisitNode(LRef<GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return VisitDeclaration(declaration);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return VisitStatement(statement);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return VisitExpression(expression);
        }
    }

    Void GS_Visitor::VisitDeclaration(LRef<GSDeclarationPtr> declaration) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return VisitTranslationUnitDeclaration(translationUnitDeclaration);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return VisitFunctionDeclaration(functionDeclaration);
            }
        }
    }

    Void GS_Visitor::VisitStatement(LRef<GSStatementPtr> statement) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return VisitVariableDeclarationStatement(variableDeclarationStatement);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return VisitAssignmentStatement(assignmentStatement);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return VisitExpressionStatement(expressionStatement);
            }
        }
    }

    Void GS_Visitor::VisitExpression(LRef<GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return VisitConstantExpression(constantExpression);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return VisitUnaryExpression(unaryExpression);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return VisitBinaryExpression(binaryExpression);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return VisitVariableUsingExpression(variableUsingExpression);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return VisitFunctionCallingExpression(functionCallingExpression);
            }
        }
    }

    Void GS_Visitor::VisitTranslationUnitDeclaration(LRef<SharedPtr<GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
        auto nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            VisitNode(node);
        }
    }

    Void GS_Visitor::VisitFunctionDeclaration(LRef<SharedPtr<GS_FunctionDeclaration>> functionDeclaration) {
        auto statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            VisitStatement(statement);
        }
    }

    Void GS_Visitor::VisitVariableDeclarationStatement(LRef<SharedPtr<GS_VariableDeclarationStatement>> variableDeclarationStatement) {
        auto expression = variableDeclarationStatement->GetExpression();

        VisitExpression(expression);
    }

    Void GS_Visitor::VisitAssignmentStatement(LRef<SharedPtr<GS_AssignmentStatement>> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        VisitExpression(lvalueExpression);
        VisitExpression(rvalueExpression);
    }

    Void GS_Visitor::VisitExpressionStatement(LRef<SharedPtr<GS_ExpressionStatement>> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        VisitExpression(expression);
    }

    Void GS_Visitor::VisitConstantExpression(LRef<SharedPtr<GS_ConstantExpression>> constantExpression) {

    }

    Void GS_Visitor::VisitUnaryExpression(LRef<SharedPtr<GS_UnaryExpression>> unaryExpression) {
        auto expression = unaryExpression->GetExpression();

        VisitExpression(expression);
    }

    Void GS_Visitor::VisitBinaryExpression(LRef<SharedPtr<GS_BinaryExpression>> binaryExpression) {
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        VisitExpression(firstExpression);
        VisitExpression(secondExpression);
    }

    Void GS_Visitor::VisitVariableUsingExpression(LRef<SharedPtr<GS_VariableUsingExpression>> variableUsingExpression) {

    }

    Void GS_Visitor::VisitFunctionCallingExpression(LRef<SharedPtr<GS_FunctionCallingExpression>> functionCallingExpression) {

    }

    GSNodePtr GS_Transformer::TransformNode(LRef<GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return TransformDeclaration(declaration);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return TransformStatement(statement);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return TransformExpression(expression);
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::TransformDeclaration(LRef<GSDeclarationPtr> declaration) {
        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return TransformTranslationUnitDeclaration(translationUnitDeclaration);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return TransformFunctionDeclaration(functionDeclaration);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::TransformStatement(LRef<GSStatementPtr> statement) {
        switch (statement->GetStatementType()) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return TransformVariableDeclarationStatement(variableDeclarationStatement);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return TransformAssignmentStatement(assignmentStatement);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return TransformExpressionStatement(expressionStatement);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::TransformExpression(LRef<GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                return TransformConstantExpression(constantExpression);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return TransformUnaryExpression(unaryExpression);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return TransformBinaryExpression(binaryExpression);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return TransformVariableUsingExpression(variableUsingExpression);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return TransformFunctionCallingExpression(functionCallingExpression);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::TransformTranslationUnitDeclaration(LRef<SharedPtr<GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
        auto &nodes = translationUnitDeclaration->GetNodes();

        for (auto &node: nodes) {
            auto transformedNode = TransformNode(node);

            node.swap(transformedNode);
        }

        return translationUnitDeclaration;
    }

    GSNodePtr GS_Transformer::TransformFunctionDeclaration(LRef<SharedPtr<GS_FunctionDeclaration>> functionDeclaration) {
        auto &statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            auto transformedStatement = ToStatement(TransformStatement(statement));

            statement.swap(transformedStatement);
        }

        return functionDeclaration;
    }

    GSNodePtr GS_Transformer::TransformVariableDeclarationStatement(LRef<SharedPtr<GS_VariableDeclarationStatement>> variableDeclarationStatement) {
        auto &expression = variableDeclarationStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression));

        expression.swap(transformedExpression);

        return variableDeclarationStatement;
    }

    GSNodePtr GS_Transformer::TransformAssignmentStatement(LRef<SharedPtr<GS_AssignmentStatement>> assignmentStatement) {
        auto &lvalueExpression = assignmentStatement->GetLValueExpression();
        auto &rvalueExpression = assignmentStatement->GetRValueExpression();

        auto transformedLvalueExpression = ToExpression(TransformExpression(lvalueExpression));
        auto transformedRvalueExpression = ToExpression(TransformExpression(rvalueExpression));

        lvalueExpression.swap(transformedLvalueExpression);
        rvalueExpression.swap(transformedRvalueExpression);

        return assignmentStatement;
    }

    GSNodePtr GS_Transformer::TransformExpressionStatement(LRef<SharedPtr<GS_ExpressionStatement>> expressionStatement) {
        auto &expression = expressionStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression));

        expression.swap(transformedExpression);

        return expressionStatement;
    }

    GSNodePtr GS_Transformer::TransformConstantExpression(LRef<SharedPtr<GS_ConstantExpression>> constantExpression) {
        return constantExpression;
    }

    GSNodePtr GS_Transformer::TransformUnaryExpression(LRef<SharedPtr<GS_UnaryExpression>> unaryExpression) {
        auto &expression = unaryExpression->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(expression));

        expression.swap(transformedExpression);

        return unaryExpression;
    }

    GSNodePtr GS_Transformer::TransformBinaryExpression(LRef<SharedPtr<GS_BinaryExpression>> binaryExpression) {
        auto &firstExpression = binaryExpression->GetFirstExpression();
        auto &secondExpression = binaryExpression->GetSecondExpression();

        auto transformedFirstExpression = ToExpression(TransformExpression(firstExpression));
        auto transformedSecondExpression = ToExpression(TransformExpression(secondExpression));

        firstExpression.swap(transformedFirstExpression);
        secondExpression.swap(transformedSecondExpression);

        return binaryExpression;
    }

    GSNodePtr GS_Transformer::TransformVariableUsingExpression(LRef<SharedPtr<GS_VariableUsingExpression>> variableUsingExpression) {
        return variableUsingExpression;
    }

    GSNodePtr GS_Transformer::TransformFunctionCallingExpression(LRef<SharedPtr<GS_FunctionCallingExpression>> functionCallingExpression) {
        return functionCallingExpression;
    }

}
