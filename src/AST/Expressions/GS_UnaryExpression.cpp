#include <Expressions/GS_UnaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_UnaryExpression::GS_UnaryExpression(UnaryOperation operation, GSExpressionPtr expression)
            : _operation(operation), _expression(std::move(expression)) {}

    std::shared_ptr<GS_UnaryExpression> GS_UnaryExpression::Create(UnaryOperation operation, GSExpressionPtr expression) {
        return std::make_shared<GS_UnaryExpression>(operation, std::move(expression));
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
