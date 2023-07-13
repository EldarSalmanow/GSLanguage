#include <Expressions/GS_IndexExpression.h>

namespace GSLanguageCompiler::AST {

    GS_IndexExpression::GS_IndexExpression(GSExpressionPtr expression,
                                           GSExpressionPtr index)
            : _expression(std::move(expression)),
              _index(std::move(index)) {}

    std::shared_ptr<GS_IndexExpression> GS_IndexExpression::Create(GSExpressionPtr expression,
                                                                   GSExpressionPtr index) {
        return std::make_shared<GS_IndexExpression>(std::move(expression),
                                                    std::move(index));
    }

    LRef<GSExpressionPtr> GS_IndexExpression::GetExpression() {
        return _expression;
    }

    LRef<GSExpressionPtr> GS_IndexExpression::GetIndex() {
        return _index;
    }

    ExpressionType GS_IndexExpression::GetExpressionType() const {
        return ExpressionType::IndexExpression;
    }

}
