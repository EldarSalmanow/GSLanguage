#include <Expressions/GS_BinaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_BinaryExpression::GS_BinaryExpression(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression, GSScopePtr scope)
            : _operation(operation), _firstExpression(std::move(firstExpression)), _secondExpression(std::move(secondExpression)), GS_Expression(std::move(scope)) {}

    SharedPtr<GS_BinaryExpression> GS_BinaryExpression::Create(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression, GSScopePtr scope) {
        return std::make_shared<GS_BinaryExpression>(operation, std::move(firstExpression), std::move(secondExpression), std::move(scope));
    }

    LRef<BinaryOperation> GS_BinaryExpression::GetBinaryOperation() {
        return _operation;
    }

    LRef<GSExpressionPtr> GS_BinaryExpression::GetFirstExpression() {
        return _firstExpression;
    }

    LRef<GSExpressionPtr> GS_BinaryExpression::GetSecondExpression() {
        return _secondExpression;
    }

    ExpressionType GS_BinaryExpression::GetExpressionType() const {
        return ExpressionType::BinaryExpression;
    }

}