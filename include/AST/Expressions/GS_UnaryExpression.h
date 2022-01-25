#ifndef GSLANGUAGE_GS_UNARYEXPRESSION_H
#define GSLANGUAGE_GS_UNARYEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Supported unary operations
     */
    enum class UnaryOperation {
        Minus
    };

    /**
     * Class for unary expressions in language grammar
     */
    class GS_UnaryExpression : public GS_Expression {
    public:

        /**
         * Constructor for GS_UnaryExpression
         * @param operation Unary operation
         * @param node Expression ptr
         * @param scope Scope
         */
        GS_UnaryExpression(UnaryOperation operation, GSExpressionPtr expression, GSScopePtr scope);

    public:

        /**
         * Getter for unary operation
         * @return Unary operation
         */
        UnaryOperation getUnaryOperation() const;

        /**
         * Getter for expression ptr
         * @return Expression ptr
         */
        GSExpressionPtr getExpression() const;

    public:

        /**
         *
         * @param visitor
         * @return
         */
        Any accept(Ptr<GS_Visitor> visitor) override;

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType getExpressionType() const override;

    private:

        /**
         * Unary operation
         */
        UnaryOperation _operation;

        /**
         * Expression ptr
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_UNARYEXPRESSION_H
