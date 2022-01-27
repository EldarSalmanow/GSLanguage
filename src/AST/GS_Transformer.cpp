#include <AST/AST.h>

namespace GSLanguageCompiler::AST {

    GS_Transformer::~GS_Transformer() = default;

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

    GSNodePtr GS_Transformer::visit(ConstLRef<GSNodePtr> node) {
        if (node->isDeclaration()) {
            auto declaration = std::reinterpret_pointer_cast<GS_Declaration>(node);

            switch (declaration->getDeclarationType()) {
                case DeclarationType::FunctionDeclaration:
                    return this->visit(std::reinterpret_pointer_cast<GS_FunctionDeclaration>(declaration));
            }
        }

        if (node->isStatement()) {
            auto statement = std::reinterpret_pointer_cast<GS_Statement>(node);

            switch (statement->getStatementType()) {
                case StatementType::VariableDeclarationStatement:
                    return this->visit(std::reinterpret_pointer_cast<GS_VariableDeclarationStatement>(statement));
                case StatementType::AssignmentStatement:
                    return this->visit(std::reinterpret_pointer_cast<GS_AssignmentStatement>(statement));
                case StatementType::ExpressionStatement:
                    return this->visit(std::reinterpret_pointer_cast<GS_ExpressionStatement>(statement));
            }
        }

        if (node->isExpression()) {
            auto expression = std::reinterpret_pointer_cast<GS_Expression>(node);

            switch (expression->getExpressionType()) {
                case ExpressionType::ConstantExpression:
                    return this->visit(std::reinterpret_pointer_cast<GS_ConstantExpression>(expression));
                case ExpressionType::UnaryExpression:
                    return this->visit(std::reinterpret_pointer_cast<GS_UnaryExpression>(expression));
                case ExpressionType::BinaryExpression:
                    return this->visit(std::reinterpret_pointer_cast<GS_BinaryExpression>(expression));
                case ExpressionType::VariableUsingExpression:
                    return this->visit(std::reinterpret_pointer_cast<GS_VariableUsingExpression>(expression));
                case ExpressionType::FunctionCallingExpression:
                    return this->visit(std::reinterpret_pointer_cast<GS_FunctionCallingExpression>(expression));
            }
        }
    }

}
