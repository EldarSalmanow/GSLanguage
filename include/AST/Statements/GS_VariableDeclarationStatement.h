#ifndef GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H
#define GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

#include <AST/GS_Type.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for variable declarations in language
     */
    class GS_VariableDeclarationStatement : public GS_Statement {
    public:

        /**
         * Constructor for variable declaration statement
         * @param name Variable name
         * @param type Variable type
         * @param scope Variable scope
         */
        GS_VariableDeclarationStatement(UString name, GSTypePtr type, GSScopePtr scope);

        /**
         * Constructor for variable declaration statement
         * @param name Variable name
         * @param expression Expression for variable
         * @param scope Variable scope
         */
        GS_VariableDeclarationStatement(UString name, GSExpressionPtr expression, GSScopePtr scope);

        /**
         * Constructor for variable declaration statement
         * @param name Variable name
         * @param type Variable type
         * @param expression Expression for variable
         * @param scope Variable scope
         */
        GS_VariableDeclarationStatement(UString name, GSTypePtr type, GSExpressionPtr expression, GSScopePtr scope);

    public:

        /**
         * Creating variable declaration statement ptr
         * @param name Variable name
         * @param type Variable type
         * @param scope Variable scope
         * @return Variable declaration statement ptr
         */
        static SharedPtr<GS_VariableDeclarationStatement> Create(UString name, GSTypePtr type, GSScopePtr scope);

        /**
         * Creating variable declaration statement ptr
         * @param name Variable name
         * @param expression Expression for variable
         * @param scope Variable scope
         * @return Variable declaration statement ptr
         */
        static SharedPtr<GS_VariableDeclarationStatement> Create(UString name, GSExpressionPtr expression, GSScopePtr scope);

        /**
         * Creating variable declaration statement ptr
         * @param name Variable name
         * @param type Variable type
         * @param expression Expression for variable
         * @param scope Variable scope
         * @return Variable declaration statement ptr
         */
        static SharedPtr<GS_VariableDeclarationStatement> Create(UString name, GSTypePtr type, GSExpressionPtr expression, GSScopePtr scope);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        LRef<UString> getName();

        /**
         * Getter for variable type
         * @return Variable type
         */
        LRef<GSTypePtr> getType();

        /**
         * Getter for expression for variable
         * @return Expression for variable
         */
        LRef<GSExpressionPtr> getExpression();

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        StatementType getStatementType() const override;

    private:

        /**
         * Variable name
         */
        UString _name;

        /**
         * Variable type
         */
        GSTypePtr _type;

        /**
         * Expression for variable
         */
        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H
