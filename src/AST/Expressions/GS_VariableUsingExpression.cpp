#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(UString name)
            : _name(std::move(name)) {}

    SharedPtr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name) {
        return std::make_shared<GS_VariableUsingExpression>(std::move(name));
    }

    LRef<UString> GS_VariableUsingExpression::GetName() {
        return _name;
    }

    ExpressionType GS_VariableUsingExpression::GetExpressionType() const {
        return ExpressionType::VariableUsingExpression;
    }

}
