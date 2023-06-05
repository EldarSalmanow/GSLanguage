#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <CodeGenerator/GS_Backend.h>

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
         * @param backend Backend
         */
        GS_CodeGenerator(LRef<Driver::GS_Session> session,
                         GSBackendPtr backend);

    public:

        /*
         *
         * GS_CodeGenerator PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating code generator
         * @param session Session
         * @param backend Backend
         * @return Code generator
         */
        static GS_CodeGenerator Create(LRef<Driver::GS_Session> session,
                                       GSBackendPtr backend);

    public:

        /*
         *
         * GS_CodeGenerator PUBLIC METHODS
         *
         */

        /**
         * Translating node to any programming language code in backend and returning it in code holder
         * @param node Node
         * @return Code holder
         */
        GSCodeHolderPtr Generate(AST::GSNodePtr node);

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
         * Code generation backend
         */
        GSBackendPtr _backend;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
