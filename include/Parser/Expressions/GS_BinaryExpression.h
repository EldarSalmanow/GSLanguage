#ifndef GSLANGUAGE_GS_BINARYEXPRESSION_H
#define GSLANGUAGE_GS_BINARYEXPRESSION_H

#include <Parser/Expressions/GS_Expression.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    enum class BinaryOperation : char {
        PLUS  = '+',
        MINUS = '-',
        STAR  = '*',
        SLASH = '/'
    };

    /**
     *
     */
    class GS_BinaryExpression : public GS_Expression {
    public:

        /**
         *
         * @param operation
         * @param firstValue
         * @param secondValue
         */
        GS_BinaryExpression(BinaryOperation operation,
                            GSExpressionPointer firstValue,
                            GSExpressionPointer secondValue);

    public:

        /**
         *
         * @return
         */
        ExpressionType getExpressionType() override;

        /**
         *
         * @return
         */
        std::string generateCode() override;

        /**
         *
         * @return
         */
        std::string toStringForDebug() override;

    private:

        /**
         *
         */
        BinaryOperation _operation;

        /**
         *
         */
        GSExpressionPointer _firstExpression;

        /**
         *
         */
        GSExpressionPointer _secondExpression;
    };

}

#endif //GSLANGUAGE_GS_BINARYEXPRESSION_H
