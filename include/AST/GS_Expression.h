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
        ArrayExpression,
        VariableUsingExpression,
        FunctionCallingExpression
    };

    /**
     * Class for all language grammar expressions
     */
    class GS_Expression : public GS_Node {
    public:

        /*
         *
         * GS_Expression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for expression
         */
        GS_Expression();

    public:

        /*
         *
         * GS_Expression PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Is expression
         * @return Is expression
         */
        Bool IsExpression() const override;

    public:

        /*
         *
         * GS_Expression PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for expression type
         * @return Expression type
         */
        virtual ExpressionType GetExpressionType() const = 0;
    };

    /**
     * Expression ptr type
     */
    using GSExpressionPtr = std::shared_ptr<GS_Expression>;

    /**
     * Expression ptr array type
     */
    using GSExpressionPtrArray = std::vector<GSExpressionPtr>;

    /**
     * Casting to expression if node is expression
     * @param node Node
     * @return Expression or null
     */
    GSExpressionPtr ToExpression(ConstLRef<GSNodePtr> node);

    /**
     * Declaring expressions for cast function
     */
    class GS_ConstantExpression;
    class GS_UnaryExpression;
    class GS_BinaryExpression;
    class GS_ArrayExpression;
    class GS_VariableUsingExpression;
    class GS_FunctionCallingExpression;

    /**
     * Casting to ExpressionT if node is expression
     * @tparam ExpressionT Type of expression
     * @param node Node
     * @return Expression or null
     */
    template<typename ExpressionT>
    inline NodePtr<ExpressionT> ToExpression(ConstLRef<GSNodePtr> node) {
        static_assert(std::is_base_of_v<GS_Expression, ExpressionT>,
                      "Type for casting must be inherited from GS_Expression!");

        auto expression = ToExpression(node);

        if (!expression) {
            return nullptr;
        }

        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression:
                if constexpr (!std::is_same_v<GS_ConstantExpression, ExpressionT>) {
                    return nullptr;
                }

                break;
            case ExpressionType::UnaryExpression:
                if constexpr (!std::is_same_v<GS_UnaryExpression, ExpressionT>) {
                    return nullptr;
                }

                break;
            case ExpressionType::BinaryExpression:
                if constexpr (!std::is_same_v<GS_BinaryExpression, ExpressionT>) {
                    return nullptr;
                }

                break;
            case ExpressionType::ArrayExpression:
                if constexpr (!std::is_same_v<GS_ArrayExpression, ExpressionT>) {
                    return nullptr;
                }

                break;
            case ExpressionType::VariableUsingExpression:
                if constexpr (!std::is_same_v<GS_VariableUsingExpression, ExpressionT>) {
                    return nullptr;
                }

                break;
            case ExpressionType::FunctionCallingExpression:
                if constexpr (!std::is_same_v<GS_FunctionCallingExpression, ExpressionT>) {
                    return nullptr;
                }

                break;
        }

        return std::reinterpret_pointer_cast<ExpressionT>(expression);
    }

    /**
     * Checking is left value expression
     * @param expression Expression
     * @return Is left value expression
     */
    inline Bool IsLValueExpression(ConstLRef<GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::VariableUsingExpression:
                return true;
            default:
                return false;
        }
    }

    /**
     * Checking is right value expression
     * @param expression Expression
     * @return Is right value expression
     */
    inline Bool IsRValueExpression(ConstLRef<GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
            case ExpressionType::ConstantExpression:
            case ExpressionType::UnaryExpression:
            case ExpressionType::BinaryExpression:
            case ExpressionType::ArrayExpression:
            case ExpressionType::VariableUsingExpression:
            case ExpressionType::FunctionCallingExpression:
                return true;
            default:
                return false;
        }
    }

}

#endif //GSLANGUAGE_GS_EXPRESSION_H
