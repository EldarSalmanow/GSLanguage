#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(UString name, GSScopePtr scope)
            : _name(std::move(name)), GS_Expression(std::move(scope)) {}

    UString GS_VariableUsingExpression::getName() const {
        return _name;
    }

    Any GS_VariableUsingExpression::accept(Ptr<GS_Visitor> visitor) {
        return visitor->visit(this);
    }

    ExpressionType GS_VariableUsingExpression::getExpressionType() const {
        return ExpressionType::VariableUsingExpression;
    }

}
