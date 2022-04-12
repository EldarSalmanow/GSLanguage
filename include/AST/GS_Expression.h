#ifndef GSLANGUAGE_GS_EXPRESSION_H
#define GSLANGUAGE_GS_EXPRESSION_H

#include <AST/GS_Node.h>

namespace GSLanguageCompiler::AST {

    /**
     * Expression type
     */
    enum class ExpressionType {
        ConstantExpression,
        UnaryExpression,
        BinaryExpression,
        VariableUsingExpression,
        FunctionCallingExpression
    };

    /**
     * Class for all language grammar expressions
     */
    class GS_Expression : public GS_Node {
    public:

        /**
         * Constructor for expression
         * @param scope Expression scope
         */
        explicit GS_Expression(GSScopePtr scope);

    public:

        /**
         * Is expression
         * @return Is expression
         */
        Bool IsExpression() const override;

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        virtual ExpressionType GetExpressionType() const = 0;
    };

    /**
     * Expression ptr type
     */
    using GSExpressionPtr = SharedPtr<GS_Expression>;

    /**
     * Expression ptr array type
     */
    using GSExpressionPtrArray = Vector<GSExpressionPtr>;

    /**
     * Casting to expression if node is expression
     * @param node Node
     * @return Expression or nullptr
     */
    GSExpressionPtr ToExpression(GSNodePtr node);

    /**
     * Casting to any type of expression if node is expression
     * @tparam T Type of expression
     * @param node Node
     * @return Expression or nullptr
     */
    template<typename T>
    SharedPtr<T> ToExpression(GSNodePtr node) {
        static_assert(std::is_base_of_v<GS_Expression, T>, "Type for casting must be inherited from GS_Expression!");

        auto expression = ToExpression(node);

        if (!expression) {
            return nullptr;
        }

        auto castedExpression = std::reinterpret_pointer_cast<T>(expression);

        return castedExpression;
    }

}

#endif //GSLANGUAGE_GS_EXPRESSION_H
