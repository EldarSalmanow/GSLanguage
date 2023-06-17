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

        /*
         *
         * GS_VariableUsingExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for variable using expression
         * @param name Variable name
         * @param nameLocationRange Variable name source location range
         */
        GS_VariableUsingExpression(UString name,
                                   IO::GS_SourceRange nameLocationRange);

    public:

        /*
         *
         * GS_VariableUsingExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating variable using expression
         * @param name Variable name
         * @param nameLocation Variable name source location range
         * @return Variable using expression ptr
         */
        static std::shared_ptr<GS_VariableUsingExpression> Create(UString name,
                                                                  IO::GS_SourceRange nameLocationRange);

        /**
         * Creating variable using expression
         * @param name Variable name
         * @return Variable using expression ptr
         */
        static std::shared_ptr<GS_VariableUsingExpression> Create(UString name);

    public:

        /*
         *
         * GS_VariableUsingExpression PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for variable name
         * @return Variable name
         */
        LRef<UString> GetName();

        /**
         * Getter for variable name source location range
         * @return Variable name source location range
         */
        ConstLRef<IO::GS_SourceRange> GetNameLocationRange() const;

    public:

        /*
         *
         * GS_VariableUsingExpression PUBLIC OVERRIDE METHODS
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
         * GS_VariableUsingExpression PRIVATE FIELDS
         *
         */

        /**
         * Variable name
         */
        UString _name;

        /**
         * Variable name source location range
         */
        IO::GS_SourceRange _nameLocationRange;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEUSINGEXPRESSION_H
