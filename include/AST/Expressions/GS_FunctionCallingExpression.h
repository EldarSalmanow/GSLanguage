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
         * Constructor for function calling expression
         * @param name Function name
         * @param params Function params
         */
        GS_FunctionCallingExpression(UString name, GSExpressionPtrArray params);

    public:

        /**
         * Creating function calling expression ptr
         * @param name Function name
         * @param params Function params
         * @return Function calling expression ptr
         */
        static std::shared_ptr<GS_FunctionCallingExpression> Create(UString name, GSExpressionPtrArray params);

    public:

        /**
         * Getter for function name
         * @return Function name
         */
        LRef<UString> GetName();

        /**
         * Getter for params
         * @return Params
         */
        LRef<GSExpressionPtrArray> GetParams();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType GetExpressionType() const override;

    private:

        /**
         * Function name
         */
        UString _name;

        /**
         * Params for calling function
         */
        GSExpressionPtrArray _params;
    };

}

#endif //GSLANGUAGE_GS_FUNCTIONCALLINGEXPRESSION_H
