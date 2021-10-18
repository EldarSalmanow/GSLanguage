#ifndef GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H
#define GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for variable using in language grammar
     */
    class GS_VariableUsingExpression : public GS_Expression {
    public:

        /**
         * Constructor for GS_VariableUsingExpression
         * @param name Variable name
         */
        explicit GS_VariableUsingExpression(String name);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        String getName();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType getExpressionType() override;

    private:

        /**
         * Variable name
         */
        String _name;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H
