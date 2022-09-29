#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(UString name, IO::GS_SourceLocation nameLocation)
            : _name(std::move(name)), _nameLocation(std::move(nameLocation)) {}

    std::shared_ptr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name, IO::GS_SourceLocation nameLocation) {
        return std::make_shared<GS_VariableUsingExpression>(std::move(name), std::move(nameLocation));
    }

    std::shared_ptr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name) {
        return GS_VariableUsingExpression::Create(std::move(name), IO::GS_SourceLocation::Create());
    }

    LRef<UString> GS_VariableUsingExpression::GetName() {
        return _name;
    }

    IO::GS_SourceLocation GS_VariableUsingExpression::GetNameLocation() const {
        return _nameLocation;
    }

    ExpressionType GS_VariableUsingExpression::GetExpressionType() const {
        return ExpressionType::VariableUsingExpression;
    }

}
