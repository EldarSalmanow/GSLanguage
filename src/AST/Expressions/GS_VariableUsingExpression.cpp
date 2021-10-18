#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(String name)
            : _name(std::move(name)) {}

    String GS_VariableUsingExpression::getName() {
        return _name;
    }

    ExpressionType GS_VariableUsingExpression::getExpressionType() {
        return ExpressionType::VariableUsingExpression;
    }

}
