#ifndef GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H
#define GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for all assignments in language grammar
     */
    class GS_AssignmentStatement : public GS_Statement {
    public:

        /**
         * Constructor for assignment statement
         * @param lvalueExpression Left value expression ptr
         * @param rvalueExpression Right value expression ptr
         * @param scope Assignment scope
         */
        GS_AssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression, GSScopePtr scope);

    public:

        /**
         * Getter for left value expression ptr
         * @return Left value expression ptr
         */
        LRef<GSExpressionPtr> getLValueExpression();

        /**
         * Getter for right value expression ptr
         * @return Right value expression ptr
         */
        LRef<GSExpressionPtr> getRValueExpression();

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        StatementType getStatementType() const override;

    private:

        /**
         * Left value expression ptr
         */
        GSExpressionPtr _lvalueExpression;

        /**
         * Right value expression ptr
         */
        GSExpressionPtr _rvalueExpression;
    };

}

#endif //GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H
