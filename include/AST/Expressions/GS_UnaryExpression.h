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

        /*
         *
         * GS_UnaryExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for unary expression
         * @param operation Unary operation
         * @param expression Expression ptr
         */
        GS_UnaryExpression(UnaryOperation operation,
                           GSExpressionPtr expression);

    public:

        /*
         *
         * GS_UnaryExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating unary expression ptr
         * @param operation Unary operation
         * @param expression Expression ptr
         * @return Unary expression ptr
         */
        static std::shared_ptr<GS_UnaryExpression> Create(UnaryOperation operation,
                                                          GSExpressionPtr expression);

    public:

        /*
         *
         * GS_UnaryExpression PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for unary operation
         * @return Unary operation
         */
        LRef<UnaryOperation> GetUnaryOperation();

        /**
         * Getter for expression ptr
         * @return Expression ptr
         */
        LRef<GSExpressionPtr> GetExpression();

    public:

        /*
         *
         * GS_UnaryExpression PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType GetExpressionType() const override;

    private:

        /*
         *
         * GS_UnaryExpression PRIVATE FIELDS
         *
         */

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
