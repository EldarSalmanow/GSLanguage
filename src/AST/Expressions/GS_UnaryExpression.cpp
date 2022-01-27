#include <Expressions/GS_UnaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_UnaryExpression::GS_UnaryExpression(UnaryOperation operation, GSExpressionPtr expression, GSScopePtr scope)
            : _operation(operation), _expression(std::move(expression)), GS_Expression(std::move(scope)) {}

    UnaryOperation GS_UnaryExpression::getUnaryOperation() const {
        return _operation;
    }

    LRef<GSExpressionPtr> GS_UnaryExpression::getExpression() {
        return _expression;
    }

    ExpressionType GS_UnaryExpression::getExpressionType() const {
        return ExpressionType::UnaryExpression;
    }

}
