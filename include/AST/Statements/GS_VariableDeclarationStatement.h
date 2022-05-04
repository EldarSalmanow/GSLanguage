#ifndef GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H
#define GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H

#include <Semantic/GS_Type.h>

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for variable declarations in language
     */
    class GS_VariableDeclarationStatement : public GS_Statement {
    public:

        /**
         * Constructor for variable declaration statement
         * @param name Name
         * @param type Type
         * @param expression Expression
         */
        GS_VariableDeclarationStatement(UString name, Semantic::GSTypePtr type, GSExpressionPtr expression);

    public:

        /**
         * Creating variable declaration statement ptr
         * @param name Name
         * @param type Type
         * @param expression Expression
         * @return Variable declaration statement ptr
         */
        static SharedPtr<GS_VariableDeclarationStatement> Create(UString name, Semantic::GSTypePtr type, GSExpressionPtr expression);

        /**
         * Creating variable declaration statement ptr
         * @param name Name
         * @param type Type
         * @return Variable declaration statement ptr
         */
        static SharedPtr<GS_VariableDeclarationStatement> Create(UString name, Semantic::GSTypePtr type);

        /**
         * Creating variable declaration statement ptr
         * @param name Name
         * @param expression Expression
         * @return Variable declaration statement ptr
         */
        static SharedPtr<GS_VariableDeclarationStatement> Create(UString name, GSExpressionPtr expression);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        LRef<UString> GetName();

        /**
         * Getter for variable type
         * @return Variable type
         */
        LRef<Semantic::GSTypePtr> GetType();

        /**
         * Getter for expression for variable
         * @return Expression for variable
         */
        LRef<GSExpressionPtr> GetExpression();

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        StatementType GetStatementType() const override;

    private:

        /**
         * Variable name
         */
        UString _name;

        /**
         * Variable type
         */
        Semantic::GSTypePtr _type;

        /**
         * Expression for variable
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H
