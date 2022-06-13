#include <GS_Node.h>

namespace GSLanguageCompiler::AST {

    GS_Node::~GS_Node() = default;

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
