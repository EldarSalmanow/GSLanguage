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
         * Constructor for variable using expression
         * @param name Variable name
         * @param scope Scope
         */
        GS_VariableUsingExpression(UString name, GSScopePtr scope);

    public:

        /**
         * Creating variable using expression ptr
         * @param name Variable name
         * @param scope Scope
         * @return Variable using expression ptr
         */
        static SharedPtr<GS_VariableUsingExpression> Create(UString name, GSScopePtr scope);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        LRef<UString> getName();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType getExpressionType() const override;

    private:

        /**
         * Variable name
         */
        UString _name;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H
