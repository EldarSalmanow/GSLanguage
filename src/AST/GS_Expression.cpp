#include <GS_Expression.h>

namespace GSLanguageCompiler::AST {

    GS_Expression::GS_Expression() = default;

    Bool GS_Expression::IsExpression() const {
        return true;
    }

    GSExpressionPtr ToExpression(ConstLRef<GSNodePtr> node) {
        if (node->IsExpression()) {
            return std::reinterpret_pointer_cast<GS_Expression>(node);
        }

        return nullptr;
    }

}
