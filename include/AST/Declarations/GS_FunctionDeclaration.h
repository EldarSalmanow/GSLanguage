#ifndef GSLANGUAGE_GS_FUNCTIONDECLARATION_H
#define GSLANGUAGE_GS_FUNCTIONDECLARATION_H

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for function declarations in language
     */
    class GS_FunctionDeclaration : public GS_Declaration {
    public:

        /**
         * Constructor for function declaration
         * @param name Function name
         * @param body Function code
         */
        GS_FunctionDeclaration(String name, GSStatementPtrArray body);

    public:

        /**
         * Getter for function name
         * @return Function name
         */
        String getName();

        /**
         * Getter for function code
         * @return Function code
         */
        GSStatementPtrArray getBody();

    public:

        /**
         *
         * @param visitor
         */
        Void accept(GS_Visitor *visitor) override;

    public:

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        DeclarationType getDeclarationType() override;

    private:

        /**
         * Function name
         */
        String _name;

        /**
         * Function code
         */
        GSStatementPtrArray _body;
    };

}

#endif //GSLANGUAGE_GS_FUNCTIONDECLARATION_H
