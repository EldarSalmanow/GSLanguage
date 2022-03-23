#include <Declarations/GS_TranslationUnitDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_TranslationUnitDeclaration::GS_TranslationUnitDeclaration(UString name, GSNodePtrArray nodes, GSScopePtr scope)
            : _name(std::move(name)), _nodes(std::move(nodes)), _globalScope(std::move(scope)), GS_Declaration(nullptr) {}

    SharedPtr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name, GSNodePtrArray nodes, GSScopePtr scope) {
        return std::make_shared<GS_TranslationUnitDeclaration>(std::move(name), std::move(nodes), std::move(scope));
    }

    SharedPtr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name, GSScopePtr scope) {
        return GS_TranslationUnitDeclaration::Create(std::move(name), GSNodePtrArray(), std::move(scope));
    }

    SharedPtr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name) {
        return GS_TranslationUnitDeclaration::Create(std::move(name), GS_Scope::CreateGlobalScope());
    }

    Void GS_TranslationUnitDeclaration::AddNode(GSNodePtr node) {
        _nodes.emplace_back(std::move(node));
    }

    LRef<UString> GS_TranslationUnitDeclaration::GetName() {
        return _name;
    }

    LRef<GSNodePtrArray> GS_TranslationUnitDeclaration::GetNodes() {
        return _nodes;
    }

    LRef<GSScopePtr> GS_TranslationUnitDeclaration::GetGlobalScope() {
        return _globalScope;
    }

    DeclarationType GS_TranslationUnitDeclaration::GetDeclarationType() const {
        return DeclarationType::TranslationUnitDeclaration;
    }

}
