#include <Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionCallingExpression::GS_FunctionCallingExpression(UString name, GSExpressionPtrArray params, GSScopePtr scope)
            : _name(std::move(name)), _params(std::move(params)), GS_Expression(std::move(scope)) {}

    SharedPtr<GS_FunctionCallingExpression> GS_FunctionCallingExpression::Create(UString name, GSExpressionPtrArray params, GSScopePtr scope) {
        return std::make_shared<GS_FunctionCallingExpression>(std::move(name), std::move(params), std::move(scope));
    }

    LRef<UString> GS_FunctionCallingExpression::getName() {
        return _name;
    }

    LRef<GSExpressionPtrArray> GS_FunctionCallingExpression::getParams() {
        return _params;
    }

    ExpressionType GS_FunctionCallingExpression::getExpressionType() const {
        return ExpressionType::FunctionCallingExpression;
    }


}
