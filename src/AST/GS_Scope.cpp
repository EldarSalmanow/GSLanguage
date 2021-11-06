#include <GS_Scope.h>

namespace GSLanguageCompiler::AST {

    GS_Scope::GS_Scope(GSScopePtr parent)
            : _parent(std::move(parent)) {}

    Void GS_Scope::addScope(GSScopePtr scope) {
        _scopes.emplace_back(std::move(scope));
    }

    Void GS_Scope::addNode(GSNodePtr node) {
        _nodes.emplace_back(std::move(node));
    }

    GSScopePtr GS_Scope::getParent() {
        return _parent;
    }

    GSScopePtrArray GS_Scope::getScopes() {
        return _scopes;
    }

    GSNodePtrArray GS_Scope::getNodes() {
        return _nodes;
    }

    Semantic::GSTableOfSymbolsPtr GS_Scope::getTableOfSymbols() {
        return _tableOfSymbols;
    }

}
