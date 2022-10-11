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

    Bool GS_Type::IsLiteralType() const {
        return false;
    }

    GS_VoidType::GS_VoidType()
            : GS_Type("Void"_us) {}

    std::shared_ptr<GS_VoidType> GS_VoidType::Create() {
        return std::make_shared<GS_VoidType>();
    }

    GS_LiteralType::GS_LiteralType(UString name)
            : GS_Type(std::move(name)) {}

    std::shared_ptr<GS_LiteralType> GS_LiteralType::Create(UString name) {
        return std::make_shared<GS_LiteralType>(std::move(name));
    }

    Bool GS_LiteralType::IsLiteralType() const {
        return true;
    }

    GS_CharType::GS_CharType()
            : GS_LiteralType("Char"_us) {}

    std::shared_ptr<GS_CharType> GS_CharType::Create() {
        return std::make_shared<GS_CharType>();
    }

    GS_I8Type::GS_I8Type()
            : GS_LiteralType("I8"_us) {}

    std::shared_ptr<GS_I8Type> GS_I8Type::Create() {
        return std::make_shared<GS_I8Type>();
    }

    GS_I16Type::GS_I16Type()
            : GS_LiteralType("I16"_us) {}

    std::shared_ptr<GS_I16Type> GS_I16Type::Create() {
        return std::make_shared<GS_I16Type>();
    }

    GS_I32Type::GS_I32Type()
            : GS_LiteralType("I32"_us) {}

    std::shared_ptr<GS_I32Type> GS_I32Type::Create() {
        return std::make_shared<GS_I32Type>();
    }

    GS_I64Type::GS_I64Type()
            : GS_LiteralType("I64"_us) {}

    std::shared_ptr<GS_I64Type> GS_I64Type::Create() {
        return std::make_shared<GS_I64Type>();
    }

    GS_U8Type::GS_U8Type()
            : GS_LiteralType("U8"_us) {}

    std::shared_ptr<GS_U8Type> GS_U8Type::Create() {
        return std::make_shared<GS_U8Type>();
    }

    GS_U16Type::GS_U16Type()
            : GS_LiteralType("U16"_us) {}

    std::shared_ptr<GS_U16Type> GS_U16Type::Create() {
        return std::make_shared<GS_U16Type>();
    }

    GS_U32Type::GS_U32Type()
            : GS_LiteralType("U32"_us) {}

    std::shared_ptr<GS_U32Type> GS_U32Type::Create() {
        return std::make_shared<GS_U32Type>();
    }

    GS_U64Type::GS_U64Type()
            : GS_LiteralType("U64"_us) {}

    std::shared_ptr<GS_U64Type> GS_U64Type::Create() {
        return std::make_shared<GS_U64Type>();
    }

    GS_StringType::GS_StringType()
            : GS_LiteralType("String"_us) {}

    std::shared_ptr<GS_StringType> GS_StringType::Create() {
        return std::make_shared<GS_StringType>();
    }

    // check

    GS_ArrayType::GS_ArrayType(GSTypePtr type, U64 size)
            : _type(std::move(type)), _size(size), GS_Type("Array["_us + type->GetName() + ", "_us + UString(std::to_string(size)) + "]"_us) {}

    std::shared_ptr<GS_ArrayType> GS_ArrayType::Create(GSTypePtr type, U64 size) {
        return std::make_shared<GS_ArrayType>(std::move(type), size);
    }

    GSTypePtr GS_ArrayType::GetType() const {
        return _type;
    }

    U64 GS_ArrayType::GetSize() const {
        return _size;
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

}
