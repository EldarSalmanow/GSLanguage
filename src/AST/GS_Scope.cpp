#include <Semantic/GS_TableOfSymbols.h>

#include <GS_Scope.h>

namespace GSLanguageCompiler::AST {

    GS_Scope::GS_Scope(GSScopePtr parent)
            : _parent(std::move(parent)), _tableOfSymbols(std::make_shared<Semantic::GS_TableOfSymbols>()) {}

    Void GS_Scope::addScope(GSScopePtr scope) {
        _scopes.emplace_back(std::move(scope));
    }

    Void GS_Scope::addNode(GSNodePtr node) {
        _nodes.emplace_back(std::move(node));
    }

    Void GS_Scope::replaceNode(GSNodePtr oldNode, GSNodePtr newNode) {
        std::replace(_nodes.begin(), _nodes.end(), oldNode, newNode);
    }

    GSScopePtr GS_Scope::getParent() const {
        return _parent;
    }

    GSScopePtrArray GS_Scope::getScopes() const {
        return _scopes;
    }

    GSNodePtrArray GS_Scope::getNodes() const {
        return _nodes;
    }

    Semantic::GSTableOfSymbolsPtr GS_Scope::getTableOfSymbols() const {
        return _tableOfSymbols;
    }

}
