#include <GS_Expression.h>

namespace GSLanguageCompiler::AST {

    GS_Expression::GS_Expression(GSScopePtr scope)
            : GS_Node(std::move(scope)) {}

    Bool GS_Expression::IsExpression() const {
        return true;
    }

    GSExpressionPtr ToExpression(GSNodePtr node) {
        if (node->IsExpression()) {
            return std::reinterpret_pointer_cast<GS_Expression>(node);
        }

        return nullptr;
    }

}
