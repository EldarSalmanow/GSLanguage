#include <GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    GS_Declaration::GS_Declaration() = default;

    Bool GS_Declaration::isDeclaration() {
        return true;
    }

}
