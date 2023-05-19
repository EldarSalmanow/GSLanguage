#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <Driver/GS_Session.h>

#include <CodeGenerator/GS_CGBackend.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Class for translation AST to any programming language code
     */
    class GS_CodeGenerator {
    public:

        /*
         *
         * GS_CodeGenerator PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for code generator
         * @param session Session
         * @param unit Translation unit declaration
         */
        GS_CodeGenerator(LRef<Driver::GS_Session> session,
                         AST::GSTranslationUnitDeclarationPtr unit);

    public:

        /*
         *
         * GS_CodeGenerator PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating code generator
         * @param session Session
         * @param unit Translation unit declaration
         * @return Code generator
         */
        static GS_CodeGenerator Create(LRef<Driver::GS_Session> session,
                                       AST::GSTranslationUnitDeclarationPtr unit);

    public:

        /*
         *
         * GS_CodeGenerator PUBLIC METHODS
         *
         */

        /**
         * Translating code holder to any programming language code in backend
         * @param backend Code generation backend
         * @return Code holder
         */
        GSCodeHolderPtr Generate(GSCGBackendPtr backend);

    private:

        /*
         *
         * GS_CodeGenerator PRIVATE FIELDS
         *
         */

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Translation unit declaration
         */
        AST::GSTranslationUnitDeclarationPtr _unit;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
