#ifndef GSLANGUAGE_GS_UNARYEXPRESSION_H
#define GSLANGUAGE_GS_UNARYEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Supported unary operations
     */
    enum class UnaryOperation {
        Neg, // -

        Not  // !
    };

    /**
     * Class for unary expression in language grammar
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
         * @param expression Expression
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
         * Creating unary expression
         * @param operation Unary operation
         * @param expression Expression
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
         * Getter for expression
         * @return Expression
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
         * Expression
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_UNARYEXPRESSION_H
