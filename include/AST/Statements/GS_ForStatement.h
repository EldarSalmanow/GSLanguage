#ifndef GSLANGUAGE_GS_FORSTATEMENT_H
#define GSLANGUAGE_GS_FORSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for for statement in language grammar
     */
    class GS_ForStatement : public GS_Statement {
    public:

        /*
         *
         * GS_ForStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for for statement
         * @param name Name
         * @param expression Expression
         * @param body Body
         */
        GS_ForStatement(UString name,
                        GSExpressionPtr expression,
                        GSStatementPtrArray body);

    public:

        /*
         *
         * GS_ForStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating for statement
         * @param name Name
         * @param expression Expression
         * @param body Body
         * @return For statement ptr
         */
        static std::shared_ptr<GS_ForStatement> Create(UString name,
                                                       GSExpressionPtr expression,
                                                       GSStatementPtrArray body);

        /**
         * Creating for statement
         * @param name Name
         * @param expression Expression
         * @return For statement ptr
         */
        static std::shared_ptr<GS_ForStatement> Create(UString name,
                                                       GSExpressionPtr expression);

    public:

        /*
         *
         * GS_ForStatement PUBLIC METHODS
         *
         */

        /**
         * Adding statement to for body
         * @param statement Statement
         * @return Statement
         */
        LRef<GSStatementPtr> AddStatement(GSStatementPtr statement);

        /**
         * Creating and adding new statement to for body and return it
         * @tparam StatementT Type of statement for creating
         * @tparam StatementArgs Argument types for creating statement
         * @param args Arguments for creating statement
         * @return Created statement
         */
        template<typename StatementT,
                 typename... StatementArgs>
        inline auto AddStatement(StatementArgs... args) {
            static_assert(std::is_base_of_v<GS_Statement, StatementT>,
                          "Type for creating must be inherited from GS_Statement!");

            auto statement = StatementT::Create(args...);

            auto statementRef = AddStatement(statement);

            return statementRef;
        }

    public:

        /*
         *
         * GS_ForStatement PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for name
         * @return Name
         */
        LRef<UString> GetName();

        /**
         * Getter for expression
         * @return Expression
         */
        LRef<GSExpressionPtr> GetExpression();

        /**
         * Getter for body
         * @return Body
         */
        LRef<GSStatementPtrArray> GetBody();

    public:

        /*
         *
         * GS_ForStatement PUBLIC OVERRIDE METHODS
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
         * GS_ForStatement PRIVATE FIELDS
         *
         */

        /**
         * Name
         */
        UString _name;

        /**
         * Expression
         */
        GSExpressionPtr _expression;

        /**
         * Body
         */
        GSStatementPtrArray _body;
    };

}

#endif //GSLANGUAGE_GS_FORSTATEMENT_H
