#include <GS_Statement.h>

namespace GSLanguageCompiler::AST {

    GS_Statement::GS_Statement() = default;

    Bool GS_Statement::isStatement() {
        return true;
    }

}
