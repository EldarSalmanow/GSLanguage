#include <Expressions/GS_BinaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_BinaryExpression::GS_BinaryExpression(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression)
            : _operation(operation), _firstExpression(std::move(firstExpression)), _secondExpression(std::move(secondExpression)) {}

    BinaryOperation GS_BinaryExpression::getBinaryOperation() {
        return _operation;
    }

    GSExpressionPtr GS_BinaryExpression::getFirstExpression() {
        return _firstExpression;
    }

    GSExpressionPtr GS_BinaryExpression::getSecondExpression() {
        return _secondExpression;
    }

    Void GS_BinaryExpression::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    ExpressionType GS_BinaryExpression::getExpressionType() {
        return ExpressionType::BinaryExpression;
    }

}