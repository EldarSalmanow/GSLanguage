#include <GS_Type.h>

namespace GSLanguageCompiler::AST {

    GS_Type::GS_Type(UString name)
            : _name(std::move(name)) {}

    UString GS_Type::getName() const {
        return _name;
    }

    GS_VoidType::GS_VoidType()
            : GS_Type(U"Void") {}

    GS_I32Type::GS_I32Type()
            : GS_Type(U"I32") {}

    GS_StringType::GS_StringType()
            : GS_Type(U"String") {}

    Bool isBaseType(GSTypePtr type) {
        auto inputType = std::move(type);
        auto typeName = inputType->getName();

        if (typeName == U"Void" || typeName == U"I32" || typeName == U"String") {
            return true;
        } else {
            return false;
        }
    }

}
