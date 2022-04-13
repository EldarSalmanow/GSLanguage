#include <Expressions/GS_ConstantExpression.h>

namespace GSLanguageCompiler::AST {

    GS_Value::GS_Value(GSTypePtr type)
            : _type(std::move(type)) {}

    GS_Value::~GS_Value() = default;

    SharedPtr<GS_Value> GS_Value::Create(GSTypePtr type) {
        return std::make_shared<GS_Value>(std::move(type));
    }

    GSTypePtr GS_Value::GetType() const {
        return _type;
    }

    Bool GS_Value::IsLiteralValue() {
        return false;
    }

    Any GS_LiteralValue::GetValue() const {
        return _value;
    }

    Bool GS_LiteralValue::IsLiteralValue() {
        return true;
    }

    GS_I32Value::GS_I32Value(I32 value)
            : GS_LiteralValue(value, GS_I32Type::Create()) {}

    SharedPtr<GS_I32Value> GS_I32Value::Create(I32 value) {
        return std::make_shared<GS_I32Value>(value);
    }

    I32 GS_I32Value::GetI32Value() const {
        return GetValueWithCast<I32>();
    }

    GS_StringValue::GS_StringValue(UString value)
            : GS_LiteralValue(std::move(value), GS_StringType::Create()) {}

    SharedPtr<GS_StringValue> GS_StringValue::Create(UString value) {
        return std::make_shared<GS_StringValue>(std::move(value));
    }

    UString GS_StringValue::GetStringValue() const {
        return GetValueWithCast<UString>();
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