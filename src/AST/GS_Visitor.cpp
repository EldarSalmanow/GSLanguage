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

}
