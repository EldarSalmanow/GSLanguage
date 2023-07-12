#ifndef GSLANGUAGE_GS_EXPRESSIONSTATEMENT_H
#define GSLANGUAGE_GS_EXPRESSIONSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for expression statement in language grammar
     */
    class GS_ExpressionStatement : public GS_Statement {
    public:

        /*
         *
         * GS_ExpressionStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for expression statement
         * @param expression Expression
         */
        explicit GS_ExpressionStatement(GSExpressionPtr expression);

    public:

        /*
         *
         * GS_ExpressionStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating expression statement
         * @param expression Expression
         * @return Expression statement ptr
         */
        static std::shared_ptr<GS_ExpressionStatement> Create(GSExpressionPtr expression);

    public:

        /*
         *
         * GS_ExpressionStatement PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for expression
         * @return Expression
         */
        LRef<GSExpressionPtr> GetExpression();

    public:

        /*
         *
         * GS_ExpressionStatement PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for statement type
         * @return Statement type
         */
        StatementType GetStatementType() const override;

    private:

        /*
         *
         * GS_ExpressionStatement PRIVATE FIELDS
         *
         */

        /**
         * Expression
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_EXPRESSIONSTATEMENT_H
