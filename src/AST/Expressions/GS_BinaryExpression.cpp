#include <Expressions/GS_BinaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_BinaryExpression::GS_BinaryExpression(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression)
            : _operation(operation), _firstExpression(std::move(firstExpression)), _secondExpression(std::move(secondExpression)) {}

    SharedPtr<GS_BinaryExpression> GS_BinaryExpression::Create(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression) {
        return std::make_shared<GS_BinaryExpression>(operation, std::move(firstExpression), std::move(secondExpression));
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