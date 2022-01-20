#include <Expressions/GS_BinaryExpression.h>

namespace GSLanguageCompiler::AST {

    GS_BinaryExpression::GS_BinaryExpression(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression, GSScopePtr scope)
            : _operation(operation), _firstExpression(std::move(firstExpression)), _secondExpression(std::move(secondExpression)), GS_Expression(std::move(scope)) {}

    BinaryOperation GS_BinaryExpression::getBinaryOperation() const {
        return _operation;
    }

    GSExpressionPtr GS_BinaryExpression::getFirstExpression() const {
        return _firstExpression;
    }

    GSExpressionPtr GS_BinaryExpression::getSecondExpression() const {
        return _secondExpression;
    }

    Void GS_BinaryExpression::accept(Ptr<GS_Visitor> visitor) {
        visitor->visit(this);
    }

    ExpressionType GS_BinaryExpression::getExpressionType() const {
        return ExpressionType::BinaryExpression;
    }

}