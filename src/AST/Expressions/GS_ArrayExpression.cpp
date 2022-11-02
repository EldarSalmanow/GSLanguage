#include <Expressions/GS_ArrayExpression.h>

namespace GSLanguageCompiler::AST {

    GS_ArrayExpression::GS_ArrayExpression(GSExpressionPtrArray expressions)
            : _expressions(std::move(expressions)) {}

    std::shared_ptr<GS_ArrayExpression> GS_ArrayExpression::Create(GSExpressionPtrArray expressions) {
        return std::make_shared<GS_ArrayExpression>(std::move(expressions));
    }

    LRef<GSExpressionPtrArray> GS_ArrayExpression::GetExpressions() {
        return _expressions;
    }

    ExpressionType GS_ArrayExpression::GetExpressionType() const {
        return ExpressionType::ArrayExpression;
    }

}
