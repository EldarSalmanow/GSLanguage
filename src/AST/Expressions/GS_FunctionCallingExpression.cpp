#include <Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionCallingExpression::GS_FunctionCallingExpression(UString name, GSExpressionPtrArray params)
            : _name(std::move(name)), _params(std::move(params)) {}

    std::shared_ptr<GS_FunctionCallingExpression> GS_FunctionCallingExpression::Create(UString name, GSExpressionPtrArray params) {
        return std::make_shared<GS_FunctionCallingExpression>(std::move(name), std::move(params));
    }

    LRef<UString> GS_FunctionCallingExpression::GetName() {
        return _name;
    }

    LRef<GSExpressionPtrArray> GS_FunctionCallingExpression::GetParams() {
        return _params;
    }

    ExpressionType GS_FunctionCallingExpression::GetExpressionType() const {
        return ExpressionType::FunctionCallingExpression;
    }


}
