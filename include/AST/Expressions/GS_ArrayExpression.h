#ifndef GSLANGUAGE_GS_ARRAYEXPRESSION_H
#define GSLANGUAGE_GS_ARRAYEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for array expressions
     */
    class GS_ArrayExpression : public GS_Expression {
    public:

        /**
         * Constructor for array expression
         * @param expressions Expressions
         */
        explicit GS_ArrayExpression(GSExpressionPtrArray expressions);

    public:

        /**
         * Creating array expression
         * @param expressions Expressions
         * @return Array expression ptr
         */
        static std::shared_ptr<GS_ArrayExpression> Create(GSExpressionPtrArray expressions);

    public:

        /**
         * Getter for expressions
         * @return Expressions
         */
        LRef<GSExpressionPtrArray> GetExpressions();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType GetExpressionType() const override;

    private:

        /**
         * Expressions
         */
        GSExpressionPtrArray _expressions;
    };

}

#endif //GSLANGUAGE_GS_ARRAYEXPRESSION_H
