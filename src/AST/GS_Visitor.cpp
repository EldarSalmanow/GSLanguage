#include <AST.h>

namespace GSLanguageCompiler::AST {

    GS_Visitor::~GS_Visitor() = default;

    GS_BaseVisitor::~GS_BaseVisitor() = default;

    Any GS_BaseVisitor::visit(Ptr<GS_FunctionDeclaration> functionDeclaration) {
        auto body = functionDeclaration->getBody();

        for (auto &statement : body) {
            statement->accept(this);
        }

        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto expression = variableDeclarationStatement->getExpression();

        expression->accept(this);

        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->getLValueExpression();
        auto rvalueExpression = assignmentStatement->getRValueExpression();

        lvalueExpression->accept(this);
        rvalueExpression->accept(this);

        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->getExpression();

        expression->accept(this);

        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_ConstantExpression> constantExpression) {
        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->getExpression();

        expression->accept(this);

        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();

        firstExpression->accept(this);
        secondExpression->accept(this);

        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_VariableUsingExpression> variableUsingExpression) {
        return nullptr;
    }

    Any GS_BaseVisitor::visit(Ptr<GS_FunctionCallingExpression> functionCallingExpression) {
        auto params = functionCallingExpression->getParams();

        for (auto &param : params) {
            param->accept(this);
        }

        return nullptr;
    }
}
