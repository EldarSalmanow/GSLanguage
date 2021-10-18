#include <GS_Type.h>

namespace GSLanguageCompiler::AST {

    GS_Type::GS_Type(String name)
            : _name(std::move(name)) {}

    String GS_Type::getName() {
        return _name;
    }

    GS_I32Type::GS_I32Type()
            : GS_Type("I32") {}

    GS_StringType::GS_StringType()
            : GS_Type("String") {}

    Bool isBaseType(GSTypePtr type) {
        auto inputType = std::move(type);
        auto typeName = inputType->getName();

        if (typeName == "Void" || typeName == "I32" || typeName == "String") {
            return true;
        } else {
            return false;
        }
    }

}
