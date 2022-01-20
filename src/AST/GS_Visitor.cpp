#include <AST.h>

namespace GSLanguageCompiler::AST {

    GS_Visitor::~GS_Visitor() = default;

    Void GS_Visitor::visit(Ptr<GS_FunctionDeclaration> functionDeclaration) {
        auto body = functionDeclaration->getBody();

        for (auto &statement : body) {
            statement->accept(this);
        }
    }

    Void GS_Visitor::visit(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement) {}

    Void GS_Visitor::visit(Ptr<GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->getLValueExpression();
        auto rvalueExpression = assignmentStatement->getRValueExpression();

        lvalueExpression->accept(this);
        rvalueExpression->accept(this);
    }

    Void GS_Visitor::visit(Ptr<GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->getExpression();

        expression->accept(this);
    }

    Void GS_Visitor::visit(Ptr<GS_ConstantExpression> constantExpression) {}

    Void GS_Visitor::visit(Ptr<GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->getExpression();

        expression->accept(this);
    }

    Void GS_Visitor::visit(Ptr<GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();

        firstExpression->accept(this);
        secondExpression->accept(this);
    }

    Void GS_Visitor::visit(Ptr<GS_VariableUsingExpression> variableUsingExpression) {}

    Void GS_Visitor::visit(Ptr<GS_FunctionCallingExpression> functionCallingExpression) {
        auto params = functionCallingExpression->getParams();

        for (auto &param : params) {
            param->accept(this);
        }
    }

}
