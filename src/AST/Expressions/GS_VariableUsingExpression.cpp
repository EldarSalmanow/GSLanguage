#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(UString name, GSScopePtr scope)
            : _name(std::move(name)), GS_Expression(std::move(scope)) {}

    SharedPtr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name, GSScopePtr scope) {
        return std::make_shared<GS_VariableUsingExpression>(std::move(name), std::move(scope));
    }

    LRef<UString> GS_VariableUsingExpression::getName() {
        return _name;
    }

    ExpressionType GS_VariableUsingExpression::getExpressionType() const {
        return ExpressionType::VariableUsingExpression;
    }

}
