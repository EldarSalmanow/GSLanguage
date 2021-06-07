#ifndef GSLANGUAGE_GS_VALUEEXPRESSION_H
#define GSLANGUAGE_GS_VALUEEXPRESSION_H

#include <Parser/Expressions/GS_Expression.h>

#include <Parser/Values/GS_Value.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_ValueExpression : public GS_Expression {
    public:

        /**
         *
         * @param value
         */
        GS_ValueExpression(GSValuePointer value);

        /**
         *
         * @param value
         * @param type
         */
//        GS_ValueExpression(GSValuePointer value, const std::string &type);

    public:

        /**
         *
         * @return
         */
        GSValuePointer getValue();

        /**
         *
         * @return
         */
//        Literal getType();

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
        GSValuePointer _value;

        /**
         *
         */
//        Literal _type;
    };

}

#endif //GSLANGUAGE_GS_VALUEEXPRESSION_H
