#include <Expressions/GS_UnaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_UnaryExpression::GS_UnaryExpression(UnaryOperation operation, GSExpressionPtr expression)
            : _operation(operation), _expression(std::move(expression)) {}

    UnaryOperation GS_UnaryExpression::getUnaryOperation() {
        return _operation;
    }

    GSExpressionPtr GS_UnaryExpression::getExpression() {
        return _expression;
    }

    ExpressionType GS_UnaryExpression::getExpressionType() {
        return ExpressionType::UnaryExpression;
    }

}
