#include <Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionCallingExpression::GS_FunctionCallingExpression(String name, GSExpressionPtrArray params)
            : _name(std::move(name)), _params(std::move(params)) {}

    String GS_FunctionCallingExpression::getName() {
        return _name;
    }

    GSExpressionPtrArray GS_FunctionCallingExpression::getParams() {
        return _params;
    }

    Void GS_FunctionCallingExpression::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    ExpressionType GS_FunctionCallingExpression::getExpressionType() {
        return ExpressionType::FunctionCallingExpression;
    }


}
