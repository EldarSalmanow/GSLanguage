#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    GS_BaseVisitor::~GS_BaseVisitor() = default;

    Void GS_BaseVisitor::visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) {
        auto body = functionDeclaration->getBody();

        for (auto &statement : body) {
            Accept(this, statement);
        }
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto expression = variableDeclarationStatement->getExpression();

        Accept(this, expression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->getLValueExpression();
        auto rvalueExpression = assignmentStatement->getRValueExpression();

        Accept(this, lvalueExpression);
        Accept(this, rvalueExpression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->getExpression();

        Accept(this, expression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_ConstantExpression> constantExpression) {

    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->getExpression();

        Accept(this, expression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();

        Accept(this, firstExpression);
        Accept(this, secondExpression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) {

    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) {
        auto params = functionCallingExpression->getParams();

        for (auto &expression : params) {
            Accept(this, expression);
        }
    }

    Void GS_BaseVisitor::visit(ConstLRef<GSNodePtr> node) {
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
