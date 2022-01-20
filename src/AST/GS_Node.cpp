#include <GS_Node.h>

namespace GSLanguageCompiler::AST {

    GS_Node::GS_Node(GSScopePtr scope)
            : _scope(std::move(scope)) {}

    GS_Node::~GS_Node() = default;

    GSScopePtr GS_Node::getScope() const {
        return _scope;
    }

    Bool GS_Node::isDeclaration() const {
        return false;
    }

    Bool GS_Node::isStatement() const {
        return false;
    }

    Bool GS_Node::isExpression() const {
        return false;
    }

}
