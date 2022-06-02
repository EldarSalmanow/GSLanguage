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

    GS_LiteralType::GS_LiteralType(UString name)
            : GS_Type(std::move(name)) {}

    std::shared_ptr<GS_LiteralType> GS_LiteralType::Create(UString name) {
        return std::make_shared<GS_LiteralType>(std::move(name));
    }

    Bool GS_LiteralType::IsLiteralType() const {
        return true;
    }

    GS_VoidType::GS_VoidType()
            : GS_LiteralType("Void"_us) {}

    std::shared_ptr<GS_VoidType> GS_VoidType::Create() {
        return std::make_shared<GS_VoidType>();
    }

    GS_I32Type::GS_I32Type()
            : GS_LiteralType("I32"_us) {}

    std::shared_ptr<GS_I32Type> GS_I32Type::Create() {
        return std::make_shared<GS_I32Type>();
    }

    GS_StringType::GS_StringType()
            : GS_LiteralType("String"_us) {}

    std::shared_ptr<GS_StringType> GS_StringType::Create() {
        return std::make_shared<GS_StringType>();
    }

    GS_TypeContext::GS_TypeContext()
            : _voidType(Semantic::GS_VoidType::Create()),
              _i32Type(Semantic::GS_I32Type::Create()),
              _stringType(Semantic::GS_StringType::Create()) {}

    std::shared_ptr<GS_TypeContext> GS_TypeContext::Create() {
        return std::make_shared<GS_TypeContext>();
    }

    std::shared_ptr<Semantic::GS_VoidType> GS_TypeContext::GetVoidType() const {
        return _voidType;
    }

    std::shared_ptr<Semantic::GS_I32Type> GS_TypeContext::GetI32Type() const {
        return _i32Type;
    }

    std::shared_ptr<Semantic::GS_StringType> GS_TypeContext::GetStringType() const {
        return _stringType;
    }

}
