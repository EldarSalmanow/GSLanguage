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
         * @param scope Function scope
         */
        GS_FunctionDeclaration(UString name, GSScopePtr scope);

        /**
         * Constructor for function declaration
         * @param name Function name
         * @param body Function code
         * @param scope Function scope
         */
        GS_FunctionDeclaration(UString name, GSStatementPtrArray body, GSScopePtr scope);

    public:

        /**
         * Adding statement to function body
         * @param statement Statement
         * @return
         */
        Void addStatement(GSStatementPtr statement);

    public:

        /**
         * Getter for function name
         * @return Function name
         */
        LRef<UString> getName();

        /**
         * Getter for function code
         * @return Function code
         */
        LRef<GSStatementPtrArray> getBody();

        /**
         * Getter for function scope
         * @return Function scope
         */
        LRef<GSScopePtr> getFunctionScope();

    public:

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        DeclarationType getDeclarationType() const override;

    private:

        /**
         * Function name
         */
        UString _name;

        /**
         * Function code
         */
        GSStatementPtrArray _body;

        /**
         * Function scope
         */
        GSScopePtr _functionScope;
    };

}

#endif //GSLANGUAGE_GS_FUNCTIONDECLARATION_H
