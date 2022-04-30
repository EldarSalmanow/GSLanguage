#include <GS_Type.h>

namespace GSLanguageCompiler::AST {

    GS_Type::GS_Type(UString name)
            : _name(std::move(name)) {}

    GS_Type::~GS_Type() = default;

    SharedPtr<GS_Type> GS_Type::Create(UString name) {
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

    SharedPtr<GS_LiteralType> GS_LiteralType::Create(UString name) {
        return std::make_shared<GS_LiteralType>(std::move(name));
    }

    Bool GS_LiteralType::IsLiteralType() const {
        return true;
    }

    GS_VoidType::GS_VoidType()
            : GS_LiteralType("Void"_us) {}

    SharedPtr<GS_VoidType> GS_VoidType::Create() {
        return std::make_shared<GS_VoidType>();
    }

    GS_I32Type::GS_I32Type()
            : GS_LiteralType("I32"_us) {}

    SharedPtr<GS_I32Type> GS_I32Type::Create() {
        return std::make_shared<GS_I32Type>();
    }

    GS_StringType::GS_StringType()
            : GS_LiteralType("String"_us) {}

    SharedPtr<GS_StringType> GS_StringType::Create() {
        return std::make_shared<GS_StringType>();
    }

    Bool isBaseType(GSTypePtr type) {
        auto typeName = type->GetName();

        return typeName == "Void"_us || typeName == "I32"_us || typeName == "String"_us;
    }

}
