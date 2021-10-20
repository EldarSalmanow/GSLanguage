#ifndef GSLANGUAGE_GS_EXPRESSIONSTATEMENT_H
#define GSLANGUAGE_GS_EXPRESSIONSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for containing expression in statement
     */
    class GS_ExpressionStatement : public GS_Statement {
    public:

        /**
         * Constructor for GS_ExpressionStatement
         * @param expression Expression ptr
         */
        explicit GS_ExpressionStatement(GSExpressionPtr expression);

    public:

        /**
         * Getter for expression ptr
         * @return Expression ptr
         */
        GSExpressionPtr getExpression();

    public:

        /**
         *
         * @param visitor
         * @return
         */
        Void accept(GS_Visitor *visitor) override;

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        StatementType getStatementType() override;

    private:

        /**
         * Expression ptr
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_EXPRESSIONSTATEMENT_H
