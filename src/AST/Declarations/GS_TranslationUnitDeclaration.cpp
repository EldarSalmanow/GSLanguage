#include <Declarations/GS_TranslationUnitDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_TranslationUnitDeclaration::GS_TranslationUnitDeclaration(GSNodePtrArray nodes, GSScopePtr scope)
            : _nodes(std::move(nodes)), _globalScope(std::move(scope)), GS_Declaration(nullptr) {}

    LRef<GSNodePtrArray> GS_TranslationUnitDeclaration::getNodes() {
        return _nodes;
    }

    LRef<GSScopePtr> GS_TranslationUnitDeclaration::getGlobalScope() {
        return _globalScope;
    }

    DeclarationType GS_TranslationUnitDeclaration::getDeclarationType() const {
        return DeclarationType::TranslationUnitDeclaration;
    }

}
