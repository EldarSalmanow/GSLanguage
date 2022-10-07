#include <Declarations/GS_TranslationUnitDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_TranslationUnitDeclaration::GS_TranslationUnitDeclaration(UString name, GSNodePtrArray nodes, U64 sourceHash)
            : _name(std::move(name)), _nodes(std::move(nodes)), _sourceHash(sourceHash) {}

    std::shared_ptr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name, GSNodePtrArray nodes, U64 sourceHash) {
        return std::make_shared<GS_TranslationUnitDeclaration>(std::move(name), std::move(nodes), sourceHash);
    }

    std::shared_ptr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name, GSNodePtrArray nodes) {
        return GS_TranslationUnitDeclaration::Create(std::move(name), std::move(nodes), 0);
    }

    std::shared_ptr<GS_TranslationUnitDeclaration> GS_TranslationUnitDeclaration::Create(UString name) {
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

    U64 GS_TranslationUnitDeclaration::GetSourceHash() const {
        return _sourceHash;
    }

    DeclarationType GS_TranslationUnitDeclaration::GetDeclarationType() const {
        return DeclarationType::TranslationUnitDeclaration;
    }

}
