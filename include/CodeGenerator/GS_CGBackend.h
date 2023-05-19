#ifndef GSLANGUAGE_GS_CGBACKEND_H
#define GSLANGUAGE_GS_CGBACKEND_H

#include <Driver/GS_Session.h>

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Code generation backend type
     */
    enum class CGBackendType {
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
         * Getter for code holder backend type
         * @return Code holder backend type
         */
        virtual CGBackendType GetBackendType() const = 0;
    };

    /**
     * Code holder ptr type
     */
    using GSCodeHolderPtr = std::shared_ptr<GS_CodeHolder>;

    /**
     * Class for containing set of operations with code generation
     */
    class GS_CGBackend {
    public:

        /*
         *
         * GS_CGBackend PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CGBackend();

    public:

        /*
         *
         * GS_CGBackend PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Translating translation unit declaration to any programming language code and returning it in code holder
         * @param session Session
         * @param unit Translation unit declaration
         * @return Code holder
         */
        virtual GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                         AST::GSTranslationUnitDeclarationPtr unit) = 0;

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

    public:

        /*
         *
         * GS_CGBackend PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for code generation backend type
         * @return Code generation backend type
         */
        virtual CGBackendType GetBackendType() const = 0;
    };

    /**
     * Code generation backend type
     */
    using GSCGBackendPtr = std::shared_ptr<GS_CGBackend>;

}

#endif //GSLANGUAGE_GS_CGBACKEND_H
