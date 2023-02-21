#ifndef GSLANGUAGE_GS_BINARYEXPRESSION_H
#define GSLANGUAGE_GS_BINARYEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Supported binary operations
     */
    enum class BinaryOperation {
        Plus,
        Minus,
        Star,
        Slash
    };

    /**
     * Class for binary expressions in language grammar
     */
    class GS_BinaryExpression : public GS_Expression {
    public:

        /*
         *
         * GS_BinaryExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for binary expression
         * @param operation Binary operation
         * @param firstNode First expression
         * @param secondNode Second expression
         */
        GS_BinaryExpression(BinaryOperation operation,
                            GSExpressionPtr firstExpression,
                            GSExpressionPtr secondExpression);

    public:

        /*
         *
         * GS_BinaryExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating binary expression
         * @param operation Binary operation
         * @param firstExpression First expression
         * @param secondExpression Second expression
         * @return Binary expression ptr
         */
        static std::shared_ptr<GS_BinaryExpression> Create(BinaryOperation operation,
                                                           GSExpressionPtr firstExpression,
                                                           GSExpressionPtr secondExpression);

    public:

        /*
         *
         * GS_BinaryExpression PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for binary operation
         * @return Binary operation
         */
        LRef<BinaryOperation> GetBinaryOperation();

        /**
         * Getter for first expression
         * @return First expression
         */
        LRef<GSExpressionPtr> GetFirstExpression();

        /**
         * Getter for second expression
         * @return Second expression
         */
        LRef<GSExpressionPtr> GetSecondExpression();

    public:

        /*
         *
         * GS_BinaryExpression PUBLIC OVERRIDE METHODS
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
         * GS_BinaryExpression PRIVATE FIELDS
         *
         */

        /**
         * Binary operation
         */
        BinaryOperation _operation;

        /**
         * First expression
         */
        GSExpressionPtr _firstExpression;

        /*
         * Second expression
         */
        GSExpressionPtr _secondExpression;
    };

}

#endif //GSLANGUAGE_GS_BINARYEXPRESSION_H
