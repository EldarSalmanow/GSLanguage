#include <Expressions/GS_ConstantExpression.h>

namespace GSLanguageCompiler::AST {

    GS_Value::~GS_Value() = default;

    Any GS_Value::GetValue() const {
        return _value;
    }

    GSTypePtr GS_Value::GetType() const {
        return _type;
    }

    GS_I32Value::GS_I32Value(I32 value)
            : GS_Value(std::make_shared<GS_I32Type>(), value) {}

    SharedPtr<GS_I32Value> GS_I32Value::Create(I32 value) {
        return std::make_shared<GS_I32Value>(value);
    }

    GS_StringValue::GS_StringValue(UString value)
            : GS_Value(std::make_shared<GS_StringType>(), std::move(value)) {}

    SharedPtr<GS_StringValue> GS_StringValue::Create(UString value) {
        return std::make_shared<GS_StringValue>(std::move(value));
    }

    GS_ConstantExpression::GS_ConstantExpression(GSValuePtr value, GSScopePtr scope)
            : _value(std::move(value)), GS_Expression(std::move(scope)) {}

    SharedPtr<GS_ConstantExpression> GS_ConstantExpression::Create(GSValuePtr value, GSScopePtr scope) {
        return std::make_shared<GS_ConstantExpression>(std::move(value), std::move(scope));
    }

    LRef<GSValuePtr> GS_ConstantExpression::GetValue() {
        return _value;
    }

    ExpressionType GS_ConstantExpression::GetExpressionType() const {
        return ExpressionType::ConstantExpression;
    }

}