#include <Declarations/GS_TranslationUnitDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_TranslationUnitDeclaration::GS_TranslationUnitDeclaration(UString name, GSNodePtrArray nodes)
            : _name(std::move(name)), _nodes(std::move(nodes)) {}

    SharedPtr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name, GSNodePtrArray nodes) {
        return std::make_shared<GS_TranslationUnitDeclaration>(std::move(name), std::move(nodes));
    }

    SharedPtr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name) {
        return GS_TranslationUnitDeclaration::Create(std::move(name), GSNodePtrArray());
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

    DeclarationType GS_TranslationUnitDeclaration::GetDeclarationType() const {
        return DeclarationType::TranslationUnitDeclaration;
    }

}
