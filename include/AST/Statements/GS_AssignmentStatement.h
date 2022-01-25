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
         * Constructor for GS_AssignmentStatement
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
        GSExpressionPtr getLValueExpression() const;

        /**
         * Getter for right value expression ptr
         * @return Right value expression ptr
         */
        GSExpressionPtr getRValueExpression() const;

    public:

        /**
         *
         * @param visitor
         * @return
         */
        Any accept(Ptr<GS_Visitor> visitor) override;

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
