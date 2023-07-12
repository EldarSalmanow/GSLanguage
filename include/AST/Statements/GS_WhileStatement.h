#ifndef GSLANGUAGE_GS_WHILESTATEMENT_H
#define GSLANGUAGE_GS_WHILESTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /*
     *
     * while <condition> {
     *     <body>
     * }
     *
     */

    /**
     * Class for while statement in language grammar
     */
    class GS_WhileStatement : public GS_Statement {
    public:

        /*
         *
         * GS_WhileStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for while statement
         * @param condition Condition
         * @param body Body
         */
        GS_WhileStatement(GSExpressionPtr condition,
                          GSStatementPtrArray body);

    public:

        /*
         *
         * GS_WhileStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating while statement
         * @param condition Condition
         * @param body Body
         * @return While statement ptr
         */
        static std::shared_ptr<GS_WhileStatement> Create(GSExpressionPtr condition,
                                                         GSStatementPtrArray body);

        /**
         * Creating while statement
         * @param condition Condition
         * @return While statement ptr
         */
        static std::shared_ptr<GS_WhileStatement> Create(GSExpressionPtr condition);

    public:

        /*
         *
         * GS_WhileStatement PUBLIC METHODS
         *
         */

        /**
         * Adding statement to while body
         * @param statement Statement
         * @return Statement
         */
        LRef<GSStatementPtr> AddStatement(GSStatementPtr statement);

        /**
         * Creating and adding new statement to while body and return it
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
         * GS_WhileStatement PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for condition
         * @return Condition
         */
        LRef<GSExpressionPtr> GetCondition();

        /**
         * Getter for body
         * @return Body
         */
        LRef<GSStatementPtrArray> GetBody();

    public:

        /*
         *
         * GS_WhileStatement PUBLIC OVERRIDE METHODS
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
         * GS_WhileStatement PRIVATE FIELDS
         *
         */

        /**
         * Condition
         */
        GSExpressionPtr _condition;

        /**
         * Body
         */
        GSStatementPtrArray _body;
    };

}

#endif //GSLANGUAGE_GS_WHILESTATEMENT_H
