#ifndef GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H
#define GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    // var a -> var_decl_stmt
    // a -> var_using_expr
    //                            |- var_decl_stmt
    // var a = 12 -> assign_stmt --
    //                            |- const_expr
    //                        |- expr_stmt -> var_using_expr
    // a = 23 -> assign_stmt --
    //                        |- const_expr

    /**
     * Class for all assignments in language grammar
     */
    class GS_AssignmentStatement : public GS_Statement {
    public:

        /**
         * Constructor for GS_AssignmentStatement
         * @param node Statement ptr
         * @param expression Expression ptr
         */
        GS_AssignmentStatement(GSStatementPtr statement, GSExpressionPtr expression);

    public:

        /**
         * Getter for statement ptr
         * @return Statement ptr
         */
        GSStatementPtr getStatement();

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
         * Statement ptr
         */
        GSStatementPtr _statement;

        /**
         * Expression ptr
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H
