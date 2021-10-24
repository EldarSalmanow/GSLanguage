#ifndef GSLANGUAGE_GS_VARIABLESPLACEHOLDERVISITOR_H
#define GSLANGUAGE_GS_VARIABLESPLACEHOLDERVISITOR_H

#include <Semantic/Passes/GS_VariablesPlaceholderPass.h>

namespace GSLanguageCompiler::Semantic {

    /**
     *
     */
    class GS_VariablesPlaceholderVisitor : public AST::GS_Visitor {
    public:

        /**
         *
         * @param pass
         */
        explicit GS_VariablesPlaceholderVisitor(GS_VariablesPlaceholderPass *pass);

    public:

        /**
         *
         * @param assignmentStatement
         * @return
         */
        Void visit(AST::GS_AssignmentStatement *assignmentStatement) override;

    private:

        /**
         *
         * @param statement
         * @param expression
         * @return
         */
        Void addVariable(AST::GS_VariableDeclarationStatement *statement, AST::GSExpressionPtr &expression);

    private:

        /**
         *
         */
        GS_VariablesPlaceholderPass *_pass;
    };

}

#endif //GSLANGUAGE_GS_VARIABLESPLACEHOLDERVISITOR_H
