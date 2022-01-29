#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    GS_BaseVisitor::~GS_BaseVisitor() = default;

    Void GS_BaseVisitor::visit(ConstLRef<GSNodePtr> node) {
        if (node->isDeclaration()) {
            auto declaration = std::reinterpret_pointer_cast<GS_Declaration>(node);

            switch (declaration->getDeclarationType()) {
                case DeclarationType::TranslationUnitDeclaration:
                    return visit(std::reinterpret_pointer_cast<GS_TranslationUnitDeclaration>(declaration));
                case DeclarationType::FunctionDeclaration:
                    return visit(std::reinterpret_pointer_cast<GS_FunctionDeclaration>(declaration));
            }
        }

        if (node->isStatement()) {
            auto statement = std::reinterpret_pointer_cast<GS_Statement>(node);

            switch (statement->getStatementType()) {
                case StatementType::VariableDeclarationStatement:
                    return visit(std::reinterpret_pointer_cast<GS_VariableDeclarationStatement>(statement));
                case StatementType::AssignmentStatement:
                    return visit(std::reinterpret_pointer_cast<GS_AssignmentStatement>(statement));
                case StatementType::ExpressionStatement:
                    return visit(std::reinterpret_pointer_cast<GS_ExpressionStatement>(statement));
            }
        }

        if (node->isExpression()) {
            auto expression = std::reinterpret_pointer_cast<GS_Expression>(node);

            switch (expression->getExpressionType()) {
                case ExpressionType::ConstantExpression:
                    return visit(std::reinterpret_pointer_cast<GS_ConstantExpression>(expression));
                case ExpressionType::UnaryExpression:
                    return visit(std::reinterpret_pointer_cast<GS_UnaryExpression>(expression));
                case ExpressionType::BinaryExpression:
                    return visit(std::reinterpret_pointer_cast<GS_BinaryExpression>(expression));
                case ExpressionType::VariableUsingExpression:
                    return visit(std::reinterpret_pointer_cast<GS_VariableUsingExpression>(expression));
                case ExpressionType::FunctionCallingExpression:
                    return visit(std::reinterpret_pointer_cast<GS_FunctionCallingExpression>(expression));
            }
        }
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto nodes = translationUnitDeclaration->getNodes();

        for (auto &node : nodes) {
            visit(node);
        }
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) {
        auto body = functionDeclaration->getBody();

        for (auto &statement : body) {
            visit(statement);
        }
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto expression = variableDeclarationStatement->getExpression();

        visit(expression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->getLValueExpression();
        auto rvalueExpression = assignmentStatement->getRValueExpression();

        visit(lvalueExpression);
        visit(rvalueExpression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->getExpression();

        visit(expression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_ConstantExpression> constantExpression) {

    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->getExpression();

        visit(expression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();

        visit(firstExpression);
        visit(secondExpression);
    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) {

    }

    Void GS_BaseVisitor::visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) {
        auto params = functionCallingExpression->getParams();

        for (auto &expression : params) {
            visit(expression);
        }
    }

}
