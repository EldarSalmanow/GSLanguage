#include <GS_Expression.h>

namespace GSLanguageCompiler::AST {

    GS_Expression::GS_Expression(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Expression::isExpression() const {
        return true;
    }

    GSExpressionPtr ToExpression(GSNodePtr node) {
        if (node->isExpression()) {
            return std::reinterpret_pointer_cast<GS_Expression>(node);
        }

        return nullptr;
    }

}
