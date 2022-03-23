#include <GS_Type.h>

namespace GSLanguageCompiler::AST {

    GS_Type::GS_Type(UString name)
            : _name(std::move(name)) {}

    SharedPtr<GS_Type> GS_Type::Create(UString name) {
        return std::make_shared<GS_Type>(std::move(name));
    }

    UString GS_Type::GetName() const {
        return _name;
    }

    GS_VoidType::GS_VoidType()
            : GS_Type(U"Void") {}

    SharedPtr<GS_VoidType> GS_VoidType::Create() {
        return std::make_shared<GS_VoidType>();
    }

    GS_I32Type::GS_I32Type()
            : GS_Type(U"I32") {}

    SharedPtr<GS_I32Type> GS_I32Type::Create() {
        return std::make_shared<GS_I32Type>();
    }

    GS_StringType::GS_StringType()
            : GS_Type(U"String") {}

    SharedPtr<GS_StringType> GS_StringType::Create() {
        return std::make_shared<GS_StringType>();
    }

    Bool isBaseType(GSTypePtr type) {
        auto typeName = type->GetName();

        if (typeName == U"Void"_us || typeName == U"I32"_us || typeName == U"String"_us) {
            return true;
        } else {
            return false;
        }
    }

}
