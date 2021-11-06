#include <Expressions/GS_UnaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_UnaryExpression::GS_UnaryExpression(UnaryOperation operation, GSExpressionPtr expression, GSScopePtr scope)
            : _operation(operation), _expression(std::move(expression)), GS_Expression(std::move(scope)) {}

    UnaryOperation GS_UnaryExpression::getUnaryOperation() {
        return _operation;
    }

    GSExpressionPtr GS_UnaryExpression::getExpression() {
        return _expression;
    }

    Void GS_UnaryExpression::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    ExpressionType GS_UnaryExpression::getExpressionType() {
        return ExpressionType::UnaryExpression;
    }

}
