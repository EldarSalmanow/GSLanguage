#include <GS_Statement.h>

namespace GSLanguageCompiler::AST {

    GS_Statement::GS_Statement(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Statement::IsStatement() const {
        return true;
    }

    GSStatementPtr ToStatement(GSNodePtr node) {
        if (node->IsStatement()) {
            return std::reinterpret_pointer_cast<GS_Statement>(node);
        }

        return nullptr;
    }

}
