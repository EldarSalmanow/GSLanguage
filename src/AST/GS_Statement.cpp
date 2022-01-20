#include <GS_Statement.h>

namespace GSLanguageCompiler::AST {

    GS_Statement::GS_Statement(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Statement::isStatement() const {
        return true;
    }

}
