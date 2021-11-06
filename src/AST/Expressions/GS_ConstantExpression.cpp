#include <Expressions/GS_ConstantExpression.h>

namespace GSLanguageCompiler::AST {

    GS_Value::~GS_Value() = default;

    Any GS_Value::getValue() {
        return _value;
    }

    GSTypePtr GS_Value::getType() {
        return _type;
    }

    GS_I32Value::GS_I32Value(I32 value)
            : GS_Value(std::make_shared<GS_I32Type>(), value) {}

    GS_StringValue::GS_StringValue(String value)
            : GS_Value(std::make_shared<GS_StringType>(), std::move(value)) {}

    GS_ConstantExpression::GS_ConstantExpression(GSValuePtr value, GSScopePtr scope)
            : _value(std::move(value)), GS_Expression(std::move(scope)) {}

    GSValuePtr GS_ConstantExpression::getValue() {
        return _value;
    }

    Void GS_ConstantExpression::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    ExpressionType GS_ConstantExpression::getExpressionType() {
        return ExpressionType::ConstantExpression;
    }

}