#ifndef GSLANGUAGE_GS_MATCHSTATEMENT_H
#define GSLANGUAGE_GS_MATCHSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for match arm in language grammar
     */
    class GS_MatchArm {
    public:

        /*
         *
         * GS_MatchArm PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for match arm
         * @param pattern Pattern
         * @param body Body
         */
        GS_MatchArm(GSExpressionPtr pattern,
                    GSStatementPtrArray body);

    public:

        /*
         *
         * GS_MatchArm PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating match arm
         * @param pattern Pattern
         * @param body Body
         * @return Match arm
         */
        static GS_MatchArm Create(GSExpressionPtr pattern,
                                  GSStatementPtrArray body);

        /**
         * Creating match arm
         * @param pattern Pattern
         * @return Match arm
         */
        static GS_MatchArm Create(GSExpressionPtr pattern);

    public:

        /*
         *
         * GS_MatchArm PUBLIC METHODS
         *
         */

        /**
         * Adding statement to match arm body
         * @param statement Statement
         * @return Statement
         */
        LRef<GSStatementPtr> AddStatement(GSStatementPtr statement);

        /**
         * Creating and adding new statement to match arm body and return it
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

            auto &statementRef = AddStatement(statement);

            return statementRef;
        }

    public:

        /*
         *
         * GS_MatchArm PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for pattern
         * @return Pattern
         */
        LRef<GSExpressionPtr> GetPattern();

        /**
         * Getter for body
         * @return Body
         */
        LRef<GSStatementPtrArray> GetBody();

    private:

        /*
         *
         * GS_MatchArm PRIVATE FIELDS
         *
         */

        /**
         * Pattern
         */
        GSExpressionPtr _pattern;

        /**
         * Body
         */
        GSStatementPtrArray _body;
    };

    /**
     * Match arm array type
     */
    using GSMatchArmArray = std::vector<GS_MatchArm>;

    /**
     * Class for match statement in language grammar
     */
    class GS_MatchStatement : public GS_Statement {
    public:

        /*
         *
         * GS_MatchStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for match statement
         * @param expression Expression
         * @param arms Arms
         */
        GS_MatchStatement(GSExpressionPtr expression,
                          GSMatchArmArray arms);

    public:

        /*
         *
         * GS_MatchStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating match statement
         * @param expression Expression
         * @param arms Arms
         * @return Match statement ptr
         */
        static std::shared_ptr<GS_MatchStatement> Create(GSExpressionPtr expression,
                                                         GSMatchArmArray arms);

        /**
         * Creating match statement
         * @param expression Expression
         * @return Match statement ptr
         */
        static std::shared_ptr<GS_MatchStatement> Create(GSExpressionPtr expression);

    public:

        /*
         *
         * GS_MatchStatement PUBLIC METHODS
         *
         */

        /**
         * Adding arm to match body
         * @param arm Arm
         * @return Arm
         */
        LRef<GS_MatchArm> AddArm(GS_MatchArm arm);

    public:

        /*
         *
         * GS_MatchStatement PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for expression
         * @return Expression
         */
        LRef<GSExpressionPtr> GetExpression();

        /**
         * Getter for arms
         * @return Arms
         */
        LRef<GSMatchArmArray> GetArms();

    public:

        /*
         *
         * GS_MatchStatement PUBLIC OVERRIDE METHODS
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
         * GS_MatchStatement PRIVATE FIELDS
         *
         */

        /**
         * Expression
         */
        GSExpressionPtr _expression;

        /**
         * Arms
         */
        GSMatchArmArray _arms;
    };

}

#endif //GSLANGUAGE_GS_MATCHSTATEMENT_H
