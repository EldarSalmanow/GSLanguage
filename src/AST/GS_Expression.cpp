#include <GS_Expression.h>

namespace GSLanguageCompiler::AST {

    GS_Expression::GS_Expression(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Expression::isExpression() {
        return true;
    }

}
