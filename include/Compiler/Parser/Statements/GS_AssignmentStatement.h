#ifndef GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H
#define GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H

#include <Compiler/Parser/Expressions/GS_Expression.h>

#include <Compiler/Parser/Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_AssignmentStatement : public GS_Statement {
    public:

        /**
         *
         * @param variableDeclaration
         * @param expression
         */
        GS_AssignmentStatement(GS_VariableDeclarationStatement &variableDeclaration, GSExpressionPointer expression);

    public:

        virtual ~GS_AssignmentStatement() = default;

    public:

        /**
         *
         * @return
         */
        GS_VariableDeclarationStatement getVariableDeclarationStatement();

        /**
         *
         * @return
         */
        GSExpressionPointer getExpression();

    public:

        /**
         *
         * @return
         */
        StatementType getStatementType() override;

        /**
         *
         * @return
         */
        std::string generateCode() override;

        /**
         *
         * @return
         */
        std::string toStringForDebug() override;

    private:

        /**
         *
         */
        GS_VariableDeclarationStatement _variableDeclaration;

        /**
         *
         */
        GSExpressionPointer _expression;
    };

}

#endif //GSLANGUAGE_GS_ASSIGNMENTSTATEMENT_H
