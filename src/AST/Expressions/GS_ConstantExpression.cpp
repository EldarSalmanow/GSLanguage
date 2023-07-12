#include <Expressions/GS_ConstantExpression.h>

namespace GSLanguageCompiler::AST {

    GS_Value::GS_Value(Semantic::GSTypePtr type)
            : _type(std::move(type)) {}

    GS_Value::~GS_Value() = default;

    std::shared_ptr<GS_Value> GS_Value::Create(Semantic::GSTypePtr type) {
        return std::make_shared<GS_Value>(std::move(type));
    }

    Semantic::GSTypePtr GS_Value::GetType() const {
        return _type;
    }

    Bool GS_Value::IsLiteralValue() {
        return false;
    }

    ConstLRef<std::any> GS_LiteralValue::GetValue() const {
        return _value;
    }

    Bool GS_LiteralValue::IsLiteralValue() {
        return true;
    }

    GS_BoolValue::GS_BoolValue(Bool value)
            : GS_LiteralValue(value,
                              Semantic::GS_BoolType::Create()) {}

    std::shared_ptr<GS_BoolValue> GS_BoolValue::Create(Bool value) {
        return std::make_shared<GS_BoolValue>(value);
    }

    Bool GS_BoolValue::GetBoolValue() const {
        return GetValueWithCast<Bool>();
    }

    GS_CharValue::GS_CharValue(USymbol value)
            : GS_LiteralValue(std::move(value),
                              Semantic::GS_CharType::Create()) {}

    std::shared_ptr<GS_CharValue> GS_CharValue::Create(USymbol value) {
        return std::make_shared<GS_CharValue>(std::move(value));
    }

    USymbol GS_CharValue::GetCharValue() const {
        return GetValueWithCast<USymbol>();
    }

    GS_I8Value::GS_I8Value(I8 value)
            : GS_IntegerValue(value,
                              Semantic::GS_I8Type::Create()) {}

    std::shared_ptr<GS_I8Value> GS_I8Value::Create(I8 value) {
        return std::make_shared<GS_I8Value>(value);
    }

    I8 GS_I8Value::GetI8Value() const {
        return GetValueWithCast<I8>();
    }

    GS_I16Value::GS_I16Value(I16 value)
            : GS_IntegerValue(value,
                              Semantic::GS_I16Type::Create()) {}

    std::shared_ptr<GS_I16Value> GS_I16Value::Create(I16 value) {
        return std::make_shared<GS_I16Value>(value);
    }

    I16 GS_I16Value::GetI16Value() const {
        return GetValueWithCast<I16>();
    }

    GS_I32Value::GS_I32Value(I32 value)
            : GS_IntegerValue(value,
                              Semantic::GS_I32Type::Create()) {}

    std::shared_ptr<GS_I32Value> GS_I32Value::Create(I32 value) {
        return std::make_shared<GS_I32Value>(value);
    }

    I32 GS_I32Value::GetI32Value() const {
        return GetValueWithCast<I32>();
    }

    GS_I64Value::GS_I64Value(I64 value)
            : GS_IntegerValue(value,
                              Semantic::GS_I64Type::Create()) {}

    std::shared_ptr<GS_I64Value> GS_I64Value::Create(I64 value) {
        return std::make_shared<GS_I64Value>(value);
    }

    I64 GS_I64Value::GetI64Value() const {
        return GetValueWithCast<I64>();
    }

    GS_U8Value::GS_U8Value(U8 value)
            : GS_UIntegerValue(value,
                               Semantic::GS_U8Type::Create()) {}

    std::shared_ptr<GS_U8Value> GS_U8Value::Create(U8 value) {
        return std::make_shared<GS_U8Value>(value);
    }

    U8 GS_U8Value::GetU8Value() const {
        return GetValueWithCast<U8>();
    }

    GS_U16Value::GS_U16Value(U16 value)
            : GS_UIntegerValue(value,
                               Semantic::GS_U16Type::Create()) {}

    std::shared_ptr<GS_U16Value> GS_U16Value::Create(U16 value) {
        return std::make_shared<GS_U16Value>(value);
    }

    U16 GS_U16Value::GetU16Value() const {
        return GetValueWithCast<U16>();
    }

    GS_U32Value::GS_U32Value(U32 value)
            : GS_UIntegerValue(value,
                               Semantic::GS_U32Type::Create()) {}

    std::shared_ptr<GS_U32Value> GS_U32Value::Create(U32 value) {
        return std::make_shared<GS_U32Value>(value);
    }

    U32 GS_U32Value::GetU32Value() const {
        return GetValueWithCast<U32>();
    }

    GS_U64Value::GS_U64Value(U64 value)
            : GS_UIntegerValue(value,
                               Semantic::GS_U64Type::Create()) {}

    std::shared_ptr<GS_U64Value> GS_U64Value::Create(U64 value) {
        return std::make_shared<GS_U64Value>(value);
    }

    U64 GS_U64Value::GetU64Value() const {
        return GetValueWithCast<U64>();
    }

    GS_StringValue::GS_StringValue(UString value)
            : GS_LiteralValue(std::move(value),
                              Semantic::GS_StringType::Create()) {}

    std::shared_ptr<GS_StringValue> GS_StringValue::Create(UString value) {
        return std::make_shared<GS_StringValue>(std::move(value));
    }

    UString GS_StringValue::GetStringValue() const {
        return GetValueWithCast<UString>();
    }

    GS_ConstantExpression::GS_ConstantExpression(GSValuePtr value)
            : _value(std::move(value)) {}

    std::shared_ptr<GS_ConstantExpression> GS_ConstantExpression::Create(GSValuePtr value) {
        return std::make_shared<GS_ConstantExpression>(std::move(value));
    }

    LRef<GSValuePtr> GS_ConstantExpression::GetValue() {
        return _value;
    }

    ExpressionType GS_ConstantExpression::GetExpressionType() const {
        return ExpressionType::ConstantExpression;
    }

}