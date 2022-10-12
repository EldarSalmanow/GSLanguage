#include <GS_Type.h>

namespace GSLanguageCompiler::Semantic {

    GS_Type::GS_Type(UString name)
            : _name(std::move(name)) {}

    GS_Type::~GS_Type() = default;

    std::shared_ptr<GS_Type> GS_Type::Create(UString name) {
        return std::make_shared<GS_Type>(std::move(name));
    }

    UString GS_Type::GetName() const {
        return _name;
    }

    TypeType GS_Type::GetType() const {
        return TypeType::User;
    }

    GS_VoidType::GS_VoidType()
            : GS_Type("Void"_us) {}

    std::shared_ptr<GS_VoidType> GS_VoidType::Create() {
        return std::make_shared<GS_VoidType>();
    }

    TypeType GS_VoidType::GetType() const {
        return TypeType::Void;
    }

    GS_CharType::GS_CharType()
            : GS_Type("Char"_us) {}

    std::shared_ptr<GS_CharType> GS_CharType::Create() {
        return std::make_shared<GS_CharType>();
    }

    TypeType GS_CharType::GetType() const {
        return TypeType::Char;
    }

    GS_IntegerType::GS_IntegerType(UString name)
            : GS_Type(std::move(name)) {}

    std::shared_ptr<GS_IntegerType> GS_IntegerType::Create(UString name) {
        return std::make_shared<GS_IntegerType>(std::move(name));
    }

    TypeType GS_IntegerType::GetType() const {
        return TypeType::Integer;
    }

    IntegerType GS_IntegerType::GetIntegerType() const {
        return IntegerType::User;
    }

    GS_I8Type::GS_I8Type()
            : GS_IntegerType("I8"_us) {}

    std::shared_ptr<GS_I8Type> GS_I8Type::Create() {
        return std::make_shared<GS_I8Type>();
    }

    IntegerType GS_I8Type::GetIntegerType() const {
        return IntegerType::I8;
    }

    GS_I16Type::GS_I16Type()
            : GS_IntegerType("I16"_us) {}

    std::shared_ptr<GS_I16Type> GS_I16Type::Create() {
        return std::make_shared<GS_I16Type>();
    }

    IntegerType GS_I16Type::GetIntegerType() const {
        return IntegerType::I16;
    }

    GS_I32Type::GS_I32Type()
            : GS_IntegerType("I32"_us) {}

    std::shared_ptr<GS_I32Type> GS_I32Type::Create() {
        return std::make_shared<GS_I32Type>();
    }

    IntegerType GS_I32Type::GetIntegerType() const {
        return IntegerType::I32;
    }

    GS_I64Type::GS_I64Type()
            : GS_IntegerType("I64"_us) {}

    std::shared_ptr<GS_I64Type> GS_I64Type::Create() {
        return std::make_shared<GS_I64Type>();
    }

    IntegerType GS_I64Type::GetIntegerType() const {
        return IntegerType::I64;
    }

    GS_UIntegerType::GS_UIntegerType(UString name)
            : GS_Type(std::move(name)) {}

    std::shared_ptr<GS_UIntegerType> GS_UIntegerType::Create(UString name) {
        return std::make_shared<GS_UIntegerType>(std::move(name));
    }

    TypeType GS_UIntegerType::GetType() const {
        return TypeType::UInteger;
    }

    UIntegerType GS_UIntegerType::GetUIntegerType() const {
        return UIntegerType::User;
    }

    GS_U8Type::GS_U8Type()
            : GS_UIntegerType("U8"_us) {}

    std::shared_ptr<GS_U8Type> GS_U8Type::Create() {
        return std::make_shared<GS_U8Type>();
    }

    UIntegerType GS_U8Type::GetUIntegerType() const {
        return UIntegerType::U8;
    }

    GS_U16Type::GS_U16Type()
            : GS_UIntegerType("U16"_us) {}

    std::shared_ptr<GS_U16Type> GS_U16Type::Create() {
        return std::make_shared<GS_U16Type>();
    }

    UIntegerType GS_U16Type::GetUIntegerType() const {
        return UIntegerType::U16;
    }

    GS_U32Type::GS_U32Type()
            : GS_UIntegerType("U32"_us) {}

    std::shared_ptr<GS_U32Type> GS_U32Type::Create() {
        return std::make_shared<GS_U32Type>();
    }

    UIntegerType GS_U32Type::GetUIntegerType() const {
        return UIntegerType::U32;
    }

    GS_U64Type::GS_U64Type()
            : GS_UIntegerType("U64"_us) {}

    std::shared_ptr<GS_U64Type> GS_U64Type::Create() {
        return std::make_shared<GS_U64Type>();
    }

    UIntegerType GS_U64Type::GetUIntegerType() const {
        return UIntegerType::U64;
    }

    GS_StringType::GS_StringType()
            : GS_Type("String"_us) {}

    std::shared_ptr<GS_StringType> GS_StringType::Create() {
        return std::make_shared<GS_StringType>();
    }

    TypeType GS_StringType::GetType() const {
        return TypeType::String;
    }

    // check

    GS_ArrayType::GS_ArrayType(GSTypePtr elementsType, U64 size)
            : _elementsType(std::move(elementsType)), _size(size), GS_Type("Array["_us + elementsType->GetName() + ", "_us + UString(std::to_string(size)) + "]"_us) {}

    std::shared_ptr<GS_ArrayType> GS_ArrayType::Create(GSTypePtr elementsType, U64 size) {
        return std::make_shared<GS_ArrayType>(std::move(elementsType), size);
    }

    GSTypePtr GS_ArrayType::GetElementsType() const {
        return _elementsType;
    }

    U64 GS_ArrayType::GetSize() const {
        return _size;
    }

    TypeType GS_ArrayType::GetType() const {
        return TypeType::Array;
    }

    GS_TypeContext::GS_TypeContext()
            : _voidType(GS_VoidType::Create()),
              _i32Type(GS_I32Type::Create()),
              _stringType(GS_StringType::Create()) {}

    std::shared_ptr<GS_TypeContext> GS_TypeContext::Create() {
        return std::make_shared<GS_TypeContext>();
    }

    TypePtr<GS_VoidType> GS_TypeContext::GetVoidType() const {
        return _voidType;
    }

    TypePtr<GS_CharType> GS_TypeContext::GetCharType() const {
        return _charType;
    }

    TypePtr<GS_I8Type> GS_TypeContext::GetI8Type() const {
        return _i8Type;
    }

    TypePtr<GS_I16Type> GS_TypeContext::GetI16Type() const {
        return _i16Type;
    }

    TypePtr<GS_I32Type> GS_TypeContext::GetI32Type() const {
        return _i32Type;
    }

    TypePtr<GS_I64Type> GS_TypeContext::GetI64Type() const {
        return _i64Type;
    }

    TypePtr<GS_U8Type> GS_TypeContext::GetU8Type() const {
        return _u8Type;
    }

    TypePtr<GS_U16Type> GS_TypeContext::GetU16Type() const {
        return _u16Type;
    }

    TypePtr<GS_U32Type> GS_TypeContext::GetU32Type() const {
        return _u32Type;
    }

    TypePtr<GS_U64Type> GS_TypeContext::GetU64Type() const {
        return _u64Type;
    }

    TypePtr<GS_StringType> GS_TypeContext::GetStringType() const {
        return _stringType;
    }

    TypePtr<GS_ArrayType> GS_TypeContext::GetArrayType(GSTypePtr type, U64 size) const {
        return GS_ArrayType::Create(std::move(type), size);
    }

}
