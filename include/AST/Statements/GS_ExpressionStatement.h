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
         * Constructor for expression statement
         * @param expression Expression ptr
         * @param scope Scope
         */
        GS_ExpressionStatement(GSExpressionPtr expression, GSScopePtr scope);

    public:

        /**
         * Creating expression statement ptr
         * @param expression Expression ptr
         * @param scope Scope ptr
         * @return Expression statement ptr
         */
        static SharedPtr<GS_ExpressionStatement> Create(GSExpressionPtr expression, GSScopePtr scope);

    public:

        /**
         * Getter for expression ptr
         * @return Expression ptr
         */
        LRef<GSExpressionPtr> getExpression();

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        StatementType getStatementType() const override;

    private:

        /**
         * Expression ptr
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_EXPRESSIONSTATEMENT_H
