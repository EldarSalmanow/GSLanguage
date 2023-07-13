#ifndef GSLANGUAGE_GS_RANGEEXPRESSION_H
#define GSLANGUAGE_GS_RANGEEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for range expression in language grammar
     */
    class GS_RangeExpression : public GS_Expression {
    public:

        /*
         *
         * GS_RangeExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for range expression
         * @param startExpression Start expression
         * @param endExpression End expression
         */
        GS_RangeExpression(GSExpressionPtr startExpression,
                           GSExpressionPtr endExpression);

    public:

        /*
         *
         * GS_RangeExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating range expression
         * @param startExpression Start expression
         * @param endExpression End expression
         * @return Range expression ptr
         */
        static std::shared_ptr<GS_RangeExpression> Create(GSExpressionPtr startExpression,
                                                          GSExpressionPtr endExpression);

    public:

        /*
         *
         * GS_RangeExpression PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for start expression
         * @return Start expression
         */
        LRef<GSExpressionPtr> GetStartExpression();

        /**
         * Getter for end expression
         * @return End expression
         */
        LRef<GSExpressionPtr> GetEndExpression();

    public:

        /*
         *
         * GS_RangeExpression PUBLIC OVERRIDE METHODS
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
         * GS_RangeExpression PRIVATE FIELDS
         *
         */

        /**
         * Start expression
         */
        GSExpressionPtr _startExpression;

        /**
         * End expression
         */
        GSExpressionPtr _endExpression;
    };

}

#endif //GSLANGUAGE_GS_RANGEEXPRESSION_H
