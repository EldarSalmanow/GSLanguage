#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(String name)
            : _name(std::move(name)) {}

    String GS_VariableUsingExpression::getName() {
        return _name;
    }

    Void GS_VariableUsingExpression::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    ExpressionType GS_VariableUsingExpression::getExpressionType() {
        return ExpressionType::VariableUsingExpression;
    }

}
