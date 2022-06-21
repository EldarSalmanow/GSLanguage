#include <GS_Statement.h>

namespace GSLanguageCompiler::AST {

    GS_Statement::GS_Statement() = default;

    Bool GS_Statement::IsStatement() const {
        return true;
    }

    GSStatementPtr ToStatement(ConstLRef<GSNodePtr> node) {
        if (node->IsStatement()) {
            return std::reinterpret_pointer_cast<GS_Statement>(node);
        }

        return nullptr;
    }

}
