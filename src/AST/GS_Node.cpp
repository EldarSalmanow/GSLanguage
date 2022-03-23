#include <GS_Node.h>

namespace GSLanguageCompiler::AST {

    GS_Node::GS_Node(GSScopePtr scope)
            : _scope(std::move(scope)) {}

    GS_Node::~GS_Node() = default;

    LRef<GSScopePtr> GS_Node::GetScope() {
        return _scope;
    }

    Bool GS_Node::IsDeclaration() const {
        return false;
    }

    Bool GS_Node::IsStatement() const {
        return false;
    }

    Bool GS_Node::IsExpression() const {
        return false;
    }

}
