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

        /**
         * Constructor for binary expression
         * @param operation Binary operation
         * @param firstNode First expression ptr
         * @param secondNode Second expression ptr
         * @param scope Scope
         */
        GS_BinaryExpression(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression, GSScopePtr scope);

    public:

        /**
         * Creating binary expression ptr
         * @param operation Binary operation
         * @param firstExpression First expression ptr
         * @param secondExpression Second expression ptr
         * @param scope Scope
         * @return Binary expression ptr
         */
        static SharedPtr<GS_BinaryExpression> Create(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression, GSScopePtr scope);

    public:

        /**
         * Getter for binary operation
         * @return Binary operation
         */
        LRef<BinaryOperation> getBinaryOperation();

        /**
         * Getter for first expression ptr
         * @return First expression ptr
         */
        LRef<GSExpressionPtr> getFirstExpression();

        /**
         * Getter for second expression ptr
         * @return Second expression ptr
         */
        LRef<GSExpressionPtr> getSecondExpression();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType getExpressionType() const override;

    private:

        /**
         * Binary operation
         */
        BinaryOperation _operation;

        /**
         * First and second expressions
         */
        GSExpressionPtr _firstExpression, _secondExpression;
    };

}

#endif //GSLANGUAGE_GS_BINARYEXPRESSION_H
