#include <Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionCallingExpression::GS_FunctionCallingExpression(UString name, GSExpressionPtrArray params, GSScopePtr scope)
            : _name(std::move(name)), _params(std::move(params)), GS_Expression(std::move(scope)) {}

    UString GS_FunctionCallingExpression::getName() const {
        return _name;
    }

    GSExpressionPtrArray GS_FunctionCallingExpression::getParams() const {
        return _params;
    }

    Any GS_FunctionCallingExpression::accept(Ptr<GS_Visitor> visitor) {
        return visitor->visit(this);
    }

    ExpressionType GS_FunctionCallingExpression::getExpressionType() const {
        return ExpressionType::FunctionCallingExpression;
    }


}
