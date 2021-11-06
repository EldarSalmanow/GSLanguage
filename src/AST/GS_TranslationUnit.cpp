#include <GS_TranslationUnit.h>

namespace GSLanguageCompiler::AST {

    GS_TranslationUnit::GS_TranslationUnit(GSNodePtrArray nodes, GSScopePtr scope)
            : _nodes(std::move(nodes)), _globalScope(std::move(scope)) {}

    GSNodePtrArray GS_TranslationUnit::getNodes() {
        return _nodes;
    }

    GSScopePtr GS_TranslationUnit::getScope() {
        return _globalScope;
    }

}
