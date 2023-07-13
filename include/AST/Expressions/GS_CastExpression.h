#ifndef GSLANGUAGE_GS_CASTEXPRESSION_H
#define GSLANGUAGE_GS_CASTEXPRESSION_H

#include <Semantic/GS_Type.h>

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for cast expression in language grammar
     */
    class GS_CastExpression : public GS_Expression {
    public:

        /*
         *
         * GS_CastExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for cast expression
         * @param expression Expression
         * @param type Type
         */
        GS_CastExpression(GSExpressionPtr expression,
                          Semantic::GSTypePtr type);

    public:

        /*
         *
         * GS_CastExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating cast expression
         * @param expression Expression
         * @param type Type
         * @return Cast expression ptr
         */
        static std::shared_ptr<GS_CastExpression> Create(GSExpressionPtr expression,
                                                         Semantic::GSTypePtr type);

    public:

        /*
         *
         * GS_CastExpression PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for expression
         * @return Expression
         */
        LRef<GSExpressionPtr> GetExpression();

        /**
         * Getter for type
         * @return Type
         */
        LRef<Semantic::GSTypePtr> GetType();

    public:

        /*
         *
         * GS_CastExpression PUBLIC OVERRIDE METHODS
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
         * GS_CastExpression PRIVATE FIELDS
         *
         */

        /**
         * Expression
         */
        GSExpressionPtr _expression;

        /**
         * Type
         */
        Semantic::GSTypePtr _type;
    };

}

#endif //GSLANGUAGE_GS_CASTEXPRESSION_H
