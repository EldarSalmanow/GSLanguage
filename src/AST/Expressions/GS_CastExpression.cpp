#include <Expressions/GS_CastExpression.h>

namespace GSLanguageCompiler::AST {

    GS_CastExpression::GS_CastExpression(GSExpressionPtr expression,
                                         Semantic::GSTypePtr type)
            : _expression(std::move(expression)),
              _type(std::move(type)) {}

    std::shared_ptr<GS_CastExpression> GS_CastExpression::Create(GSExpressionPtr expression,
                                                                 Semantic::GSTypePtr type) {
        return std::make_shared<GS_CastExpression>(std::move(expression),
                                                   std::move(type));
    }

    LRef<GSExpressionPtr> GS_CastExpression::GetExpression() {
        return _expression;
    }

    LRef<Semantic::GSTypePtr> GS_CastExpression::GetType() {
        return _type;
    }

    ExpressionType GS_CastExpression::GetExpressionType() const {
        return ExpressionType::CastExpression;
    }

}
