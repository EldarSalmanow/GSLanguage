#ifndef GSLANGUAGE_GS_UNARYEXPRESSION_H
#define GSLANGUAGE_GS_UNARYEXPRESSION_H

#include <Parser/Expressions/GS_Expression.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    enum class UnaryOperation : char {
        MINUS = '-'
    };

    /**
     *
     */
    class GS_UnaryExpression : public GS_Expression {
    public:

        /**
         *
         */
        GS_UnaryExpression(UnaryOperation operation, GSExpressionPointer expression);

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
        UnaryOperation _operation;

        /**
         *
         */
        GSExpressionPointer _expression;
    };

}

#endif //GSLANGUAGE_GS_UNARYEXPRESSION_H
