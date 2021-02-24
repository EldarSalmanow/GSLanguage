#ifndef GSLANGUAGE_GS_EXPRESSION_H
#define GSLANGUAGE_GS_EXPRESSION_H

namespace GSLanguageCompiler {

    enum class ExpressionType {

    };

    /**
     * Base class for expressions
     */
    class GS_Expression {
    public:

        /**
         * Getter for expression type
         * @return
         */
        virtual ExpressionType getExpressionType() = 0;
    };

    typedef std::shared_ptr<GS_Expression> GSExpressionPointer;

}

#endif //GSLANGUAGE_GS_EXPRESSION_H
