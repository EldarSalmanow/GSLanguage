#include <Expressions/GS_RangeExpression.h>

namespace GSLanguageCompiler::AST {

    GS_RangeExpression::GS_RangeExpression(GSExpressionPtr startExpression,
                                           GSExpressionPtr endExpression)
            : _startExpression(std::move(startExpression)),
              _endExpression(std::move(endExpression)) {}

    std::shared_ptr<GS_RangeExpression> GS_RangeExpression::Create(GSExpressionPtr startExpression,
                                                                   GSExpressionPtr endExpression) {
        return std::make_shared<GS_RangeExpression>(std::move(startExpression),
                                                    std::move(endExpression));
    }

    LRef<GSExpressionPtr> GS_RangeExpression::GetStartExpression() {
        return _startExpression;
    }

    LRef<GSExpressionPtr> GS_RangeExpression::GetEndExpression() {
        return _endExpression;
    }

    ExpressionType GS_RangeExpression::GetExpressionType() const {
        return ExpressionType::RangeExpression;
    }

}
