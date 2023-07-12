#ifndef GSLANGUAGE_GS_IFSTATEMENT_H
#define GSLANGUAGE_GS_IFSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /*
     *
     * if <condition> {
     *     <ifBody>
     * }
     *
     * OR
     *
     * if <condition> {
     *     <ifBody>
     * } else {
     *     <elseBody>
     * }
     *
     */

    /**
     * Class for if statement in language grammar
     */
    class GS_IfStatement : public GS_Statement {
    public:

        /*
         *
         * GS_IfStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for if statement
         * @param condition Condition
         * @param ifBody If body
         * @param elseBody Else body
         */
        GS_IfStatement(GSExpressionPtr condition,
                       GSStatementPtrArray ifBody,
                       GSStatementPtrArray elseBody);

    public:

        /*
         *
         * GS_IfStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating if statement
         * @param condition Condition
         * @param ifBody If body
         * @param elseBody Else body
         * @return If statement ptr
         */
        static std::shared_ptr<GS_IfStatement> Create(GSExpressionPtr condition,
                                                      GSStatementPtrArray ifBody,
                                                      GSStatementPtrArray elseBody);

        /**
         * Creating if statement
         * @param condition Condition
         * @param ifBody If body
         * @return If statement ptr
         */
        static std::shared_ptr<GS_IfStatement> Create(GSExpressionPtr condition,
                                                      GSStatementPtrArray ifBody);

        /**
         * Creating if statement
         * @param condition Condition
         * @return If statement ptr
         */
        static std::shared_ptr<GS_IfStatement> Create(GSExpressionPtr condition);

    public:

        /*
         *
         * GS_IfStatement PUBLIC METHODS
         *
         */

        /**
         * Adding statement to if body
         * @param statement Statement
         * @return Statement
         */
        LRef<GSStatementPtr> AddIfStatement(GSStatementPtr statement);

        /**
         * Creating and adding new statement to if body and return it
         * @tparam StatementT Type of statement for creating
         * @tparam StatementArgs Argument types for creating statement
         * @param args Arguments for creating statement
         * @return Created statement
         */
        template<typename StatementT,
                 typename... StatementArgs>
        inline auto AddIfStatement(StatementArgs... args) {
            static_assert(std::is_base_of_v<GS_Statement, StatementT>,
                          "Type for creating must be inherited from GS_Statement!");

            auto statement = StatementT::Create(args...);

            auto statementRef = AddIfStatement(statement);

            return statementRef;
        }

        /**
         * Adding statement to else body
         * @param statement Statement
         * @return Statement
         */
        LRef<GSStatementPtr> AddElseStatement(GSStatementPtr statement);

        /**
         * Creating and adding new statement to else body and return it
         * @tparam StatementT Type of statement for creating
         * @tparam StatementArgs Argument types for creating statement
         * @param args Arguments for creating statement
         * @return Created statement
         */
        template<typename StatementT,
                 typename... StatementArgs>
        inline auto AddElseStatement(StatementArgs... args) {
            static_assert(std::is_base_of_v<GS_Statement, StatementT>,
                          "Type for creating must be inherited from GS_Statement!");

            auto statement = StatementT::Create(args...);

            auto statementRef = AddIfStatement(statement);

            return statementRef;
        }

    public:

        /*
         *
         * GS_IfStatement PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for condition
         * @return Condition
         */
        LRef<GSExpressionPtr> GetCondition();

        /**
         * Getter for if body
         * @return If body
         */
        LRef<GSStatementPtrArray> GetIfBody();

        /**
         * Getter for else body
         * @return Else body
         */
        LRef<GSStatementPtrArray> GetElseBody();

    public:

        /*
         *
         * GS_IfStatement PUBLIC OVERRIDE METHODS
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
         * GS_IfStatement PRIVATE FIELDS
         *
         */

        /**
         * Condition
         */
        GSExpressionPtr _condition;

        /**
         * If body
         */
        GSStatementPtrArray _ifBody;

        /**
         * Else body
         */
        GSStatementPtrArray _elseBody;
    };

}

#endif //GSLANGUAGE_GS_IFSTATEMENT_H
