#include <GS_Expression.h>

namespace GSLanguageCompiler::AST {

    GS_Expression::GS_Expression() = default;

    Bool GS_Expression::isExpression() {
        return true;
    }

}
