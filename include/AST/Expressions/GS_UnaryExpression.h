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
         * Constructor for unary expression
         * @param operation Unary operation
         * @param expression Expression ptr
         * @param scope Scope
         */
        GS_UnaryExpression(UnaryOperation operation, GSExpressionPtr expression, GSScopePtr scope);

    public:

        /**
         * Creating unary expression ptr
         * @param operation Unary operation
         * @param expression Expression ptr
         * @param scope Scope
         * @return Unary expression ptr
         */
        static SharedPtr<GS_UnaryExpression> Create(UnaryOperation operation, GSExpressionPtr expression, GSScopePtr scope);

    public:

        /**
         * Getter for unary operation
         * @return Unary operation
         */
        LRef<UnaryOperation> getUnaryOperation();

        /**
         * Getter for expression ptr
         * @return Expression ptr
         */
        LRef<GSExpressionPtr> getExpression();

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
