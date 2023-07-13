#include <Expressions/GS_VariableUsingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_VariableUsingExpression::GS_VariableUsingExpression(UString name,
                                                           IO::GS_SourceRange nameLocation)
            : _name(std::move(name)),
              _nameLocation(nameLocation) {}

    std::shared_ptr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name,
                                                                                   IO::GS_SourceRange nameLocation) {
        return std::make_shared<GS_VariableUsingExpression>(std::move(name),
                                                            nameLocation);
    }

    std::shared_ptr<GS_VariableUsingExpression> GS_VariableUsingExpression::Create(UString name) {
        return GS_VariableUsingExpression::Create(std::move(name),
                                                  IO::GS_SourceRange::Create());
    }

    LRef<UString> GS_VariableUsingExpression::GetName() {
        return _name;
    }

    LRef<IO::GS_SourceRange> GS_VariableUsingExpression::GetNameLocation() {
        return _nameLocation;
    }

    ExpressionType GS_VariableUsingExpression::GetExpressionType() const {
        return ExpressionType::VariableUsingExpression;
    }

}
