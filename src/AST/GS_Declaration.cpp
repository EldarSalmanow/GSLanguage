#include <GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    GS_Declaration::GS_Declaration(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Declaration::isDeclaration() const {
        return true;
    }

}
