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

        /*
         *
         * GS_VariableDeclarationStatement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for variable declaration statement
         * @param name Name
         * @param type Type
         * @param expression Expression
         */
        GS_VariableDeclarationStatement(UString name,
                                        Semantic::GSTypePtr type,
                                        GSExpressionPtr expression);

    public:

        /*
         *
         * GS_VariableDeclarationStatement PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating variable declaration statement
         * @param name Name
         * @param type Type
         * @param expression Expression
         * @return Variable declaration statement ptr
         */
        static std::shared_ptr<GS_VariableDeclarationStatement> Create(UString name,
                                                                       Semantic::GSTypePtr type,
                                                                       GSExpressionPtr expression);

        /**
         * Creating variable declaration statement
         * @param name Name
         * @param type Type
         * @return Variable declaration statement ptr
         */
        static std::shared_ptr<GS_VariableDeclarationStatement> Create(UString name,
                                                                       Semantic::GSTypePtr type);

        /**
         * Creating variable declaration statement
         * @param name Name
         * @param expression Expression
         * @return Variable declaration statement ptr
         */
        static std::shared_ptr<GS_VariableDeclarationStatement> Create(UString name,
                                                                       GSExpressionPtr expression);

    public:

        /*
         *
         * GS_VariableDeclarationStatement PUBLIC GETTER METHODS
         *
         */

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

        /*
         *
         * GS_VariableDeclarationStatement PUBLIC OVERRIDE METHODS
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
         * GS_VariableDeclarationStatement PRIVATE FIELDS
         *
         */

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
