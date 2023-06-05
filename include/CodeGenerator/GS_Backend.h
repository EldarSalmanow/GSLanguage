#ifndef GSLANGUAGE_GS_BACKEND_H
#define GSLANGUAGE_GS_BACKEND_H

#include <Driver/GS_Session.h>

#include <AST/Declarations/GS_TranslationUnitDeclaration.h> // TODO replace to AST/AST.h?

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Code generation backend type
     */
    enum class BackendType {
        LLVM
    };

    /**
     * Class for containing generated code
     */
    class GS_CodeHolder {
    public:

        /*
         *
         * GS_CodeHolder PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CodeHolder();

    public:

        /*
         *
         * GS_CodeHolder PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for backend type
         * @return Backend type
         */
        virtual BackendType GetBackendType() const = 0;
    };

    /**
     * Code holder ptr type
     */
    using GSCodeHolderPtr = std::shared_ptr<GS_CodeHolder>;

    /**
     * Class for containing set of code generation operations
     */
    class GS_Backend {
    public:

        /*
         *
         * GS_Backend PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Backend();

    public:

        /*
         *
         * GS_Backend PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Translating node to any programming language code and returning it in code holder
         * @param session Session
         * @param node Node
         * @return Code holder
         */
        virtual GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                         AST::GSNodePtr node) = 0;

        /**
         * Writing code holder to file
         * @param session Session
         * @param fileName File name
         * @param codeHolder Code holder
         * @return Void return
         */
        virtual Void Write(LRef<Driver::GS_Session> session,
                           UString fileName,
                           GSCodeHolderPtr codeHolder) = 0;

        /**
         * Linking files
         * @param session Session
         * @param inputFileNames Input filenames
         * @param outputFileName Output filename
         * @return Void return
         */
        virtual Void Link(LRef<Driver::GS_Session> session,
                          std::vector<UString> inputFileNames,
                          UString outputFileName) = 0;

    public:

        /*
         *
         * GS_Backend PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for backend type
         * @return Backend type
         */
        virtual BackendType GetBackendType() const = 0;
    };

    /**
     * Code generation backend type
     */
    using GSBackendPtr = std::shared_ptr<GS_Backend>;

}

#endif //GSLANGUAGE_GS_BACKEND_H
