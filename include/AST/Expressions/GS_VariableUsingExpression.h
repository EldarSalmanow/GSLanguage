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
         */
        explicit GS_VariableUsingExpression(UString name);

    public:

        /**
         * Creating variable using expression ptr
         * @param name Variable name
         * @return Variable using expression ptr
         */
        static std::shared_ptr<GS_VariableUsingExpression> Create(UString name);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        LRef<UString> GetName();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType GetExpressionType() const override;

    private:

        /**
         * Variable name
         */
        UString _name;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H
