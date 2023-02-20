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

        /*
         *
         * GS_AssignmentStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for assignment statement
         * @param lvalueExpression Left value expression
         * @param rvalueExpression Right value expression
         */
        GS_AssignmentStatement(GSExpressionPtr lvalueExpression,
                               GSExpressionPtr rvalueExpression);

    public:

        /*
         *
         * GS_AssignmentStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating assignment statement
         * @param lvalueExpression Left value expression
         * @param rvalueExpression Right value expression
         * @return Assignment statement ptr
         */
        static std::shared_ptr<GS_AssignmentStatement> Create(GSExpressionPtr lvalueExpression,
                                                              GSExpressionPtr rvalueExpression);

    public:

        /*
         *
         * GS_AssignmentStatement PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for left value expression
         * @return Left value expression
         */
        LRef<GSExpressionPtr> GetLValueExpression();

        /**
         * Getter for right value expression
         * @return Right value expression
         */
        LRef<GSExpressionPtr> GetRValueExpression();

    public:

        /*
         *
         * GS_AssignmentStatement PUBLIC OVERRIDE METHODS
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
         * GS_AssignmentStatement PRIVATE FIELDS
         *
         */

        /**
         * Left value expression
         */
        GSExpressionPtr _lvalueExpression;

        /**
         * Right value expression
         */
        GSExpressionPtr _rvalueExpression;
    };

}

#endif //GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H
