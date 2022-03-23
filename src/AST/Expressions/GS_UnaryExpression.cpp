#include <Expressions/GS_UnaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_UnaryExpression::GS_UnaryExpression(UnaryOperation operation, GSExpressionPtr expression, GSScopePtr scope)
            : _operation(operation), _expression(std::move(expression)), GS_Expression(std::move(scope)) {}

    SharedPtr<GS_UnaryExpression> GS_UnaryExpression::Create(UnaryOperation operation, GSExpressionPtr expression, GSScopePtr scope) {
        return std::make_shared<GS_UnaryExpression>(operation, std::move(expression), std::move(scope));
    }

    LRef<UnaryOperation> GS_UnaryExpression::GetUnaryOperation() {
        return _operation;
    }

    LRef<GSExpressionPtr> GS_UnaryExpression::GetExpression() {
        return _expression;
    }

    ExpressionType GS_UnaryExpression::GetExpressionType() const {
        return ExpressionType::UnaryExpression;
    }

}
