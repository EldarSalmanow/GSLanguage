#include <GS_Node.h>

namespace GSLanguageCompiler::AST {

    GS_Node::GS_Node(GSScopePtr scope)
            : _scope(std::move(scope)) {}

    GS_Node::~GS_Node() = default;

    GSScopePtr GS_Node::getScope() {
        return _scope;
    }

    Bool GS_Node::isDeclaration() {
        return false;
    }

    Bool GS_Node::isStatement() {
        return false;
    }

    Bool GS_Node::isExpression() {
        return false;
    }

}
