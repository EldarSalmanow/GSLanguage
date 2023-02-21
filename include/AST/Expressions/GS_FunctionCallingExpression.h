#ifndef GSLANGUAGE_GS_FUNCTIONCALLINGEXPRESSION_H
#define GSLANGUAGE_GS_FUNCTIONCALLINGEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for function calling expression in language grammar
     */
    class GS_FunctionCallingExpression : public GS_Expression {
    public:

        /*
         *
         * GS_FunctionCallingExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for function calling expression
         * @param name Function name
         * @param params Function params
         */
        GS_FunctionCallingExpression(UString name,
                                     GSExpressionPtrArray params);

    public:

        /*
         *
         * GS_FunctionCallingExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating function calling expression
         * @param name Function name
         * @param params Function params
         * @return Function calling expression ptr
         */
        static std::shared_ptr<GS_FunctionCallingExpression> Create(UString name,
                                                                    GSExpressionPtrArray params);

    public:

        /*
         *
         * GS_FunctionCallingExpression PUBLIC GETTER METHODS
         *
         */

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

        /*
         *
         * GS_FunctionCallingExpression PUBLIC OVERRIDE METHODS
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
         * GS_FunctionCallingExpression PRIVATE FIELDS
         *
         */

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
