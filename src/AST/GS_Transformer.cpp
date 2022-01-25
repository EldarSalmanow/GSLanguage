#include <AST/AST.h>

namespace GSLanguageCompiler::AST {

    GS_Transformer::~GS_Transformer() = default;

    GS_BaseTransformer::~GS_BaseTransformer() = default;

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_FunctionDeclaration> functionDeclaration) {
        auto transformedFunctionDeclaration = GS_BaseVisitor::visit(functionDeclaration);

        return std::any_cast<GSNodePtr>(transformedFunctionDeclaration);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto transformedVariableDeclarationStatement = GS_BaseVisitor::visit(variableDeclarationStatement);

        return std::any_cast<GSNodePtr>(transformedVariableDeclarationStatement);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_AssignmentStatement> assignmentStatement) {
        auto transformedAssignmentStatement = GS_BaseVisitor::visit(assignmentStatement);

        return std::any_cast<GSNodePtr>(transformedAssignmentStatement);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_ExpressionStatement> expressionStatement) {
        auto transformedExpressionStatement = GS_BaseVisitor::visit(expressionStatement);

        return std::any_cast<GSNodePtr>(transformedExpressionStatement);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_ConstantExpression> constantExpression) {
        auto transformedConstantExpression = GS_BaseVisitor::visit(constantExpression);

        return std::any_cast<GSNodePtr>(transformedConstantExpression);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_UnaryExpression> unaryExpression) {
        auto transformedUnaryExpression = GS_BaseVisitor::visit(unaryExpression);

        return std::any_cast<GSNodePtr>(transformedUnaryExpression);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_BinaryExpression> binaryExpression) {
        auto transformedBinaryExpression = GS_BaseVisitor::visit(binaryExpression);

        return std::any_cast<GSNodePtr>(transformedBinaryExpression);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_VariableUsingExpression> variableUsingExpression) {
        auto transformedVariableUsingExpression = GS_BaseVisitor::visit(variableUsingExpression);

        return std::any_cast<GSNodePtr>(transformedVariableUsingExpression);
    }

    GSNodePtr GS_BaseTransformer::transform(Ptr<GS_FunctionCallingExpression> functionCallingExpression) {
        auto transformedFunctionCallingExpression = GS_BaseVisitor::visit(functionCallingExpression);

        return std::any_cast<GSNodePtr>(transformedFunctionCallingExpression);
    }

}
