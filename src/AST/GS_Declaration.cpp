#include <GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    GS_Declaration::GS_Declaration(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Declaration::IsDeclaration() const {
        return true;
    }

    GSDeclarationPtr ToDeclaration(GSNodePtr node) {
        if (node->IsDeclaration()) {
            return std::reinterpret_pointer_cast<GS_Declaration>(node);
        }

        return nullptr;
    }

}
