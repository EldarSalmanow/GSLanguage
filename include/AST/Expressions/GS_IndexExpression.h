#ifndef GSLANGUAGE_GS_INDEXEXPRESSION_H
#define GSLANGUAGE_GS_INDEXEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for index expression in language grammar
     */
    class GS_IndexExpression : public GS_Expression {
    public:

        /*
         *
         * GS_IndexExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for index expression
         * @param expression Expression
         * @param index Index
         */
        GS_IndexExpression(GSExpressionPtr expression,
                           GSExpressionPtr index);

    public:

        /*
         *
         * GS_IndexExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating index expression
         * @param expression Expression
         * @param index Index
         * @return Index expression
         */
        static std::shared_ptr<GS_IndexExpression> Create(GSExpressionPtr expression,
                                                          GSExpressionPtr index);

    public:

        /*
         *
         * GS_IndexExpression PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for expression
         * @return Expression
         */
        LRef<GSExpressionPtr> GetExpression();

        /**
         * Getter for index
         * @return Index
         */
        LRef<GSExpressionPtr> GetIndex();

    public:

        /*
         *
         * GS_IndexExpression PUBLIC OVERRIDE METHODS
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
         * GS_IndexExpression PRIVATE FIELDS
         *
         */

        /**
         * Expression
         */
        GSExpressionPtr _expression;

        /**
         * Index
         */
        GSExpressionPtr _index;
    };

}

#endif //GSLANGUAGE_GS_INDEXEXPRESSION_H
