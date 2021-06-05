#ifndef GSLANGUAGE_GS_VARIABLEDECLARATION_H
#define GSLANGUAGE_GS_VARIABLEDECLARATION_H

#include <Compiler/Parser/Statements/GS_Statement.h>

#include <Compiler/Parser/Values/LiteralTypes.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_VariableDeclarationStatement : public GS_Statement {
    public:

        /**
         *
         */
        GS_VariableDeclarationStatement() = default;

        /**
         *
         * @param name
         */
        GS_VariableDeclarationStatement(const std::string &name);

        /**
         *
         * @param name
         * @param type
         */
        GS_VariableDeclarationStatement(const std::string &name, const std::string &type);

    public:

        virtual ~GS_VariableDeclarationStatement() = default;

    public:

        /**
         *
         * @return
         */
        std::string getName();

        /**
         *
         * @return
         */
        std::string getType();

        /**
         *
         * @param type
         */
        void setType(const std::string &type);

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
        std::string _name;

        /**
         *
         */
        std::string _type;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEDECLARATION_H
