#include <Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionCallingExpression::GS_FunctionCallingExpression(UString name,
                                                               GSExpressionPtrArray arguments)
            : _name(std::move(name)),
              _arguments(std::move(arguments)) {}

    std::shared_ptr<GS_FunctionCallingExpression> GS_FunctionCallingExpression::Create(UString name,
                                                                                       GSExpressionPtrArray arguments) {
        return std::make_shared<GS_FunctionCallingExpression>(std::move(name),
                                                              std::move(arguments));
    }

    std::shared_ptr<GS_FunctionCallingExpression> GS_FunctionCallingExpression::Create(UString name) {
        return GS_FunctionCallingExpression::Create(std::move(name),
                                                    GSExpressionPtrArray());
    }

    LRef<UString> GS_FunctionCallingExpression::GetName() {
        return _name;
    }

    LRef<GSExpressionPtrArray> GS_FunctionCallingExpression::GetArguments() {
        return _arguments;
    }

    ExpressionType GS_FunctionCallingExpression::GetExpressionType() const {
        return ExpressionType::FunctionCallingExpression;
    }


}
