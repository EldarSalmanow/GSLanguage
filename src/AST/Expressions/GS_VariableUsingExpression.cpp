#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(UString name, IO::GSByteSourceRange nameLocationRange)
            : _name(std::move(name)), _nameLocationRange(nameLocationRange) {}

    std::shared_ptr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name, IO::GSByteSourceRange nameLocationRange) {
        return std::make_shared<GS_VariableUsingExpression>(std::move(name), nameLocationRange);
    }

    std::shared_ptr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name) {
        return GS_VariableUsingExpression::Create(std::move(name), IO::GSByteSourceRange::Create());
    }

    LRef<UString> GS_VariableUsingExpression::GetName() {
        return _name;
    }

    IO::GSByteSourceRange GS_VariableUsingExpression::GetNameLocationRange() const {
        return _nameLocationRange;
    }

    ExpressionType GS_VariableUsingExpression::GetExpressionType() const {
        return ExpressionType::VariableUsingExpression;
    }

}
