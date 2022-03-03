#include <GS_Statement.h>

namespace GSLanguageCompiler::AST {

    GS_Statement::GS_Statement(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Statement::isStatement() const {
        return true;
    }

    GSStatementPtr ToStatement(GSNodePtr node) {
        if (node->isStatement()) {
            return std::reinterpret_pointer_cast<GS_Statement>(node);
        }

        return nullptr;
    }

}
