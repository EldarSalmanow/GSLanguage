#ifndef GSLANGUAGE_GS_FUNCTIONCALLINGEXPRESSION_H
#define GSLANGUAGE_GS_FUNCTIONCALLINGEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for function calling expression in language grammar
     */
    class GS_FunctionCallingExpression : public GS_Expression {
    public:

        /**
         * Constructor for GS_FunctionCallingExpression
         * @param name Function name
         * @param params Function params
         * @param scope Scope
         */
        GS_FunctionCallingExpression(String name, GSExpressionPtrArray params, GSScopePtr scope);

    public:

        /**
         * Getter for function name
         * @return Function name
         */
        String getName();

        /**
         * Getter for params
         * @return Params
         */
        GSExpressionPtrArray getParams();

    public:

        /**
         *
         * @param visitor
         * @return
         */
        Void accept(GS_Visitor *visitor) override;

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType getExpressionType() override;

    private:

        /**
         * Function name
         */
        String _name;

        /**
         * Params for calling function
         */
        GSExpressionPtrArray _params;
    };

}

#endif //GSLANGUAGE_GS_FUNCTIONCALLINGEXPRESSION_H
