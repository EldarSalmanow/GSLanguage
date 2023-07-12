#ifndef GSLANGUAGE_GS_RETURNSTATEMENT_H
#define GSLANGUAGE_GS_RETURNSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /*
     *
     * return <expression>
     *
     */

    /**
     * Class for return statement in language grammar
     */
    class GS_ReturnStatement : public GS_Statement {
    public:

        /*
         *
         * GS_ReturnStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for return statement
         * @param expression Expression
         */
        explicit GS_ReturnStatement(GSExpressionPtr expression);

    public:

        /*
         *
         * GS_ReturnStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating return statement
         * @param expression Expression
         * @return Return statement ptr
         */
        static std::shared_ptr<GS_ReturnStatement> Create(GSExpressionPtr expression);

        /**
         * Creating return statement
         * @return Return statement ptr
         */
        static std::shared_ptr<GS_ReturnStatement> Create();

    public:

        /*
         *
         * GS_ReturnStatement PUBLIC GETTER METHODS
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
         * GS_ReturnStatement PUBLIC OVERRIDE METHODS
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
         * GS_ReturnStatement PRIVATE FIELDS
         *
         */

        /**
         * Expression
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_RETURNSTATEMENT_H
