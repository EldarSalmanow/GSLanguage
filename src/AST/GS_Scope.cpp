#include <Semantic/GS_TableOfSymbols.h>

#include <GS_Scope.h>

namespace GSLanguageCompiler::AST {

    GS_Scope::GS_Scope(GSScopePtr parent)
            : _parent(std::move(parent)), _tableOfSymbols(std::make_shared<Semantic::GS_TableOfSymbols>()) {}

    GSScopePtr GS_Scope::Create(GSScopePtr scope) {
        return std::make_shared<GS_Scope>(std::move(scope));
    }

    GSScopePtr GS_Scope::CreateGlobalScope() {
        return GS_Scope::Create(nullptr);
    }

    Void GS_Scope::AddScope(GSScopePtr scope) {
        _scopes.emplace_back(std::move(scope));
    }

    Void GS_Scope::AddNode(GSNodePtr node) {
        _nodes.emplace_back(std::move(node));
    }

    Void GS_Scope::ReplaceNode(GSNodePtr oldNode, GSNodePtr newNode) {
        std::replace(_nodes.begin(), _nodes.end(), oldNode, newNode);
    }

    GSScopePtr GS_Scope::GetParent() const {
        return _parent;
    }

    GSScopePtrArray GS_Scope::GetScopes() const {
        return _scopes;
    }

    GSNodePtrArray GS_Scope::GetNodes() const {
        return _nodes;
    }

    Semantic::GSTableOfSymbolsPtr GS_Scope::GetTableOfSymbols() const {
        return _tableOfSymbols;
    }

}
