#include <AST/AST.h>

namespace GSLanguageCompiler::AST {

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) {
        auto &body = functionDeclaration->getBody();

        for (auto &statement : body) {
            auto transformedStatement = std::reinterpret_pointer_cast<GS_Statement>(Accept(this, statement));

            statement.swap(transformedStatement);
        }

        return functionDeclaration;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto &expression = variableDeclarationStatement->getExpression();

        auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, expression));

        expression.swap(transformedExpression);

        return variableDeclarationStatement;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) {
        auto &lvalueExpression = assignmentStatement->getLValueExpression();
        auto &rvalueExpression = assignmentStatement->getRValueExpression();

        auto lvalueTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, lvalueExpression));
        auto rvalueTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, rvalueExpression));

        lvalueExpression.swap(lvalueTransformedExpression);
        rvalueExpression.swap(rvalueTransformedExpression);

        return assignmentStatement;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_ExpressionStatement> expressionStatement) {
        auto &expression = expressionStatement->getExpression();

        auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, expression));

        expression.swap(transformedExpression);

        return expressionStatement;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_ConstantExpression> constantExpression) {
        return constantExpression;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_UnaryExpression> unaryExpression) {
        auto &expression = unaryExpression->getExpression();

        auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, expression));

        expression.swap(transformedExpression);

        return unaryExpression;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_BinaryExpression> binaryExpression) {
        auto &firstExpression = binaryExpression->getFirstExpression();
        auto &secondExpression = binaryExpression->getSecondExpression();

        auto firstTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, firstExpression));
        auto secondTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, secondExpression));

        firstExpression.swap(firstTransformedExpression);
        secondExpression.swap(secondTransformedExpression);

        return binaryExpression;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) {
        return variableUsingExpression;
    }

    GSNodePtr GS_Transformer::visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) {
        auto &params = functionCallingExpression->getParams();

        for (auto &expression : params) {
            auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(Accept(this, expression));

            expression.swap(transformedExpression);
        }

        return functionCallingExpression;
    }

}
