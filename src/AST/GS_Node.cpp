#include <GS_Node.h>

namespace GSLanguageCompiler::AST {

    GS_Node::~GS_Node() = default;

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
