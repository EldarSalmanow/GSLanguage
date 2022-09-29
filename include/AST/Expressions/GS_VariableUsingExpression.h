#ifndef GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H
#define GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H

#include <Lexer/GS_Token.h>

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
         * @param nameLocation Variable name location
         */
        GS_VariableUsingExpression(UString name, IO::GS_SourceLocation nameLocation);

    public:

        /**
         * Creating variable using expression ptr
         * @param name Variable name
         * @param nameLocation Variable name location
         * @return Variable using expression ptr
         */
        static std::shared_ptr<GS_VariableUsingExpression> Create(UString name, IO::GS_SourceLocation nameLocation);

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

        /**
         * Getter for variable name location
         * @return Variable name location
         */
        IO::GS_SourceLocation GetNameLocation() const;

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

        /**
         * Variable name location
         */
        IO::GS_SourceLocation _nameLocation;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H
