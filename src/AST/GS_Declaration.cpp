#include <GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    GS_Declaration::GS_Declaration() = default;

    Bool GS_Declaration::IsDeclaration() const {
        return true;
    }

    GSDeclarationPtr ToDeclaration(ConstLRef<GSNodePtr> node) {
        if (node->IsDeclaration()) {
            return std::reinterpret_pointer_cast<GS_Declaration>(node);
        }

        return nullptr;
    }

}
