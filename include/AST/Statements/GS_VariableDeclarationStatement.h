#ifndef GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H
#define GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H

#include <AST/GS_Statement.h>

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
         */
        GS_VariableDeclarationStatement(String name, GSTypePtr type);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        String getName();

        /**
         * Getter for variable type
         * @return Variable type
         */
        GSTypePtr getType();

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        StatementType getStatementType() override;

    private:

        /**
         * Variable name
         */
        String _name;

        /**
         * Variable type
         */
        GSTypePtr _type;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEDECLARATIONSTATEMENT_H
